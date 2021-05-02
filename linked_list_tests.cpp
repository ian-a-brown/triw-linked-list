#include <stdexcept>
#include "linked_list.cpp"
#include <gtest/gtest.h>

TEST(LinkedList, Template) {
  LinkedList<int> *primitiveList = new LinkedList<int>();
  int value = 666;
  primitiveList->append(value);
  ASSERT_EQ(primitiveList->first(), value);
  ASSERT_EQ(primitiveList->find(value), 0);

  LinkedList<char *> *pointerList = new LinkedList<char *>();
  char *pointer = new char[6];
  pointerList->insert(pointer);
  ASSERT_EQ(pointerList->last(), pointer);
  ASSERT_EQ(pointerList->find(pointer), 0);

  class TestClass {
    int value;

    public:
      TestClass(int i) : value(i) {}
  };
  LinkedList<TestClass *> *classList = new LinkedList<TestClass *>();
  TestClass *testClass = new TestClass(555);
  classList->append(testClass);
  ASSERT_EQ(classList->at(0), testClass);
  ASSERT_EQ(classList->find(testClass), 0);
}

TEST(LinkedList, Append) {
  LinkedList<int> *list = new LinkedList<int>();

  list->append(5);
  ASSERT_EQ(list->count(), 1);
  ASSERT_EQ(list->first(), 5);
  ASSERT_EQ(list->last(), 5);

  list->append(6);
  ASSERT_EQ(list->count(), 2);
  ASSERT_EQ(list->first(), 5);
  ASSERT_EQ(list->last(), 6);
};

TEST(LinkedList, At) {
  LinkedList<int> *list = new LinkedList<int>();
  ASSERT_EQ(list->count(), 0);

  list->append(3);
  list->append(1);
  list->append(4);
  list->append(2);
  ASSERT_EQ(list->count(), 4);

  ASSERT_THROW(list->at(-1), std::range_error);
  ASSERT_THROW(list->at(4), std::range_error);
  ASSERT_EQ(list->at(2), 4);
  ASSERT_EQ(list->at(0), 3);
  ASSERT_EQ(list->at(3), 2);
  ASSERT_EQ(list->at(1), 1);

  list->insertAt(5, 2);
  ASSERT_EQ(list->at(0), 3);
  ASSERT_EQ(list->at(1), 1);
  ASSERT_EQ(list->at(2), 5);
  ASSERT_EQ(list->at(3), 4);
  ASSERT_EQ(list->at(4), 2);
}

TEST(LinkedList, Clear) {
  LinkedList<int> *list = new LinkedList<int>();
  ASSERT_EQ(list->count(), 0);

  list->clear();
  ASSERT_EQ(list->count(), 0);

  list->append(3);
  list->append(1);
  list->append(4);
  list->append(2);
  ASSERT_EQ(list->count(), 4);

  list->clear();
  ASSERT_EQ(list->count(), 0);
  ASSERT_THROW(list->first(), std::range_error);
  ASSERT_THROW(list->last(), std::range_error);
}

TEST(LinkedList, Find) {
  LinkedList<int> *list = new LinkedList<int>();
  ASSERT_EQ(list->count(), 0);

  list->append(3);
  list->append(1);
  list->append(4);
  list->append(2);
  ASSERT_EQ(list->count(), 4);

  ASSERT_EQ(list->find(5), -1);
  ASSERT_EQ(list->find(4), 2);
  ASSERT_EQ(list->find(3), 0);
  ASSERT_EQ(list->find(2), 3);
  ASSERT_EQ(list->find(1), 1);

  list->insertAt(5, 3);
  ASSERT_EQ(list->find(5), 3);
  ASSERT_EQ(list->find(2), 4);
}

TEST(LinkedList, Insert) {
  LinkedList<int> *list = new LinkedList<int>();
  ASSERT_EQ(list->count(), 0);

  list->insert(97);
  ASSERT_EQ(list->count(), 1);
  ASSERT_EQ(list->first(), 97);
  ASSERT_EQ(list->last(), 97);

  list->insert(96);
  ASSERT_EQ(list->count(), 2);
  ASSERT_EQ(list->first(), 96);
  ASSERT_EQ(list->last(), 97);
};

TEST(LinkedList, InsertAt) {
  LinkedList<int> *list = new LinkedList<int>();
  ASSERT_EQ(list->count(), 0);

  EXPECT_THROW({ list->insertAt(99, -1); }, std::range_error);
  EXPECT_THROW({ list->insertAt(103, 3); }, std::range_error);

  list->insertAt(102, 0);
  ASSERT_EQ(list->count(), 1);
  ASSERT_EQ(list->first(), 102);
  ASSERT_EQ(list->last(), 102);

  list->insertAt(100, 0);
  ASSERT_EQ(list->count(), 2);
  ASSERT_EQ(list->first(), 100);
  ASSERT_EQ(list->last(), 102);

  list->insertAt(101, 1);
  ASSERT_EQ(list->count(), 3);
  ASSERT_EQ(list->first(), 100);
  ASSERT_EQ(list->at(1), 101);
  ASSERT_EQ(list->last(), 102);
};

TEST(LinkedList, Remove) {
  LinkedList<int> *list = new LinkedList<int>();
  ASSERT_EQ(list->count(), 0);

  list->append(1);
  list->append(2);
  list->append(3);
  ASSERT_EQ(list->count(), 3);
 
  list->remove(0);
  ASSERT_EQ(list->count(), 3);
  ASSERT_EQ(list->first(), 1);
  ASSERT_EQ(list->at(1), 2);
  ASSERT_EQ(list->last(), 3);

  list->remove(2);
  ASSERT_EQ(list->count(), 2);
  ASSERT_EQ(list->first(), 1);
  ASSERT_EQ(list->last(), 3);

  list->insert(3);
  ASSERT_EQ(list->count(), 3);
  list->remove(3);
  ASSERT_EQ(list->count(), 2);
  ASSERT_EQ(list->first(), 1);
  ASSERT_EQ(list->last(), 3);
};

TEST(LinkedList, RemoveAt) {
  LinkedList<int> *list = new LinkedList<int>();
  ASSERT_EQ(list->count(), 0);

  list->append(1);
  list->append(2);
  list->append(3);
  ASSERT_EQ(list->count(), 3);

  EXPECT_THROW(list->removeAt(-1), std::range_error);
};