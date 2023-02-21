#include<iostream>

#include"Square.hpp"

using namespace std;

Square::Square()
{

}

Square::Square(float c1x, float c1y)
{
	position_ = {c1x, c1y};
}

Square::~Square()
{
	outVerts.clear();
}

void Square::MarchSquare(std::vector<std::vector<int>> nodes)
{
	int j = (int)position_.x;
	int i = (int)position_.y;

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
		if (code != 15)
		{
			numLines = outLineCombsArray[code][0][0];
			numOutVerts = numLines * 2;

			for (int i = 1; i <= numLines; i++)
			{
				outVerts.push_back(position_ + Point<float>{(float)outLineCombsArray[code][i][0]/2.0f, (float)outLineCombsArray[code][i][1]/2.0f});
				outVerts.push_back(position_ + Point<float>{(float)outLineCombsArray[code][i][2]/2.0f, (float)outLineCombsArray[code][i][3]/2.0f});
			}
		}
	}
}
