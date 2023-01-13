#include"TrisSquares.hpp"
#include"Environment.hpp"

Environment::Environment(int SQUARES_WIDTH_, int SQUARES_HEIGHT_)
{
	SQUARES_WIDTH = SQUARES_WIDTH_;
	SQUARES_HEIGHT = SQUARES_HEIGHT_;

	NODES_WIDTH = SQUARES_WIDTH + 1;
	NODES_HEIGHT = SQUARES_HEIGHT + 1;

	VERTS_WIDTH = 2 * NODES_WIDTH - 1;
	VERTS_HEIGHT = 2 * NODES_HEIGHT - 1;

	for (int i = 0; i < SQUARES_HEIGHT; i++)
	{
		for (int j = 0; j < SQUARES_WIDTH; j++)
		{
			Square* sq = new Square(2*(i * VERTS_WIDTH + j), 2*(i * SQUARES_WIDTH + j) + 2*VERTS_WIDTH + 2);
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

void Environment::GenerateVertices()
{
	for (int i = 0; i < VERTS_HEIGHT; i++)
	{
		for (int j = 0; j < VERTS_WIDTH; j++)
		{
			vertices.push_back((float)(j) / (VERTS_WIDTH - 1) * 2 - 1);
			vertices.push_back(-((float)(i) / (VERTS_HEIGHT - 1) * 2 - 1));
		}
	}
}

void Environment::GenerateNodes() {
	nM.GenerateNodeMap();
	//nM.SetRegionNumbers();
}

void Environment::SetUpCombs() 
{
	int squareCombsArray[16][5][3] = {
		{{0}, { 0,0,0 }}, // 0
		{{1}, {0,1,VERTS_WIDTH}}, // 1
		{{1}, {1,2,VERTS_WIDTH + 2}}, // 2
		{{2}, {0,2,VERTS_WIDTH + 2}, {0,VERTS_WIDTH + 2,VERTS_WIDTH}}, // 3
		{{1}, {2 * VERTS_WIDTH + 1,2 * VERTS_WIDTH,VERTS_WIDTH},}, // 4
		{{2}, {0,1,2 * VERTS_WIDTH + 1},{0,2 * VERTS_WIDTH + 1,2 * VERTS_WIDTH}}, // 5
		{{4}, {1,2,VERTS_WIDTH + 2},{1,VERTS_WIDTH + 2,2 * VERTS_WIDTH + 1},{1,2 * VERTS_WIDTH + 1,2 * VERTS_WIDTH},{1,2 * VERTS_WIDTH,VERTS_WIDTH}}, // 6
		{{3}, {0,2,VERTS_WIDTH + 2},{0,VERTS_WIDTH + 2,2 * VERTS_WIDTH + 1},{0,2 * VERTS_WIDTH + 1,2 * VERTS_WIDTH}}, // 7
		{{1}, {VERTS_WIDTH + 2,2 * VERTS_WIDTH + 2,2 * VERTS_WIDTH + 1}}, // 8
		{{4}, {0,1,VERTS_WIDTH + 2},{0,VERTS_WIDTH + 2,2 * VERTS_WIDTH + 2},{0,2 * VERTS_WIDTH + 2,2 * VERTS_WIDTH + 1},{0,2 * VERTS_WIDTH + 1,VERTS_WIDTH}}, // 9
		{{2}, {1,2,2 * VERTS_WIDTH + 2},{1,2 * VERTS_WIDTH + 2,2 * VERTS_WIDTH + 1}}, // 10
		{{3}, {0,2,2 * VERTS_WIDTH + 2},{0,2 * VERTS_WIDTH + 2,2 * VERTS_WIDTH + 1},{0,2 * VERTS_WIDTH + 1,VERTS_WIDTH}}, // 11
		{{2}, {VERTS_WIDTH,VERTS_WIDTH + 2,2 * VERTS_WIDTH + 2},{VERTS_WIDTH,2 * VERTS_WIDTH + 2,2 * VERTS_WIDTH}}, // 12
		{{3}, {0,1,VERTS_WIDTH + 2},{0,VERTS_WIDTH + 2,2 * VERTS_WIDTH + 2},{0,2 * VERTS_WIDTH + 2,2 * VERTS_WIDTH}}, // 13
		{{3}, {1,2,2 * VERTS_WIDTH + 2},{1,2 * VERTS_WIDTH + 2,2 * VERTS_WIDTH},{1,2 * VERTS_WIDTH,VERTS_WIDTH}}, // 14
		{{2}, {0,2,2 * VERTS_WIDTH + 2},{0,2 * VERTS_WIDTH + 2,2 * VERTS_WIDTH}}, // 15
	};

	int outLineCombsArray[16][3][2] = {
		{{0}}, // 0
		{{1}, {1, VERTS_WIDTH}}, // 1
		{{1}, {1, VERTS_WIDTH + 2}}, // 2
		{{1}, {VERTS_WIDTH + 2,VERTS_WIDTH}}, // 3
		{{1}, {VERTS_WIDTH, 2 * VERTS_WIDTH + 1}}, // 4
		{{1}, {1,2 * VERTS_WIDTH + 1}}, // 5
		{{2}, {1, VERTS_WIDTH}, {VERTS_WIDTH + 2,2 * VERTS_WIDTH + 1}}, // 6
		{{1}, {VERTS_WIDTH + 2, 2 * VERTS_WIDTH + 1}}, // 7
		{{1}, {VERTS_WIDTH + 2, 2 * VERTS_WIDTH + 1}}, // 8
		{{2}, {VERTS_WIDTH, 2 * VERTS_WIDTH + 1}, {1, VERTS_WIDTH + 2}}, // 9
		{{1}, {1,2 * VERTS_WIDTH + 1}}, // 10
		{{1}, {VERTS_WIDTH, 2 * VERTS_WIDTH + 1}}, // 11
		{{1}, {VERTS_WIDTH + 2,VERTS_WIDTH}}, // 12
		{{1}, {1, VERTS_WIDTH + 2}}, // 13
		{{1}, {1, VERTS_WIDTH}}, // 14
		{{0}}, // 15
	};

	squareCombs = new int**[16];
	for (int i = 0; i < 16; i++)
	{
		int** newRow = new int*[5];
		for (int j = 0; j < 5; j++)
		{
			int* newRow2 = new int[3];
			for (int k = 0; k < 3; k++)
			{
				newRow2[k] = squareCombsArray[i][j][k];
			}
			newRow[j] = newRow2;
		}
		squareCombs[i] = newRow;
	}

	outLineCombs = new int**[16];
	for (int i = 0; i < 16; i++)
	{
		int** newRow = new int* [3];
		for (int j = 0; j < 3; j++)
		{
			int* newRow2 = new int[2];
			for (int k = 0; k < 2; k++)
			{
				newRow2[k] = outLineCombsArray[i][j][k];
			}
			newRow[j] = newRow2;
		}
		outLineCombs[i] = newRow;
	}

}

void Environment::MarchAllSquares()
{
	mainMesh = std::vector<int> (0);
	//allLines = std::vector<int> (0);
	exteriorLines = std::vector<int> (0);
	uniqueExteriorLines = std::vector<int> (0);

	for (int i = 0; i < SQUARES_HEIGHT; i++)
	{
		for (int j = 0; j < SQUARES_WIDTH; j++)
		{
			Square* s = squares[i * SQUARES_WIDTH + j];
			std::cout<<"got sq";
			s->MarchSquare(nM.nodes, squareCombs, outLineCombs, VERTS_WIDTH);
			std::cout<<"marches";
			if (s->code != 0)
			{
				for (int h = 0; h < s->numTris; h++)
				{
					mainMesh.push_back(s->tris[h]->v1);
					mainMesh.push_back(s->tris[h]->v2);
					mainMesh.push_back(s->tris[h]->v3);
					std::cout<<"Pushed";

					// allLines.push_back(s->tris[h]->v1);
					// allLines.push_back(s->tris[h]->v2);
					// allLines.push_back(s->tris[h]->v2);
					// allLines.push_back(s->tris[h]->v3);
					// allLines.push_back(s->tris[h]->v3);
					// allLines.push_back(s->tris[h]->v1);
				}

				// std::vector<int> outlineVerts = *(s->GetOutlineLines());
				// for (int g = 0; g < s->numTris + 1; g++)
				// {
				// 	exteriorLines.push_back(outlineVerts.at(g));
				// 	exteriorLines.push_back(outlineVerts.at(g+1));
				// }
				// exteriorLines.push_back(outlineVerts.at(s->numTris + 1));
				// exteriorLines.push_back(outlineVerts.at(0));

				// for (int f = 0; f < s->numOutVerts; f++)
				// {
				// 	uniqueExteriorLines.push_back(s->outVerts[f]);
				// }
				// std::cout << "ExtPush\n";
			}
		}
	}
}
