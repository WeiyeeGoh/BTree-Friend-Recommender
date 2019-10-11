//user .cpp
#include <iostream>
#include "user.h"

User::User(int permNumber, std::string name, std::string genre1, std::string genre2){
  this->permNumber=permNumber;
  this->name=name;
  this->genre1=genre1;
  this->genre2=genre2;
}

void User::print() {
  std::cout << "-----------USER----------" << std::endl;
	std::cout << "Perm:  " << permNumber << "" << std::endl;
	std::cout << "Name: " << name << std::endl;
	std::cout << "Genre 1: " << genre1 << std::endl;
	std::cout << "Genre 2: " << genre2 << std::endl;
  std::cout <<"\n";
}
