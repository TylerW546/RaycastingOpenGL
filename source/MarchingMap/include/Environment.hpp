#pragma once

#ifndef Environment_H
#define Environment_H

#include<iostream>
#include<set>
#include<stdlib.h>
#include<vector>

#include"Square.hpp"
#include"NodeMap.hpp"

const float wallLinearizations[16][8] = {
	{}, // 0
	{0,0.5,0.5,0}, // 1
	{0.5,0,1,0.5}, // 2
	{0,0.5,1,0.5}, // 3
	{0.5,1,0,0.5}, // 4
	{0.5,1,0.5,0}, // 5
	{0.5,0,1,0.5,0.5,1,0,0.5}, // 6
	{0.5,1,1,0.5}, // 7
	{1,0.5,0.5,1}, // 8
	{1,0.5,0.5,1,0,0.5,0.5,0}, // 9
	{0.5,0,0.5,1}, // 10
	{0,0.5,0.5,1}, // 11
	{1,0.5,0,0.5}, // 12
	{1,0.5,0.5,0}, // 13
	{0.5,0,0,0.5}, // 14
	{},
};

class Environment
{
public:
	Environment(int SQUARES_WIDTH_, int SQUARES_HEIGHT_);
	~Environment();

	void GenerateNodes();
	void SetDrawingNodes();
	void RotateSelected(int n);

	void SetUpCombs();

	void MarchAllSquares();

	int GetCode(int i, int j);
	std::vector<float> IndexAtPos(float x, float y, int mapSize);
	bool PositionInAir(float x, float y);
	std::vector<float> WallIntersection(float i, float j, float iTarget, float jTarget);

	void Destroy();

	const float buffer = .1; // Multiply this by root 2 for diagonal walls
	const float diagBuffer = buffer*sqrt(2);

	std::vector<float> vertices;

	NodeMap nM;

	int*** squareCombs;
	int*** outLineCombs;

	std::vector<Point<float>> uniqueExteriorLines;
	std::vector<int> wallCodes;

	int SQUARES_WIDTH;
	int SQUARES_HEIGHT;

	int NODES_WIDTH;
	int NODES_HEIGHT;

	std::vector<Square*> squares;
};

#endif