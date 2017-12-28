#pragma once
#include"Util.h"
#include"myNode.h"
class Station
{
private:
	int _id;
	static int _count;

	string _no;

	vector<myNode*> _nodeList;

public:
	Station(string no);

	void pushNode(myNode* node) { _nodeList.push_back(node); }
	vector<myNode*> getNodeList() { return _nodeList; }

	void setNodeId(int startId);
	void sortNode() { sort(_nodeList.begin(), _nodeList.end(), myNode::cmpByTime); }
	void mergeNode();

	myNode* getCountNode();

	void print();
	void printNodeList();

};

