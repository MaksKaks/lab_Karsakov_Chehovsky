#include <gtest/gtest.h>
#include "map.h"
#include "trees.h"
#include "hashtable.h"
#include "kucha.h"
#include <string>

using namespace std;

//ORDEREDMAP

TEST(OrderedMap, can_insert_and_find_element)
{
    Orderedmap<string, int> map;
    map.Insert("apple", 5);

    int* value = map.Find("apple");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(5, *value);
}

TEST(OrderedMap, find_returns_nullptr_for_nonexistent_key)
{
    Orderedmap<string, int> map;
    map.Insert("apple", 5);

    int* value = map.Find("banana");
    EXPECT_EQ(nullptr, value);
}

TEST(OrderedMap, can_update_existing_key)
{
    Orderedmap<string, int> map;
    map.Insert("apple", 5);
    map.Insert("apple", 10);

    int* value = map.Find("apple");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(10, *value);
}

TEST(OrderedMap, can_delete_existing_key)
{
    Orderedmap<string, int> map;
    map.Insert("apple", 5);
    map.Insert("banana", 3);
    map.Delete("apple");

    EXPECT_EQ(1, map.Count());
    EXPECT_EQ(nullptr, map.Find("apple"));
    EXPECT_NE(nullptr, map.Find("banana"));
}

TEST(OrderedMap, delete_nonexistent_key_throws_exception)
{
    Orderedmap<string, int> map;
    map.Insert("apple", 5);

    ASSERT_ANY_THROW(map.Delete("banana"));
}

TEST(OrderedMap, operator_brackets_creates_new_element)
{
    Orderedmap<string, int> map;
    map["newkey"] = 42;

    int* value = map.Find("newkey");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(42, *value);
}

TEST(OrderedMap, can_get_size)
{
    Orderedmap<string, int> map;
    EXPECT_EQ(0, map.Count());

    map.Insert("apple", 5);
    map.Insert("banana", 3);
    EXPECT_EQ(2, map.Count());

    map.Delete("apple");
    EXPECT_EQ(1, map.Count());
}

TEST(OrderedMap, can_clear_map)
{
    Orderedmap<string, int> map;
    map.Insert("apple", 5);
    map.Insert("banana", 3);
    map.Clear();

    EXPECT_EQ(0, map.Count());
    EXPECT_TRUE(map.isempty());
    EXPECT_EQ(nullptr, map.Find("apple"));
}

//UNORDEREDMAP

TEST(UnorderedMap, can_insert_and_find_element)
{
    Unorderedmap<string, int> map;
    map.Insert("apple", 5);

    int* value = map.Find("apple");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(5, *value);
}

TEST(UnorderedMap, find_returns_nullptr_for_nonexistent_key)
{
    Unorderedmap<string, int> map;
    map.Insert("apple", 5);

    int* value = map.Find("banana");
    EXPECT_EQ(nullptr, value);
}

TEST(UnorderedMap, can_update_existing_key)
{
    Unorderedmap<string, int> map;
    map.Insert("apple", 5);
    map.Insert("apple", 10);

    int* value = map.Find("apple");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(10, *value);
}

TEST(UnorderedMap, can_delete_existing_key)
{
    Unorderedmap<string, int> map;
    map.Insert("apple", 5);
    map.Insert("banana", 3);
    map.Delete("apple");

    EXPECT_EQ(1, map.Count());
    EXPECT_EQ(nullptr, map.Find("apple"));
    EXPECT_NE(nullptr, map.Find("banana"));
}

TEST(UnorderedMap, delete_nonexistent_key_throws_exception)
{
    Unorderedmap<string, int> map;
    map.Insert("apple", 5);

    ASSERT_ANY_THROW(map.Delete("banana"));
}

TEST(UnorderedMap, operator_brackets_creates_new_element)
{
    Unorderedmap<string, int> map;
    map["newkey"] = 42;

    int* value = map.Find("newkey");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(42, *value);
}

TEST(UnorderedMap, can_get_size)
{
    Unorderedmap<string, int> map;
    EXPECT_EQ(0, map.Count());

    map.Insert("apple", 5);
    map.Insert("banana", 3);
    EXPECT_EQ(2, map.Count());
}

//BINARYTREE

TEST(BinaryTree, can_insert_and_find_element)
{
    Binarytree<string, int> tree;
    tree.Insert("apple", 5);

    int* value = tree.Find("apple");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(5, *value);
}

