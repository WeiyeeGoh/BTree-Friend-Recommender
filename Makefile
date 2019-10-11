all: FriendRec

FriendRec: main.cpp recommender.cpp recommender.h user.h user.cpp adjacencyList.cpp adjacencyList.h
	g++ -std=c++11 main.cpp recommender.cpp user.cpp adjacencyList.cpp -o FriendRec

test: tester.cpp recommender.cpp recommender.h user.h user.cpp adjacencyList.cpp adjacencyList.h usertree.h usertree.cpp
		g++ -Wall -std=c++11 tester.cpp usertree.cpp recommender.cpp user.cpp adjacencyList.cpp -o tester


clean:
	rm FriendRec
