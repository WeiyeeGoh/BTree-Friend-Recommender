#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <utility>
#include "user.h"
#include "usertree.h"
#include "adjacencyList.h"
#include <algorithm>


//#include "usertree.cpp"
class recommender{
public:
  void insertIntoAdjList(int a, int b);
  void insertUser(User* u, int i);
  User* findUserInTree(int perm);
  void recommendFriends(int perm);
  void printFriends(int index);
  int findIndexFromTree(int perm);
  std::vector<int> findFriends(int perm);
  void updateFriends(int userPerm, int friendPerm);

private:
  adjacencyList alist;
  UserTree userTree;
  void DFS(int perm, std::pair<std::string, std::string> genres, std::unordered_set<int> &visited, std::vector<int> friends);
  bool genreMatcher(std::pair<std::string, std::string> genres, std::string g1, std::string g2);

};
