#include "List.h"
#include <gtest.h>

TEST(Node, can_create_node) {
	ASSERT_NO_THROW(Node<int> obj(1));
}

TEST(Node, is_node_comparison_valid) {
	Node<int> node1(1);
	Node<int> node2(1);
	EXPECT_TRUE(node1 == node2);
}

TEST(Node, is_node_comparison_unequal_valid) {
	Node<int> node1(1);
	Node<int> node2(2);
	EXPECT_TRUE(node1 != node2);
}

TEST(Node, can_copy_existing_node) {
	Node<int> obj1(1);
	ASSERT_NO_THROW(Node<int> obj2(obj1));
}

TEST(Node, can_copy_existing_node_by_operator) {
	Node<int> obj1(1);
	Node<int> obj2(2);
	ASSERT_NO_THROW(obj2 = obj1);
}

TEST(List, can_create_empty_list) {
	ASSERT_NO_THROW(List<int> obj);
}

TEST(List, can_create_list_from_existing_node) {
	Node<int> node(1);
	ASSERT_NO_THROW(List<int> obj(&node));
}

TEST(List, can_add_new_node) {
	Node<int> node(1);
	List<int> obj;
	ASSERT_NO_THROW(obj.push_back(node));
}

TEST(List, can_add_many_nodes) {
	Node<int> node1(1);
	Node<int> node2(2);
	Node<int> node3(3);
	List<int> obj;
	obj.push_back(node1);
	obj.push_back(node2);
	ASSERT_NO_THROW(obj.push_back(node3));
}

TEST(List, can_add_node_from_value) {
	List<int> obj;
	ASSERT_NO_THROW(obj.push_back(1));
}

TEST(List, can_copy_existing_list) {
	Node<int> node(1);
	List<int> src(&node);
	ASSERT_NO_THROW(List<int> obj(src));
}

TEST(List, is_list_erase_valid) {
	List<int> obj;
	obj.push_back(1);
	obj.push_back(2);
	obj.push_back(3);
	Iterator<int> it(obj.begin());
	it++;
	ASSERT_NO_THROW(obj.erase(it));
}

TEST(Iterator, can_create_iterator) {
	Node<int> node(1);
	ASSERT_NO_THROW(Iterator<int> it(node));
}

TEST(Iterator, can_copy_existing_iterator) {
	Node<int> node(1);
	Iterator<int> obj(node);
	ASSERT_NO_THROW(Iterator<int> it(obj));
}

TEST(Iterator, can_get_data_from_iterator) {
	Node<int> node(1);
	Iterator<int> obj(node);
	ASSERT_NO_THROW(*obj);
}

TEST(Iterator, is_data_from_iterator_valid) {
	Node<int> node(1);
	Iterator<int> obj(node);
	EXPECT_EQ(*obj, 1);
}

TEST(Iterator, can_get_begin_of_list) {
	Node<int> node(1);
	List<int> obj(&node);
	ASSERT_NO_THROW(Iterator<int> it(obj.begin()));
}

TEST(Iterator, is_increment_iterator_valid) {
	List<int> obj;
	obj.push_back(1);
	obj.push_back(2);
	obj.push_back(3);
	Iterator<int> it(obj.begin());
	it++;
	it++;
	EXPECT_EQ(*it, 3);
}