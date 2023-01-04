#pragma once

#ifndef TRISSQUARES_H
#define TRISSQUARES_H


using namespace std;

class Triangle
{
public:
	Triangle();
	void SetVerts(int v1, int v2, int v3);

	int v1;
	int v2;
	int v3;
};


class Square
{
public:
	Square();
	void SetCorners(int c1_, int c4_);
	void MarchSquare(int** nodes, int*** squareCombs, int*** outLineCombs, int VERTS_WIDTH);
	int* GetOutlineLines();

	int numOutVerts;
	int* outVerts = new int[8];

	Triangle* tris = new Triangle[4];
	int numTris;
	uint8_t code = 0;

	int c1;
	int c2;
	int c3;
	int c4;
};

#endif