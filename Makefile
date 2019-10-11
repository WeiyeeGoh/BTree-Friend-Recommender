all: FriendRec

FriendRec: main.cpp recommender.cpp recommender.h user.h user.cpp adjacencyList.cpp adjacencyList.h
	g++ -std=c++11 main.cpp recommender.cpp user.cpp adjacencyList.cpp usertree.cpp -o FriendRec

clean:
	rm FriendRec
