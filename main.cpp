#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "user.h"
#include "usertree.h"

int main()
{
	
	/*
	
	//User tempUser(1, "jon", "adventure", "scifi");
	//tempUser.print();
	
	std::vector<User*> user_list;

  	std::ifstream myfile;
	//myfile.open(filename.c_str());
	myfile.open("sample.txt");
	std::string word;
	while(!myfile.eof()) {
		myfile >> word;
		if (myfile.eof()) break;
		
		std::vector<std::string> word_split;
		std::string tword = "";
		std::string tchar = "";
		std::string user_info[4];

		//count to 4. 0 is perm, 1 is name, 2 is genre1, 3 is genre2
		int count = 0;
		
		for(int i = 0; i < word.length(); i++) {
			tchar = "";
			tchar += word[i];

			if(tchar == ";") {
				//std::cout << tword << std::endl;

				if(count < 4) {
					user_info[count] = tword;
				}
				count++;
				tword = "";
			} else {
				tword += tchar;
			}
		}


		std::stringstream ss;
		int permNum;
		ss << user_info[0];
		ss >> permNum;

		User* userPtr = new User(permNum, user_info[1], user_info[2], user_info[3]);
		userPtr->print();
		user_list.push_back(userPtr);

	}
	myfile.close();
	*/

	UserTree tree;
	User* userPtr1 = new User(30, "weiyee", "scifi", "adventure");
	User* userPtr2 = new User(40, "jon", "scifi", "adventure");
	User* userPtr3 = new User(60, "Amanda", "scifi", "adventure");
	User* userPtr4 = new User(80, "quinn", "scifi", "adventure");
	User* userPtr5 = new User(100, "quinn", "scifi", "adventure");
	User* userPtr6 = new User(120, "quinn", "scifi", "adventure");
	User* userPtr7 = new User(166, "quinn", "scifi", "adventure");
	User* userPtr8 = new User(179, "quinn", "scifi", "adventure");
	User* userPtr9 = new User(209, "quinn", "scifi", "adventure");
	User* userPtr10 = new User(251, "quinn", "scifi", "adventure");
	User* userPtr11 = new User(333, "quinn", "scifi", "adventure");
	User* userPtr12 = new User(357, "quinn", "scifi", "adventure");
	User* userPtr13 = new User(411, "quinn", "scifi", "adventure");
	User* userPtr14 = new User(433, "quinn", "scifi", "adventure");
	User* userPtr15 = new User(444, "quinn", "scifi", "adventure");
	User* userPtr16 = new User(478, "quinn", "scifi", "adventure");
	User* userPtr17 = new User(501, "quinn", "scifi", "adventure");
	User* userPtr18 = new User(511, "quinn", "scifi", "adventure");
	User* userPtr19 = new User(555, "quinn", "scifi", "adventure");
	User* userPtr20 = new User(577, "quinn", "scifi", "adventure");
	User* userPtr21 = new User(599, "quinn", "scifi", "adventure");
	User* userPtr22 = new User(622, "quinn", "scifi", "adventure");


	
	/*
	tree.insertItem(userPtr1, 10);
	tree.insertItem(userPtr2, 10);
	tree.insertItem(userPtr3, 10);
	tree.insertItem(userPtr4, 10);
	tree.insertItem(userPtr5, 10);
	tree.insertItem(userPtr6, 10);
	tree.insertItem(userPtr7, 10);
	tree.insertItem(userPtr8, 10);
	tree.insertItem(userPtr9, 10);
	tree.insertItem(userPtr10, 10);
	tree.insertItem(userPtr11, 10);
	tree.insertItem(userPtr12, 10);
	tree.insertItem(userPtr13, 10);
	tree.insertItem(userPtr14, 10);
	tree.insertItem(userPtr15, 10);
	tree.insertItem(userPtr16, 10);
	tree.insertItem(userPtr17, 10);
	tree.insertItem(userPtr18, 10);
	tree.insertItem(userPtr19, 10);
	tree.insertItem(userPtr20, 10);
	tree.insertItem(userPtr21, 10);
	tree.insertItem(userPtr22, 10);
	*/

	tree.insertItem(userPtr12, 10);
	tree.insertItem(userPtr13, 16);
	tree.insertItem(userPtr10, 8);
	tree.insertItem(userPtr11, 9);
	tree.insertItem(userPtr15, 25);
	//tree.insertItem(userPtr11, 10);
	//tree.insertItem(userPtr10, 10);
	//tree.insertItem(userPtr9, 10);
	//tree.insertItem(userPtr8, 10);
	//tree.insertItem(userPtr7, 10);
	//tree.insertItem(userPtr6, 10);
	//tree.insertItem(userPtr5, 10);
	//tree.insertItem(userPtr4, 10);
	//tree.insertItem(userPtr3, 10);
	//tree.insertItem(userPtr2, 10);
	//tree.insertItem(userPtr1, 10);

	
	tree.print();
	/*
	tree.printUser(30);
	tree.printUser(40);
	tree.printUser(50);
	tree.printUser(60);
	tree.printUser(70);
	tree.printUser(80);
	tree.printUser(90);
	tree.printUser(100);
	tree.printUser(120);
	tree.printUser(333);
	tree.printUser(444);
	*/



	return 0;
		
}
