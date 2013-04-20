#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
	Node(float g, Node *p, short *s);
	Node::Node(Node *N);
	~Node(void);

	float getF();
	void getMoves(vector<short> &v);
	short getZeroPos();
	Node* getParent();
	void setBetterPath(Node *N);

	void makeMove(short s);
	void calcH();

	bool finished();
	
	bool operator== (Node *N);

	friend ostream& operator<<(ostream& os, const Node &n);

private:
	float G, H;
	short *state;
	Node *parent;
	short zeroPos;

	void calcZeroPos();
};

