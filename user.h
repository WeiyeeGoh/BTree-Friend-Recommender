#ifndef USER_H
#define USER_H
#include<iostream>
#include<string>

class User
{
  public :

    User(int permNumber, std::string name, std::string genre1, std::string genre2);

    int getPerm(){return permNumber;};
    std::string getName(){return name;};
    std::string getGenre1(){return genre1;};
    std::string getGenre2(){return genre2;};
    void print();

  private :
    int permNumber ; // un ique i d
    std::string name ; // name o f t h e per s on
    std::string genre1 ; // f a v o r i t e movie gen re
    std::string genre2 ; // second f a v o r i t e movie gen re
} ;

#endif