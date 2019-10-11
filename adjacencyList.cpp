#include "adjacencyList.h"
#include <iostream>


void adjacencyList::insert(int userPerm, int friendPerm){

  for(unsigned int i =0; i<adjList.size(); i++){
    if(adjList[i]->perm==userPerm) {//user is already in the table yup
      Node* tmp = adjList[i];
      while(tmp->next!=NULL){
        tmp=tmp->next;
      }
      Node* n = new Node();
      n->next=NULL;
      n->perm=friendPerm;
      tmp->next=n;
      return;
    }
  }

  Node* userN = new Node();
  Node* friendN = new Node();
  friendN->perm=friendPerm;
  friendN->next=NULL;
  userN->perm=userPerm;
  userN->next=friendN;
  adjList.push_back(userN);

}

std::vector<int> adjacencyList::getFriends(int p){
  std::vector<int> f;

  Node* tmp = adjList[p]->next;
  while(tmp!=NULL){
    f.push_back(tmp->perm);
    tmp=tmp->next;
  }

  return f;
}

void adjacencyList::printList(){
  for(unsigned int i =0; i<adjList.size(); i++){
    Node* tmp =adjList[i];
    while(tmp!=NULL){
      if(tmp->next!=NULL)
        std::cout<<tmp->perm<<"->";
      else
        std::cout<<tmp->perm<<"\n";
      tmp=tmp->next;
    }
  }
}

void adjacencyList::printList(int perm){
  for(unsigned int i =0; i<adjList.size(); i++){

    Node* tmp =adjList[i];
    if(tmp->perm==perm){
      while(tmp!=NULL){
        if(tmp->next!=NULL)
          std::cout<<tmp->perm<<"->";
        else
          std::cout<<tmp->perm<<"\n";
        tmp=tmp->next;
      }
    }
  }
}

void adjacencyList::printIndex(int index){
  Node* tmp =adjList[index];
  std::cout<<tmp->perm<<" is friends with ";
  tmp=tmp->next;
  while(tmp!=NULL){
    if(tmp->next!=NULL)
      std::cout<<tmp->perm<<",";
    else
      std::cout<<tmp->perm<<"\n";
    tmp=tmp->next;
  }
}
