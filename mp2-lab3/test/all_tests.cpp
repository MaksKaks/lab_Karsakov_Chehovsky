#include <gtest/gtest.h>
#include "map.h"
#include "trees.h"
#include "hashtable.h"
#include <string>

using namespace std;

//ORDEREDMAP

TEST(OrderedMap, can_insert_and_find_element)
// Проверяет вставку и поиск элемента
{
    Orderedmap<string, int> map;
    map.Insert("apple", 5);

    int* value = map.Find("apple");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(5, *value);
}

TEST(OrderedMap, find_returns_nullptr_for_nonexistent_key)
// Проверяет поиск несуществующего ключа
{
    Orderedmap<string, int> map;
    map.Insert("apple", 5);

    int* value = map.Find("banana");
    EXPECT_EQ(nullptr, value);
}

TEST(OrderedMap, can_update_existing_key)
// Проверяет обновление значения по существующему ключу
{
    Orderedmap<string, int> map;
    map.Insert("apple", 5);
    map.Insert("apple", 10);

    int* value = map.Find("apple");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(10, *value);
}

TEST(OrderedMap, can_delete_existing_key)
// Проверяет удаление элемента
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
// Проверяет, что при удалении несуществующего ключа выбрасывается исключение
{
    Orderedmap<string, int> map;
    map.Insert("apple", 5);

    ASSERT_ANY_THROW(map.Delete("banana"));
}

TEST(OrderedMap, operator_brackets_creates_new_element)
// Проверяет, что оператор [] создаёт новый элемент
{
    Orderedmap<string, int> map;
    map["newkey"] = 42;

    int* value = map.Find("newkey");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(42, *value);
}

TEST(OrderedMap, can_get_size)
// Проверяет корректность подсчёта количества элементов
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
// Проверяет очистку
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
// Проверяет вставку и поиск элемента
{
    Unorderedmap<string, int> map;
    map.Insert("apple", 5);

    int* value = map.Find("apple");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(5, *value);
}

TEST(UnorderedMap, find_returns_nullptr_for_nonexistent_key)
// Проверяет поиск несуществующего ключа
{
    Unorderedmap<string, int> map;
    map.Insert("apple", 5);

    int* value = map.Find("banana");
    EXPECT_EQ(nullptr, value);
}

TEST(UnorderedMap, can_update_existing_key)
// Проверяет обновление значения
{
    Unorderedmap<string, int> map;
    map.Insert("apple", 5);
    map.Insert("apple", 10);

    int* value = map.Find("apple");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(10, *value);
}

TEST(UnorderedMap, can_delete_existing_key)
// Проверяет удаление элемента
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
// Проверяет, что при удалении несуществующего ключа выбрасывается исключение
{
    Unorderedmap<string, int> map;
    map.Insert("apple", 5);

    ASSERT_ANY_THROW(map.Delete("banana"));
}

TEST(UnorderedMap, operator_brackets_creates_new_element)
// Проверяет, что оператор [] создаёт новый элемент
{
    Unorderedmap<string, int> map;
    map["newkey"] = 42;

    int* value = map.Find("newkey");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(42, *value);
}

TEST(UnorderedMap, can_get_size)
// Проверяет корректность подсчёта количества элементов
{
    Unorderedmap<string, int> map;
    EXPECT_EQ(0, map.Count());

    map.Insert("apple", 5);
    map.Insert("banana", 3);
    EXPECT_EQ(2, map.Count());
}

//BINARYTREE

TEST(BinaryTree, can_insert_and_find_element)
// Проверяет вставку и поиск элемента
{
    Binarytree<string, int> tree;
    tree.Insert("apple", 5);

    int* value = tree.Find("apple");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(5, *value);
}

TEST(BinaryTree, find_returns_nullptr_for_nonexistent_key)
// Проверяет поиск несуществующего ключа
{
    Binarytree<string, int> tree;
    tree.Insert("apple", 5);

    int* value = tree.Find("banana");
    EXPECT_EQ(nullptr, value);
}

TEST(BinaryTree, can_update_existing_key)
// Проверяет обновление значения
{
    Binarytree<string, int> tree;
    tree.Insert("apple", 5);
    tree.Insert("apple", 10);

    int* value = tree.Find("apple");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(10, *value);
}

TEST(BinaryTree, can_delete_leaf_node)
// Проверяет удаление листового узла
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
// Проверяет удаление узла с двумя детьми
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
// Проверяет, что оператор [] создаёт новый элемент
{
    Binarytree<string, int> tree;
    tree["newkey"] = 42;

    int* value = tree.Find("newkey");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(42, *value);
}

TEST(BinaryTree, can_get_size)
// Проверяет корректность подсчёта количества элементов
{
    Binarytree<string, int> tree;
    EXPECT_EQ(0, tree.Count());

    tree.Insert("apple", 5);
    tree.Insert("banana", 3);
    EXPECT_EQ(2, tree.Count());
}

TEST(BinaryTree, can_clear_tree)
// Проверяет очистку дерева
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
// Проверяет вставку и поиск элемента
{
    ChainHashTable<string, int> ht;
    ht.Insert("apple", 5);

    int* value = ht.Find("apple");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(5, *value);
}

TEST(ChainHashTable, find_returns_nullptr_for_nonexistent_key)
// Проверяет поиск несуществующего ключа
{
    ChainHashTable<string, int> ht;
    ht.Insert("apple", 5);

    int* value = ht.Find("banana");
    EXPECT_EQ(nullptr, value);
}

TEST(ChainHashTable, can_update_existing_key)
// Проверяет обновление значения
{
    ChainHashTable<string, int> ht;
    ht.Insert("apple", 5);
    ht.Insert("apple", 10);

    int* value = ht.Find("apple");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(10, *value);
}

TEST(ChainHashTable, can_delete_existing_key)
// Проверяет удаление элемента
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
// Проверяет, что при удалении несуществующего ключа выбрасывается исключение
{
    ChainHashTable<string, int> ht;
    ht.Insert("apple", 5);

    ASSERT_ANY_THROW(ht.Delete("banana"));
}

TEST(ChainHashTable, operator_brackets_creates_new_element)
// Проверяет, что оператор [] создаёт новый элемент
{
    ChainHashTable<string, int> ht;
    ht["newkey"] = 42;

    int* value = ht.Find("newkey");
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(42, *value);
}

TEST(ChainHashTable, can_get_size)
// Проверяет корректность подсчёта количества элементов
{
    ChainHashTable<string, int> ht;
    EXPECT_EQ(0, ht.count());

    ht.Insert("apple", 5);
    ht.Insert("banana", 3);
    EXPECT_EQ(2, ht.count());
}

TEST(ChainHashTable, can_clear_table)
// Проверяет очистку таблицы
{
    ChainHashTable<string, int> ht;
    ht.Insert("apple", 5);
    ht.Insert("banana", 3);
    ht.Clear();

    EXPECT_EQ(0, ht.count());
    EXPECT_TRUE(ht.isempty());
}