TEST(BinaryTree, find_returns_nullptr_for_nonexistent_key)
{
    Binarytree<string, int> tree;
    tree.Insert("apple", 5);

    int* value = tree.Find("banana");
    EXPECT_EQ(nullptr, value);
}

TEST(BinaryTree, can_update_existing_key)
{
    Binarytree<string, int> tree;
    tree.Insert("apple", 5);
    tree.Insert("apple", 10);

    int* value = tree.Find("apple");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(10, *value);
}

TEST(BinaryTree, can_delete_leaf_node)
{
    Binarytree<string, int> tree;
    tree.Insert("banana", 3);
    tree.Insert("apple", 5);
    tree.Insert("cherry", 7);
    tree.Delete("apple");

    EXPECT_EQ(2, tree.Count());
    EXPECT_EQ(nullptr, tree.Find("apple"));
}

TEST(BinaryTree, can_delete_node_with_two_children)
{
    Binarytree<int, int> tree;
    tree.Insert(50, 50);
    tree.Insert(30, 30);
    tree.Insert(70, 70);
    tree.Insert(20, 20);
    tree.Insert(40, 40);

    tree.Delete(50);

    EXPECT_EQ(4, tree.Count());
    EXPECT_EQ(nullptr, tree.Find(50));
}

TEST(BinaryTree, operator_brackets_creates_new_element)
{
    Binarytree<string, int> tree;
    tree["newkey"] = 42;

    int* value = tree.Find("newkey");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(42, *value);
}

TEST(BinaryTree, can_get_size)
{
    Binarytree<string, int> tree;
    EXPECT_EQ(0, tree.Count());

    tree.Insert("apple", 5);
    tree.Insert("banana", 3);
    EXPECT_EQ(2, tree.Count());
}

TEST(BinaryTree, can_clear_tree)
{
    Binarytree<string, int> tree;
    tree.Insert("apple", 5);
    tree.Insert("banana", 3);
    tree.Clear();

    EXPECT_EQ(0, tree.Count());
    EXPECT_TRUE(tree.isempty());
}

//CHAINHASHTABLE

TEST(ChainHashTable, can_insert_and_find_element)
{
    ChainHashTable<string, int> ht;
    ht.Insert("apple", 5);

    int* value = ht.Find("apple");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(5, *value);
}

TEST(ChainHashTable, find_returns_nullptr_for_nonexistent_key)
{
    ChainHashTable<string, int> ht;
    ht.Insert("apple", 5);

    int* value = ht.Find("banana");
    EXPECT_EQ(nullptr, value);
}

TEST(ChainHashTable, can_update_existing_key)
{
    ChainHashTable<string, int> ht;
    ht.Insert("apple", 5);
    ht.Insert("apple", 10);

    int* value = ht.Find("apple");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(10, *value);
}

TEST(ChainHashTable, can_delete_existing_key)
{
    ChainHashTable<string, int> ht;
    ht.Insert("apple", 5);
    ht.Insert("banana", 3);
    ht.Delete("apple");

    EXPECT_EQ(1, ht.count());
    EXPECT_EQ(nullptr, ht.Find("apple"));
    EXPECT_NE(nullptr, ht.Find("banana"));
}

TEST(ChainHashTable, delete_nonexistent_key_throws_exception)
{
    ChainHashTable<string, int> ht;
    ht.Insert("apple", 5);

    ASSERT_ANY_THROW(ht.Delete("banana"));
}

TEST(ChainHashTable, operator_brackets_creates_new_element)
{
    ChainHashTable<string, int> ht;
    ht["newkey"] = 42;

    int* value = ht.Find("newkey");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(42, *value);
}

TEST(ChainHashTable, can_get_size)
{
    ChainHashTable<string, int> ht;
    EXPECT_EQ(0, ht.count());

    ht.Insert("apple", 5);
    ht.Insert("banana", 3);
    EXPECT_EQ(2, ht.count());
}

TEST(ChainHashTable, can_clear_table)
{
    ChainHashTable<string, int> ht;
    ht.Insert("apple", 5);
    ht.Insert("banana", 3);
    ht.Clear();

    EXPECT_EQ(0, ht.count());
    EXPECT_TRUE(ht.isempty());
}

//D-ÊÓ×À

