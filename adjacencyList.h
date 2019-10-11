//.h
#include<vector>
#include<string>

struct Node{
  int perm;
  Node* next;
};

class adjacencyList{
public:
  void insert(int userPerm, int friendPerm);
  void printList();
  void printList(int perm);
  void printIndex(int index);
  std::vector<int> getFriends(int p);
private:
  std::vector<Node*> adjList;
};
