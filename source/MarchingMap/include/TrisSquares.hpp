#pragma once

#ifndef TRISSQUARES_H
#define TRISSQUARES_H

#include <vector>
#include <stdint.h>

using namespace std;

const int outLineCombsArray[16][3][4] = {
	{{0}}, // 0
	{{1}, {0,1,1,0}}, // 1
	{{1}, {1,0,2,1}}, // 2
	{{1}, {0,1,2,1}}, // 3
	{{1}, {1,2,0,1}}, // 4
	{{1}, {1,2,1,0}}, // 5
	{{2}, {1,0,2,1}, {1,2,0,1}}, // 6 OLD: {{2}, {1,0,0,1}, {1,2,2,1}},
	{{1}, {1,2,2,1}}, // 7
	{{1}, {2,1,1,2}}, // 8
	{{2}, {2,1,1,2}, {0,1,1,0}}, // 9 OLD: {{2}, {0,1,1,2}, {2,1,1,0}},
	{{1}, {1,0,1,2}}, // 10
	{{1}, {0,1,1,2}}, // 11
	{{1}, {2,1,0,1}}, // 12
	{{1}, {2,1,1,0}}, // 13
	{{1}, {1,0,0,1}}, // 14
	{{0}}, // 15
};

class Triangle
{
public:
	Triangle();
	Triangle(int v1_, int v2_, int v3_);
	void SetVerts(int v1_, int v2_, int v3_);

	int v1;
	int v2;
	int v3;
};


class Square
{
public:
	Square();
	Square(int c1_, int c4_);
	~Square();
	void SetCorners(int c1_, int c4_);
	void MarchSquare(std::vector<std::vector<int>> nodes, int VERTS_WIDTH);
	vector<int>* GetOutlineLines();

	int numLines = 0;
	int numOutVerts = 0;
	std::vector<int> outVerts;

	std::vector<Triangle*> tris;
	int numTris;
	int code = 0;

	int c1;
	int c2;
	int c3;
	int c4;
};

#endif