TEST(Heapmax, can_create_heap_with_default_children)
{
    Heapmax<int> heap;
    EXPECT_TRUE(heap.isEmpty());
    EXPECT_EQ(0, heap.getSize());
}

TEST(Heapmax, can_create_heap_with_specified_children)
{
    Heapmax<int> heap(3);
    EXPECT_TRUE(heap.isEmpty());
    EXPECT_EQ(0, heap.getSize());
}

TEST(Heapmax, throws_when_children_count_less_than_2)
{
    EXPECT_ANY_THROW(Heapmax<int> heap(1));
}

TEST(Heapmax, can_create_heap_from_vector)
{
    vector<int> source = { 1, 2, 3, 4, 5 };
    Heapmax<int> heap(source);

    EXPECT_EQ(5, heap.getSize());
    EXPECT_FALSE(heap.isEmpty());
}

TEST(Heapmax, throws_when_creating_from_empty_vector)
{
    vector<int> empty;
    EXPECT_ANY_THROW(Heapmax<int> heap(empty));
}

TEST(Heapmax, can_push_element)
{
    Heapmax<int> heap;
    heap.push(10);

    EXPECT_EQ(1, heap.getSize());
    EXPECT_EQ(10, heap.Getmaxval());
}

TEST(Heapmax, push_maintains_heap_property_max_at_root)
{
    Heapmax<int> heap;
    heap.push(10);
    heap.push(20);
    heap.push(5);
    heap.push(30);

    EXPECT_EQ(30, heap.Getmaxval());
    EXPECT_EQ(4, heap.getSize());
}

TEST(Heapmax, can_pop_max_element)
{
    Heapmax<int> heap;
    heap.push(10);
    heap.push(20);
    heap.push(5);

    int maxVal = heap.popmax();

    EXPECT_EQ(20, maxVal);
    EXPECT_EQ(2, heap.getSize());
}

TEST(Heapmax, popmax_removes_max_and_maintains_heap_property)
{
    Heapmax<int> heap;
    heap.push(10);
    heap.push(30);
    heap.push(20);
    heap.push(5);
    heap.push(25);

    heap.popmax();

    EXPECT_EQ(25, heap.Getmaxval());
    EXPECT_EQ(4, heap.getSize());
}

TEST(Heapmax, popmax_throws_when_heap_empty)
{
    Heapmax<int> heap;
    EXPECT_ANY_THROW(heap.popmax());
}

TEST(Heapmax, getmaxval_returns_max_without_removing)
{
    Heapmax<int> heap;
    heap.push(10);
    heap.push(30);
    heap.push(20);

    int maxVal = heap.Getmaxval();

    EXPECT_EQ(30, maxVal);
    EXPECT_EQ(3, heap.getSize());
}

TEST(Heapmax, getmaxval_throws_when_heap_empty)
{
    Heapmax<int> heap;
    EXPECT_ANY_THROW(heap.Getmaxval());
}

TEST(Heapmax, can_check_if_heap_is_empty)
{
    Heapmax<int> heap;
    EXPECT_TRUE(heap.isEmpty());

    heap.push(10);
    EXPECT_FALSE(heap.isEmpty());

    heap.popmax();
    EXPECT_TRUE(heap.isEmpty());
}

TEST(Heapmax, can_get_heap_size)
{
    Heapmax<int> heap;
    EXPECT_EQ(0, heap.getSize());

    heap.push(10);
    EXPECT_EQ(1, heap.getSize());

    heap.push(20);
    EXPECT_EQ(2, heap.getSize());

    heap.popmax();
    EXPECT_EQ(1, heap.getSize());
}

TEST(Heapmax, can_clear_heap)
{
    Heapmax<int> heap;
    heap.push(10);
    heap.push(20);
    heap.push(30);

    heap.clear();

    EXPECT_TRUE(heap.isEmpty());
    EXPECT_EQ(0, heap.getSize());
}

TEST(Heapmax, works_with_different_data_types)
{
    Heapmax<double> doubleHeap;
    doubleHeap.push(1.5);
    doubleHeap.push(3.7);
    doubleHeap.push(2.1);

    EXPECT_EQ(3.7, doubleHeap.Getmaxval());

    Heapmax<string> stringHeap;
    stringHeap.push("apple");
    stringHeap.push("banana");
    stringHeap.push("cherry");

    EXPECT_EQ("cherry", stringHeap.Getmaxval());
}

