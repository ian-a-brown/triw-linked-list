template<typename V> struct Node {
  V data;
  Node *previous;
  Node *next;

  Node(V value, Node *before, Node *after): data(value), previous(before), next(after) {}
};
