#include<iostream>

#include"TrisSquares.hpp"

using namespace std;



Triangle::Triangle()
{

}

Triangle::Triangle(int v1_, int v2_, int v3_)
{
	v1 = v1_;
	v2 = v2_;
	v3 = v3_;
}

void Triangle::SetVerts(int v1_, int v2_, int v3_)
{
	v1 = v1_;
	v2 = v2_;
	v3 = v3_;
}

Square::Square()
{

}

Square::Square(int c1_, int c4_)
{
	c1 = c1_;
	c2 = c1_ + 2;
	c3 = c4_ - 2;
	c4 = c4_;
}

Square::~Square()
{
	while (!tris.empty()) {
		delete tris.back();
		tris.pop_back();
	}
	outVerts.clear();
}

void Square::SetCorners(int c1_, int c4_)
{
	c1 = c1_;
	c2 = c1_ + 2;
	c3 = c4_ - 2;
	c4 = c4_;
}

void Square::MarchSquare(std::vector<std::vector<int>> nodes, int VERTS_WIDTH)
{
	int j = c1 / 2 % VERTS_WIDTH;
	int i = (c1 / 2 - j) / VERTS_WIDTH;

	code = 0;
	if (nodes[i][j] == 0)
		code += 1;
	if (nodes[i][j + 1] == 0)
		code += 2;
	if (nodes[i + 1][j] == 0)
		code += 4;
	if (nodes[i + 1][j + 1] == 0)
		code += 8;

	if (code != 0)
	{
		numTris = squareCombsArray[code][0][0];
		for (int tri = 1; tri <= numTris; tri++)
		{
			int q = c1 + squareCombsArray[code][tri][0] + VERTS_WIDTH * squareCombsArray[code][tri][1];
			int w = c1 + squareCombsArray[code][tri][2] + VERTS_WIDTH * squareCombsArray[code][tri][3];
			int e = c1 + squareCombsArray[code][tri][4] + VERTS_WIDTH * squareCombsArray[code][tri][5];
			Triangle* x = new Triangle(q, w, e);
			tris.push_back(x);
		}


		if (code != 15)
		{
			numLines = outLineCombsArray[code][0][0];
			numOutVerts = numLines * 2;

			for (int i = 1; i <= numLines; i++)
			{
				outVerts.push_back(c1 + outLineCombsArray[code][i][0] + VERTS_WIDTH * outLineCombsArray[code][i][1]);
				outVerts.push_back(c1 + outLineCombsArray[code][i][2] + VERTS_WIDTH * outLineCombsArray[code][i][3]);
			}
		}
	}
}

vector<int>* Square::GetOutlineLines()
{
	vector<int> out;
	out.push_back(tris[0]->v1);
	out.push_back(tris[0]->v2);
	out.push_back(tris[0]->v3);
	for (int i = 1; i < numTris; i++)
	{
		out.push_back(tris[i]->v3);
	}
	return &out;
}