#include <iostream>
#include "Node.h"
#include <vector>
#include <algorithm>

using namespace std;

bool sortingFun (Node *i,Node *j);
void solvePuzzle(vector<Node*> &openList, vector<Node*> &closedList);

int main()
{
	vector<Node*> openList;
	vector<Node*> closedList;

	short state[] = {
		0, 1, 3,
		2, 5, 8,
		7, 6, 4
	};

	Node startNode(0, NULL, state);
	openList.push_back(&startNode);

	cout << "Starting board:\n" << startNode << endl;

	short N = 0;

	for(short i = 0; i < 9; ++i)
	{
		if(state[i] == 0)
		{
			continue;
		}
		for(short j = i+1; j < 9; ++j)
		{
			if(state[i] > state[j] && state[j] != 0)
				N++;
		}
	}

	if(N%2 == 1)
		cout << "Solution is impossible." << endl;

	else
	{
		
		if(openList.back()->finished());
		else
		{
			solvePuzzle(openList, closedList);
		}
		vector<Node*> solution;
		Node *tmp = openList.back();
		solution.push_back(tmp);
		while(tmp = tmp->getParent())
			solution.push_back(tmp);

		reverse(solution.begin(),solution.end()); 

		cout << "Solution: " << endl;

		for(vector<Node*>::iterator it = solution.begin(); it < solution.end(); it++)
		{
			cout << *(*it) << endl;
		}

		cout << "Steps to solve = " << solution.size() - 1 << endl;
	}

	cin.get();

	return 0;
}

bool sortingFun (Node *i,Node *j)
{ 
	return (i->getF()<j->getF()); 
}

void solvePuzzle(vector<Node*> &openList, vector<Node*> &closedList)
{
	cout << "Solving ...\n\n";

	Node *current;
	bool foundBestRoute = false;
	vector<short> possibleMoves;

	while(!foundBestRoute)
	{		
		current = openList.back();
		closedList.push_back(current);
		openList.pop_back();

		possibleMoves.clear();
		current->getMoves(possibleMoves);

		for(vector<short>::iterator it = possibleMoves.begin(); it < possibleMoves.end(); it++)
		{
			Node *nextNode = new Node(current);
			nextNode->makeMove(*it);

			bool inList = false;
			for(vector<Node*>::iterator it2 = openList.begin(); it2 < openList.end(); it2++)
			{
				Node *nodeInList = *it2;
				if(*nodeInList == nextNode)
				{
					if(nodeInList->getF() > nextNode->getF())
					{
						nodeInList->setBetterPath(nextNode);
					}
					delete nextNode;
					inList = true;
					break;
				}
			}

			if(!inList)
			{
				openList.push_back(nextNode);
			}
		}
		sort(openList.rbegin(), openList.rend(), sortingFun);
		
		if(openList.back()->finished()) foundBestRoute = true;
	}
}