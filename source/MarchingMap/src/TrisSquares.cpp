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
}

void Square::SetCorners(int c1_, int c4_)
{
	c1 = c1_;
	c2 = c1_ + 2;
	c3 = c4_ - 2;
	c4 = c4_;
}

void Square::MarchSquare(std::vector<std::vector<int>> nodes, int*** squareCombs, int*** outLineCombs, int VERTS_WIDTH)
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
	
	std::cout<<code;

	int startVert = c1;
	if (code != 0)
	{
		numTris = squareCombs[code][0][0];
		std::cout<<" c1: " << c1 << "  tris -- " << numTris << " ";
		for (int tri = 1; tri <= numTris; tri++)
		{
			std::cout<<"pushing...";
			int q = c1 + squareCombs[code][tri][0];
			int w = c1 + squareCombs[code][tri][1];
			int e = c1 + squareCombs[code][tri][2];
			std::cout<<q<<"  "<<w<<"  "<<e;
			Triangle* x = new Triangle(q, w, e);
			tris.push_back(x);
			std::cout<<"...pushed";
		}


		if (code != 15)
		{
			numLines = outLineCombs[code][0][0];
			numOutVerts = numLines * 2;

			for (int i = 1; i <= numLines; i++)
			{
				outVerts.push_back(c1 + outLineCombs[code][i][0]);
				outVerts.push_back(c1 + outLineCombs[code][i][1]);
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