#pragma once

#ifndef SQUARE_H
#define SQUARE_H

#include <vector>
#include <stdint.h>
#include <Util.hpp>

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

class Square
{
public:
	Square();
	Square(float c1x, float c1y);
	~Square();
	void MarchSquare(std::vector<std::vector<int>> nodes);

	int numLines = 0;
	int numOutVerts = 0;
	std::vector<Point<float>> outVerts;

	int code = 0;

	Point<float> position_;
};

#endif