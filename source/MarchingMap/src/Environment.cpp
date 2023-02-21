#include"Environment.hpp"

Environment::Environment(int SQUARES_WIDTH_, int SQUARES_HEIGHT_)
{
	SQUARES_WIDTH = SQUARES_WIDTH_;
	SQUARES_HEIGHT = SQUARES_HEIGHT_;

	NODES_WIDTH = SQUARES_WIDTH + 1;
	NODES_HEIGHT = SQUARES_HEIGHT + 1;

	for (int i = 0; i < SQUARES_HEIGHT; i++)
	{
		for (int j = 0; j < SQUARES_WIDTH; j++)
		{
			Square* sq = new Square(j, i);
			squares.push_back(sq);
		}
	}

	nM = NodeMap(NODES_WIDTH, NODES_HEIGHT);
}

Environment::~Environment() {
	while (!squares.empty()) {
		delete squares.back();
		squares.pop_back();
	}

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			delete[] squareCombs[i][j];
		}
		delete[] squareCombs[i];
	}
	delete[] squareCombs;

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			delete[] outLineCombs[i][j];
		}
		delete[] outLineCombs[i];
	}
	delete[] outLineCombs;
}

void Environment::GenerateNodes() {
	nM.GenerateNodeMap();
	nM.PrintMap(0,0);
	while (nM.MakePaths()) {}
	nM.SetRegionNumbers();
	nM.PrintMap(0,0);
}

void Environment::MarchAllSquares()
{
	uniqueExteriorLines.clear();

	for (int i = 0; i < SQUARES_HEIGHT; i++)
	{
		for (int j = 0; j < SQUARES_WIDTH; j++)
		{
			Square* s = squares[i * SQUARES_WIDTH + j];
			s->MarchSquare(nM.nodes);
			if (s->code != 0)
			{
				if (s->numOutVerts > 0) {
					for (int f = 0; f < s->numOutVerts; f++)
					{
						uniqueExteriorLines.push_back(s->outVerts.at(f));
						wallCodes.push_back(s->code);
					}
				}
			}
		}
	}
}

int Environment::GetCode(int i, int j) {
	return squares[i * SQUARES_WIDTH + j]->code;
}

std::vector<float> Environment::IndexAtPos(float x, float y, int mapSize) {
	return std::vector<float>{(-y/mapSize+1)/2*SQUARES_HEIGHT, (x/mapSize+1)/2*SQUARES_WIDTH};
}

bool Environment::PositionInAir(float i, float j) {
	int iFloor = i;
	int jFloor = j;
	float leftOverI = i-iFloor;
	float leftOverJ = j-jFloor;
	int code = squares[round(iFloor) * SQUARES_WIDTH + round(jFloor)]->code;
	//std::cout << code << "    " << j << " " << leftOverJ << "    " << i << " " << leftOverI << "\n";

	switch (code)
	{
	case 0:
		return true;
	case 1:
		return leftOverJ+leftOverI > .5+diagBuffer;
	case 2:
		return (1-leftOverJ)+leftOverI > .5+diagBuffer;
	case 3:
		return leftOverI > .5+buffer;
	case 4:
		return leftOverJ+(1-leftOverI) > .5+diagBuffer;
	case 5:
		return leftOverJ > .5+buffer;
	case 6:
		return (1-leftOverJ)+leftOverI > .5+diagBuffer && leftOverJ+(1-leftOverI) > .5+diagBuffer;
	case 7:
		return (1-leftOverJ)+(1-leftOverI) < .5-diagBuffer;
	case 8:
		return (1-leftOverJ)+(1-leftOverI) > .5+diagBuffer;
	case 9:
		return leftOverJ+leftOverI > .5+diagBuffer && (1-leftOverJ)+(1-leftOverI) > .5+diagBuffer;
	case 10:
		return leftOverJ < .5-buffer;
	case 11:
		return leftOverJ+(1-leftOverI) < .5-diagBuffer;
	case 12:
		return leftOverI < .5-buffer;
	case 13:
		return (1-leftOverJ)+leftOverI < .5-diagBuffer;
	case 14:
		return leftOverJ+leftOverI < .5-diagBuffer;
	case 15:
		return false;
	default:
		return true;
	}
}

std::vector<float> Environment::WallIntersection(float i, float j, float iTarget, float jTarget) {
	return std::vector<float>{10,10};
}