TEST(Heapmax, d_heap_property_with_3_children)
{
    Heapmax<int> heap(3);
    heap.push(10);
    heap.push(20);
    heap.push(30);
    heap.push(5);
    heap.push(25);
    heap.push(35);

    EXPECT_EQ(35, heap.Getmaxval());
    EXPECT_EQ(6, heap.getSize());

    heap.popmax();
    EXPECT_EQ(30, heap.Getmaxval());
}

TEST(Heapmax, heap_from_vector_preserves_max_at_root)
{
    vector<int> source = { 5, 3, 8, 1, 9, 2, 7 };
    Heapmax<int> heap(source);

    int maxFromVector = *max_element(source.begin(), source.end());
    EXPECT_EQ(maxFromVector, heap.Getmaxval());
}

TEST(Heapmax, multiple_push_and_pop_sequence)
{
    Heapmax<int> heap;

    heap.push(15);
    heap.push(25);
    heap.push(10);
    heap.push(30);
    heap.push(20);

    EXPECT_EQ(30, heap.popmax()); 
    EXPECT_EQ(25, heap.popmax()); 
    EXPECT_EQ(20, heap.popmax()); 
    EXPECT_EQ(15, heap.popmax()); 
    EXPECT_EQ(10, heap.popmax()); 

    EXPECT_TRUE(heap.isEmpty());
}

//ÀÂË-ÄÅÐÅÂÜß

TEST(AVLTree, can_insert_and_find_element)
{
    AVLTree<string, int> tree;
    tree.Insert("apple", 5);

    int* value = tree.Find("apple");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(5, *value);
}

TEST(AVLTree, find_returns_nullptr_for_nonexistent_key)
{
    AVLTree<string, int> tree;
    tree.Insert("apple", 5);

    int* value = tree.Find("banana");
    EXPECT_EQ(nullptr, value);
}

TEST(AVLTree, can_update_existing_key)
{
    AVLTree<string, int> tree;
    tree.Insert("apple", 5);
    tree.Insert("apple", 10);

    int* value = tree.Find("apple");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(10, *value);
}

TEST(AVLTree, can_delete_leaf_node)
{
    AVLTree<string, int> tree;
    tree.Insert("banana", 3);
    tree.Insert("apple", 5);
    tree.Insert("cherry", 7);
    tree.Delete("apple");

    EXPECT_EQ(2, tree.Count());
    EXPECT_EQ(nullptr, tree.Find("apple"));
    EXPECT_NE(nullptr, tree.Find("banana"));
    EXPECT_NE(nullptr, tree.Find("cherry"));
}

TEST(AVLTree, can_delete_node_with_one_child)
{
    AVLTree<int, int> tree;
    tree.Insert(50, 50);
    tree.Insert(30, 30);
    tree.Insert(70, 70);
    tree.Insert(20, 20);

    tree.Delete(30);

    EXPECT_EQ(3, tree.Count());
    EXPECT_EQ(nullptr, tree.Find(30));
    EXPECT_NE(nullptr, tree.Find(20));
    EXPECT_NE(nullptr, tree.Find(50));
    EXPECT_NE(nullptr, tree.Find(70));
}

TEST(AVLTree, can_delete_node_with_two_children)
{
    AVLTree<int, int> tree;
    tree.Insert(50, 50);
    tree.Insert(30, 30);
    tree.Insert(70, 70);
    tree.Insert(20, 20);
    tree.Insert(40, 40);
    tree.Insert(60, 60);
    tree.Insert(80, 80);

    tree.Delete(50);

    EXPECT_EQ(6, tree.Count());
    EXPECT_EQ(nullptr, tree.Find(50));
}

TEST(AVLTree, keys_are_returned_in_sorted_order)
{
    AVLTree<string, int> tree;
    tree.Insert("banana", 3);
    tree.Insert("apple", 5);
    tree.Insert("cherry", 7);
    tree.Insert("date", 2);

    vector<string> keys = tree.keys();
    ASSERT_EQ(4, keys.size());
    EXPECT_EQ("apple", keys[0]);
    EXPECT_EQ("banana", keys[1]);
    EXPECT_EQ("cherry", keys[2]);
    EXPECT_EQ("date", keys[3]);
}

