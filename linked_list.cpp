#include <stdexcept>
#include "node.h"

/* Templated implementation of a linked list. This list is NOT thread-safe. */
template <typename V>
class LinkedList {
  Node<V> *head = NULL;
  Node<V> *tail = NULL;
  size_t length = 0;

  public:
    /* Adds a value at the end of the list. */
    void append(V value) {
      Node<V> *newNode = new Node<V>(value, tail, NULL);
      if (tail != NULL) {
        tail->next = newNode;
      }
      if (head == NULL) {
        head = newNode;
      }
      tail = newNode;
      ++length;
    }

    /* Returns the value at the specified index (0-based). */
    V at(int index) {
      checkIndexInRange(index);
      Node<V> *node = findNodeAt(index);
      return node->data;
    }

    /* Clears all values out of the list. */
    void clear() {
      if (length == 0) {
        return;
      }

      Node<V> *theNode = head;
      Node<V> *nextNode = theNode->next;
      while (theNode != NULL) {
        delete theNode;
        theNode = nextNode;
        if (theNode != NULL) {
          nextNode = theNode->next;
        } else {
          nextNode = NULL;
        }
      }

      head =
        tail = NULL;
      length = 0;
    }

    /* Returns the number of values stored in the list. */
    size_t count() {
      return length;
    }

    /* Returns the index of the first node that has a value matching the specified entry, or -1 if the value is not found. */
    int find(V value) {
      Node<V> *theNode = head;
      int index = 0;

      while (theNode != NULL && theNode->data != value) {
        theNode = theNode->next;
        ++index;
      }

      if (theNode == NULL) {
        return -1;
      }

      return index;
    }

    /* Returns the first value in the list. */
    V first() {
      if (length == 0) {
        throw std::range_error("Cannot get first value from empty list");
      }
      return head->data;
    }

    /* Adds a value at the beginning of the list, before any existing first value. */
    void insert(V value) {
      Node<V> *newNode = new Node<V>(value, NULL, head);
      if (head != NULL) {
        head->previous = newNode;
      }
      if (tail == NULL) {
        tail = newNode;
      }
      head = newNode;
      ++length;
    }
    
    /* Inserts a value at the specified index (0-based) in the list, shifting the existing record (if any) at that location. */
    void insertAt(V value, int index) {
      if (index == 0) {
        insert(value);
        return;
      }
       if (index == length) {
        append(value);
        return;
      }

      checkIndexInRange(index);
      Node<V> *next = findNodeAt(index);
      Node<V> *newNode = new Node<V>(value, next->previous, next);
      if (next->previous != NULL) {
        next->previous->next = newNode;
      }
      next->previous = newNode;
      ++length;
    }

    /* Returns the last value in the list. */
    V last() {
      if (length == 0) {
        throw std::range_error("Cannot get last value from empty list");
      }
      return tail->data;
    }

    /* Removes the first occurrence of the specified value from the list. */
    void remove(V value) {
      Node<V> *theNode = findNode(value);
      if (theNode != NULL) {
        if (theNode->previous != NULL) {
          theNode->previous->next = theNode->next;
        }
        if (head == theNode) {
          head = head->next;
        }
        if (theNode->next != NULL) {
          theNode->next->previous = theNode->previous;
        }
        if (tail == theNode) {
          tail = theNode->previous;
        }
        delete theNode;
        --length;
      }
    }

    /* Removes the value at the specified index of the list. */
    void removeAt(int index) {
      checkIndexInRange(index);

      Node<V> *theNode = findNodeAt(index);
      if (theNode->previous != NULL) {
        theNode->previous->next = theNode->next;
      }
      if (theNode->next != NULL) {
        theNode->next->previous = theNode->previous;
      }
      if (index == 0) {
        tail = theNode->next;
      }
      if (index == length - 1) {
        head = theNode->previous;
      }

      delete theNode;
      --length;
    }

  private:
    /* Determines in the specified index is within the bounds of the list - 0 (inclusive) to length (exclusive). */
    void checkIndexInRange(int index) {
      if (index < 0) {
        throw std::range_error("Index cannot be negative");
      }

      if (index >= length) {
        throw std::range_error("Index past end of list");
      }
    }

    /* Finds the node containing the first occurrence of the specified value. Returns NULL if value is not found in list. */
    Node<V> *findNode(V value) {
      for (Node<V> *theNode = head; theNode != NULL; theNode = theNode->next) {
        if (theNode->data == value) {
          return theNode;
        }
      }

      return NULL;
    }

    /* Finds the node at the specified index. The caller is expected to check the specified index against the bounds. */
    Node<V> *findNodeAt(int index) {
      if (index == 0) {
        return head;
      }

      if (index == length - 1) {
        return tail;
      }

      if (index < length/2) {
        return forwardFindNodeAt(index);
      }

      return reverseFindNodeAt(index);
    }

    /* Finds the node at the specified index by stepping forwards from the beginning of the list. */
    Node<V> *forwardFindNodeAt(int index) {
      Node<V> *theNode = head;

      for (int i = 0; i < index; ++i) {
        theNode = theNode->next;
      }

      return theNode;
    }

    /* Finds the node at the specified index by stepping backwards from the end of the list. */
    Node<V> *reverseFindNodeAt(int index) {
      Node<V> *theNode = tail;

      for (int i = length - 1; i > index; --i) {
        theNode = theNode->previous;
      }

      return theNode;
    }
};
