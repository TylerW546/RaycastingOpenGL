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

void Environment::MarchAllSquares()
{
	mainMesh.clear();
	//allLines = std::vector<int> (0);
	//exteriorLines = std::vector<int> (0);
	uniqueExteriorLines.clear();

	for (int i = 0; i < SQUARES_HEIGHT; i++)
	{
		for (int j = 0; j < SQUARES_WIDTH; j++)
		{
			Square* s = squares[i * SQUARES_WIDTH + j];
			s->MarchSquare(nM.nodes, VERTS_WIDTH);
			if (s->code != 0)
			{
				for (int h = 0; h < s->numTris; h++)
				{
					mainMesh.push_back(s->tris[h]->v1);
					mainMesh.push_back(s->tris[h]->v2);
					mainMesh.push_back(s->tris[h]->v3);

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
				if (s->numOutVerts > 0) {
					for (int f = 0; f < s->numOutVerts; f++)
					{
						uniqueExteriorLines.push_back(s->outVerts.at(f));
					}
				}
				// std::cout << "ExtPush\n";
			}
		}
	}
}
