#pragma once

#ifndef NODEMAP_H
#define NODEMAP_H

using namespace std;

#include <stdlib.h>
#include <vector>
#include <iostream>

class NodeMap
{
public:
	NodeMap();
	NodeMap(int NODES_WIDTH, int NODES_HEIGHT);
	
	int GetSurroundingOnNodes(int i, int j);
	void SmoothMap();
	void GenerateNodeMap();

	void SetRegionNumbers();
	void Spread(int i, int j, int num);

	void PrintMap(int i, int j);

	int NODES_WIDTH;
	int NODES_HEIGHT;

	std::vector<std::vector<int>> nodes;
	std::vector<std::vector<int>> oldNodes;

	int maxRegionNum = 0;
};

#endif