#include <iostream>
#include "List.h"
#include "Monom.h"
#include "Polynomial.h"

int main() {
    // ----------------------- EXAMPLE ----------------------

    Polynomial<double> a1;
    Polynomial<double> a2;

    std::cin >> a1; // 5 * x ^ 5.8 + 10 * y ^ 3.2
    std::cin >> a2; // 10 * x ^ 4 + 5 * y ^ 6

    std::cout << a1 << '\n' << a2 << std::endl;

    Polynomial<double> b1 = a1 + a2; // 5*x^5.8 + 10*y^3.2 + 10*x^4 + 5*y^6
    Polynomial<double> b2 = a1 - a2; // 5*x^5.8 + 10*y^3.2 - 10*x^4 - 5*y^6
    Polynomial<double> b3 = a1 * a2; // 50*x^9.8 + 25*x^5.8*y^6 + 100*y^3.2*x^4 + 50*y^9.2
    Polynomial<double> b4 = a1 * 10; // 50*x^5.8 + 100*y^3.2

    std::cout << b1 << std::endl;
    std::cout << b2 << std::endl;
    std::cout << b3 << std::endl;
    std::cout << b4 << std::endl;
}