TEST(AVLTree, operator_brackets_creates_new_element)
{
    AVLTree<string, int> tree;
    tree["newkey"] = 42;

    int* value = tree.Find("newkey");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(42, *value);
}

TEST(AVLTree, operator_brackets_updates_existing_element)
{
    AVLTree<string, int> tree;
    tree["test"] = 10;
    tree["test"] = 20;

    EXPECT_EQ(20, tree["test"]);
    EXPECT_EQ(1, tree.Count());
}

TEST(AVLTree, can_get_correct_size)
{
    AVLTree<string, int> tree;
    EXPECT_EQ(0, tree.Count());

    tree.Insert("a", 1);
    EXPECT_EQ(1, tree.Count());

    tree.Insert("b", 2);
    tree.Insert("c", 3);
    EXPECT_EQ(3, tree.Count());

    tree.Delete("b");
    EXPECT_EQ(2, tree.Count());
}

TEST(AVLTree, isempty_works_correctly)
{
    AVLTree<string, int> tree;
    EXPECT_TRUE(tree.isempty());

    tree.Insert("a", 1);
    EXPECT_FALSE(tree.isempty());

    tree.Clear();
    EXPECT_TRUE(tree.isempty());
}

TEST(AVLTree, can_clear_tree)
{
    AVLTree<string, int> tree;
    tree.Insert("apple", 5);
    tree.Insert("banana", 3);
    tree.Insert("cherry", 7);
    tree.Clear();

    EXPECT_EQ(0, tree.Count());
    EXPECT_TRUE(tree.isempty());
    EXPECT_EQ(nullptr, tree.Find("apple"));
}

TEST(AVLTree, avl_stays_balanced_after_sorted_insertions)
{
    AVLTree<int, int> tree;

    for (int i = 1; i <= 100; i++) {
        tree.Insert(i, i);
    }

    for (int i = 1; i <= 100; i++) {
        int* value = tree.Find(i);
        ASSERT_NE(nullptr, value);
        EXPECT_EQ(i, *value);
    }

    EXPECT_EQ(100, tree.Count());
}

TEST(AVLTree, avl_stays_balanced_after_deletions)
{
    AVLTree<int, int> tree;

    for (int i = 1; i <= 50; i++) {
        tree.Insert(i, i);
    }

    for (int i = 10; i <= 40; i++) {
        tree.Delete(i);
    }

    for (int i = 1; i <= 9; i++) {
        EXPECT_NE(nullptr, tree.Find(i));
    }
    for (int i = 41; i <= 50; i++) {
        EXPECT_NE(nullptr, tree.Find(i));
    }
    for (int i = 10; i <= 40; i++) {
        EXPECT_EQ(nullptr, tree.Find(i));
    }

    EXPECT_EQ(19, tree.Count());
}

TEST(AVLTree, works_with_string_keys)
{
    AVLTree<string, string> tree;
    tree.Insert("Russia", "Moscow");
    tree.Insert("USA", "Washington");
    tree.Insert("France", "Paris");
    tree.Insert("Germany", "Berlin");

    EXPECT_EQ("Moscow", *tree.Find("Russia"));
    EXPECT_EQ("Paris", *tree.Find("France"));
    EXPECT_EQ(4, tree.Count());
}

TEST(AVLTree, works_with_double_values)
{
    AVLTree<string, double> tree;
    tree.Insert("pi", 3.14159);
    tree.Insert("e", 2.71828);

    EXPECT_DOUBLE_EQ(3.14159, *tree.Find("pi"));
    EXPECT_DOUBLE_EQ(2.71828, *tree.Find("e"));
}

TEST(AVLTree, copy_values_correctly_after_update)
{
    AVLTree<int, string> tree;
    tree.Insert(1, "one");
    tree.Insert(2, "two");
    tree.Insert(1, "ONE");

    string* val = tree.Find(1);
    ASSERT_NE(nullptr, val);
    EXPECT_EQ("ONE", *val);
    EXPECT_EQ(2, tree.Count());
}

TEST(AVLTree, handles_large_number_of_elements)
{
    AVLTree<int, int> tree;

    for (int i = 0; i < 1000; i++) {
        tree.Insert(i, i * 10);
    }

    EXPECT_EQ(1000, tree.Count());

    for (int i = 0; i < 1000; i++) {
        int* val = tree.Find(i);
        ASSERT_NE(nullptr, val);
        EXPECT_EQ(i * 10, *val);
    }
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
