#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include "Monom.h"
#include "List.h"

template <class type>
class Polynomial {
public:
    List<Monom<type>> monoms;
    Polynomial() {}

    void push(const Monom<type>& obj) {
        bool flag = false;

        for (auto it = monoms.begin(); it != monoms.end(); it++) {
            if (it->GetVars() == obj.GetVars()) {
                it->coef += obj.coef;
                if (it->coef == 0) { monoms.erase(it); }
                flag = true;
                break;
            }
        }

        if (!flag && obj.coef != 0) { monoms.push_back(obj); }
    }

    Polynomial<type> operator+(Polynomial<type>& obj) {
        Polynomial<type> res = *this;
        for (auto it = obj.monoms.begin(); it != obj.monoms.end(); it++) {
            res.push(*it);
        }
        return res;
    }

    Polynomial<type> operator-(Polynomial<type>& obj) {
        Polynomial<type> res = *this;
        for (auto it = obj.monoms.begin(); it != obj.monoms.end(); it++) {
            Monom<type> alt_monom = *it;
            alt_monom.coef = -alt_monom.coef;
            res.push(alt_monom);
        }
        return res;
    }

    Polynomial<type> operator*(Polynomial<type>& obj) {
        Polynomial<type> res;
        for (auto it = monoms.begin(); it != monoms.end(); it++) {
            for (auto k = obj.monoms.begin(); k != obj.monoms.end(); k++) {
                Monom<type> comp = (*it) * (*k);
                res.push(comp);
            }
        }
        return res;
    }

    Polynomial<type> operator*(type value) {
        Polynomial<type> res;
        for (auto it = monoms.begin(); it != monoms.end(); it++) {
            Monom<type> temp = *it;
            temp.coef *= value;
            res.push(temp);
        }
        return res;
    }

    template <class K>
    friend std::ostream& operator<<(std::ostream& ostr, Polynomial<K>& obj) {
        auto it = obj.monoms.begin();
        if (it != obj.monoms.end()) {
            ostr << *it;
            ++it;
        }
        while (it != obj.monoms.end()) {
            ostr << " + " << *it;
            ++it;
        }
        return ostr;
    }

    bool ValidCheck(const std::string& str) {
        for (char symbol : str) {
            if (!std::isdigit(symbol) && !std::isalpha(symbol) && symbol != '-' && symbol != '+' && symbol != '*' && symbol != '^' && symbol != '.') { return false; }
        }
        return true;
    }

    friend std::istream& operator>>(std::istream& istr, Polynomial& obj) {
        std::string str;

        std::getline(istr, str);
        GapsTransform(str);
        if (!obj.ValidCheck(str)) { throw std::invalid_argument("Invalid args!"); }

        std::string tmp_str = "";

        if (str[0] == '-') {
            tmp_str = "-";
            str = str.substr(1);
        }

        for (char symbol : str) {
            Monom<type> monom;
            std::istringstream str_stream(tmp_str);

            if (symbol == '-') {
                str_stream >> monom;
                obj.push(monom);
                tmp_str = "-";
            } else if (symbol == '+') {
                str_stream >> monom;
                obj.push(monom);
                tmp_str = "";
            } else {
                tmp_str += symbol;
            }
        }

        Monom<type> monom;
        std::istringstream str_stream(tmp_str);
        str_stream >> monom;
        obj.push(monom);

        return istr;
    }
};