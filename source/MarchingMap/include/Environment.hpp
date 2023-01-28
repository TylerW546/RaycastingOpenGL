#pragma once

#ifndef Environment_H
#define Environment_H

#include<iostream>
#include<set>
#include<stdlib.h>
#include<vector>

#include"TrisSquares.hpp"
#include"NodeMap.hpp"

class Environment
{
public:
	Environment(int SQUARES_WIDTH_, int SQUARES_HEIGHT_);
	~Environment();
	void GenerateVertices();

	void GenerateNodes();
	void SetDrawingNodes();
	void RotateSelected(int n);

	void SetUpCombs();

	void MarchAllSquares();

	int GetCode(int i, int j);
	bool PositionInAir(float x, float y);

	void ToggleMesh();
	void ToggleLines();
	void ToggleExteriors();
	void ToggleUniques();

	void ToggleOns();
	void ToggleOffs();

	void RegenerateShaders();
	void GenerateShaders();
	void Draw();
	void ShaderClean();

	void Destroy();

	std::vector<float> vertices;

	NodeMap nM;

	int*** squareCombs;
	int*** outLineCombs;

	std::vector<int> mainMesh;
	//std::vector<int> allLines;
	std::vector<int> exteriorLines;
	std::vector<int> uniqueExteriorLines;
	std::vector<int> wallCodes;

	int SQUARES_WIDTH;
	int SQUARES_HEIGHT;

	int NODES_WIDTH;
	int NODES_HEIGHT;

	int VERTS_WIDTH;
	int VERTS_HEIGHT;

	std::vector<Square*> squares;
};

#endif