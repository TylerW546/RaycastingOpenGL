#pragma once

#ifndef TRISSQUARES_H
#define TRISSQUARES_H

#include <vector>

using namespace std;

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
	void MarchSquare(std::vector<std::vector<int>> nodes, int*** squareCombs, int*** outLineCombs, int VERTS_WIDTH);
	vector<int>* GetOutlineLines();

	int numLines;
	int numOutVerts;
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