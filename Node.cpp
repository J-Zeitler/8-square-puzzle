#include "Node.h"
#include <cmath>

Node::Node(float g, Node *p, short *s) : G(g), parent(p)
{
	state = new short[9];
	for(short i = 0; i < 9; ++i)
	{
		state[i] = s[i];
	}
	calcZeroPos();
	calcH();
}

//this is a sneaky copy constructor
Node::Node(Node *N)
{
	state = new short[9];
	for(short i = 0; i < 9; ++i)
	{
		state[i] = N->state[i];
	}
	G = N->G + 1;
	parent = N;
	zeroPos = N->zeroPos;
	H = N->H;
}

Node::~Node(){
	delete state;
}

void Node::calcZeroPos()
{
	for(short i = 0; i < 9; ++i)
	{
		if(state[i] == 0) zeroPos = i;
	}
}

void Node::calcH()
{
	H = 0;

	for(short i = 0; i < 9; ++i)
	{
		switch(state[i])
		{
			case 0: break;
			case 1: 
				H += floor((float)i/3) + i%3;
				break;
			case 2:
				H += floor((float)i/3) + abs(i%3-1);
				break;
			case 3:
				H += floor((float)i/3) + abs(i%3-2);
				break;
			case 4:
				H += abs(floor((float)i/3)-1) + i%3;
				break;
			case 5:
				H += abs(floor((float)i/3)-1) + abs(i%3-1);
				break;
			case 6:
				H += abs(floor((float)i/3)-1) + abs(i%3-2);
				break;
			case 7:
				H += abs(floor((float)i/3)-2) + i%3;
				break;
			case 8:
				H += abs(floor((float)i/3)-2) + abs(i%3-1);
				break;
		}
	}
}

void Node::makeMove(short index)
{
	state[zeroPos] = state[index];
	state[index] = 0;
	zeroPos = index;
	calcH();
}

float Node::getF() { return G + H; }

short Node::getZeroPos() { return zeroPos; }

Node* Node::getParent() { return parent; }

//inserts the index of possible squares to move into v
void Node::getMoves(vector<short> &v)
{
	short lastMove = (parent) ? parent->state[zeroPos] : -1;

	for(short i = -3; i < 4; i += 2)
	{
		switch(zeroPos)
		{
		case 2:
		case 5:
			if(i == 1) 
				continue;
			break;
		case 3:
		case 6:
			if(i == -1) 
				continue;
			break;
		}
		if(zeroPos+i < 9 && zeroPos+i > -1 && state[zeroPos+i] != lastMove)
		{
			v.push_back(zeroPos+i);
		}
	}
}

void Node::setBetterPath(Node *N)
{
	G = N->G;
	parent = N->parent;
}

bool Node::finished()
{
	if(H == 0) return true;
	return false;
}

bool Node::operator== (Node *N)
{
	for (short i = 0; i < 9; ++i)
	{
		if(state[i] != N->state[i]) return false;
	}
	return true;
}

ostream& operator <<(ostream& os, const Node& N)
{
    for(char i = 0; i < 9; ++i)
	{
		if(i%3 == 0)
		{
			os << "\n\t";
		}
		os << N.state[i] << " ";
	}
	os << "\n";

    return os;
}
