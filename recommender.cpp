//.cpp
#include "recommender.h"

void recommender::insertIntoAdjList(int a, int b){
  alist.insert(a,b);
}

void recommender::insertUser(User* u, int i){
  userTree.insertItem(u,i);
}

User* recommender::findUserInTree(int perm){
  return userTree.findUser(perm);
}

void recommender::printFriends(int index){
  alist.printIndex(index);
}
  int recommender::findIndexFromTree(int perm){
    return userTree.findIndex(perm);
}
std::vector<int> recommender::findFriends(int perm){
    return alist.getFriends(perm);
}
void recommender::updateFriends(int userPerm, int friendPerm){
  alist.insert(userPerm,friendPerm);
}
void recommender::DFS(int perm, std::pair<std::string, std::string> genres, std::unordered_set<int> &visited, std::vector<int> friends){
  User* u = findUserInTree(perm);
  if(visited.count(u->getPerm())<1){
    int uindex= findIndexFromTree(perm);
    std::vector<int> f = findFriends(uindex);
    visited.insert(perm);
    if(genreMatcher(genres,u->getGenre1(),u->getGenre2())){
      if(std::find(friends.begin(), friends.end(), u->getPerm()) == friends.end()) {
          u->print();
      }
    }
    for(auto i : f){
      DFS(i, genres, visited, friends);
    }
  }
}

bool recommender::genreMatcher(std::pair<std::string, std::string> genres, std::string g1, std::string g2 ){
  if(g1==genres.first || g1==genres.second)
    return true;
  if(g2==genres.first||g2==genres.second)
    return true;
}

void recommender::recommendFriends(int perm){
  std::unordered_set<int> visited;
  visited.insert(perm);
  User* u  = findUserInTree(perm);
  std::pair <std::string , std::string> genres (u->getGenre1(), u-> getGenre2());
  std::vector<int> f = findFriends( findIndexFromTree(perm));
  for(auto i : f){
    //visited.insert(i);
    DFS(i, genres, visited, f);
  }
  //std::cout<<"EVERYONE IS A FRIEND\n";
}
