#pragma once
#include <iostream>

template <class type>
class Iterator;

template <class type>
class List;

// ------------------ NODE -----------------------

template <class type>
class Node {

	template <class k>
	friend class List;

	template <class k>
	friend class Iterator;

private:
	type data;
	Node* next_ptr;

public:
	Node(type value, Node* next = nullptr) : data(value), next_ptr(next) {}
	Node(const Node& obj) : data(obj.data), next_ptr(obj.next_ptr) {}

	Node& operator=(const Node& obj) {
		data = obj.data;
		next_ptr = obj.next_ptr;
		return *this;
	}

	bool operator==(const Node& obj) const noexcept {
		return ((data == obj.data) && (next_ptr == obj.next_ptr));
	}
	bool operator!=(const Node& obj) const noexcept {
		return ((data != obj.data) || (next_ptr != obj.next_ptr));
	}

	type GetData() const { return data; }
	Node* GetNext() { return next_ptr; }

	void SetData(type value) { data = value; }
	void SetNext(Node& next) { next_ptr = &next; }

};

template <class type>
std::ostream& operator<<(std::ostream& stream, const Node<type>& obj) {
	stream << obj.GetData();
	return stream;
}

// --------------------- ITERATOR ------------------------

template <class type>
class Iterator {

	template <class k>
	friend class List;

private:
	Node<type>* current_node;

public:
	Iterator(Node<type>& node) : current_node(&node) {}
	Iterator(Node<type>* node) : current_node(node) {}
	Iterator(const Iterator<type>& obj) : current_node(obj.current_node) {}

	Iterator& operator++() {
		if (current_node != nullptr) { current_node = current_node->next_ptr; }
		else { throw std::out_of_range("Invalid iterator!"); }
		return *this;
	}
	const Iterator operator++(int) {
		if (current_node == nullptr) throw std::out_of_range("Invalid iterator!");
		Iterator<type> it(*this);
		++(*this);
		return it;
	}

	bool operator==(const Iterator<type>& obj) const noexcept {
		return current_node == obj.current_node;
	}
	bool operator!=(const Iterator<type>& obj) const noexcept {
		return current_node != obj.current_node;
	}

	type& operator*() {
		return current_node->data;
	}
	type& operator*() const {
		return current_node->data;
	}

	type* operator->() {
		return &(current_node->data);
	}
	const type* operator->() const {
		return &(current_node->data);
	}

};

template <class type>
std::ostream& operator<<(std::ostream& stream, const Iterator<type>& obj) {
	stream << *obj;
	return stream;
}

// ------------------------ LIST ------------------------

template <class type>
class List {
private:
	Node<type>* head_node;

public:
	List(Node<type>* node = nullptr) : head_node(node) {}

	void push_back(type value) {
		if (head_node == nullptr) {
			head_node = new Node<type>(value);
		} else {
			Node<type>* current = head_node;
			while (current->next_ptr) {
				current = current->next_ptr;
			}
			current->next_ptr = new Node<type>(value);
		}
	}

	void push_back(const Node<type>& node) {
		push_back(node.data);
	}

	List(const List& obj) : head_node(nullptr) {
		Node<type>* current = obj.head_node;
		while (current) {
			push_back(current->data);
			current = current->next_ptr;
		}
	}

	void erase(Iterator<type> it) {
		if (head_node == nullptr || it.current_node == nullptr) {
			throw std::runtime_error("Invalid iterator!");
		}
		if (head_node == it.current_node) {
			Node<type>* del_node = head_node;
			head_node = head_node->next_ptr;
			delete del_node;
			return;
		}
		Node<type>* current = head_node;
		while (current->next_ptr && current->next_ptr != it.current_node) {
			current = current->next_ptr;
		}
		if (current->next_ptr == it.current_node) {
			Node<type>* del_node = current->next_ptr;
			current->next_ptr = current->next_ptr->next_ptr;
			delete del_node;
		} else {
			throw std::runtime_error("Iterator does not belong to this list!");
		}
	}

	Iterator<type> begin() { return Iterator<type>(head_node); }
	Iterator<type> end() { return nullptr; }

	~List() {
		Node<type>* current_node = head_node;

		while (current_node) {
			Node<type>* next_node = current_node->next_ptr;
			delete current_node;
			current_node = next_node;
		}
		head_node = nullptr;
	}
};