#include"NodeMap.hpp"

NodeMap::NodeMap()
{

}

NodeMap::NodeMap(int NODES_WIDTH_, int NODES_HEIGHT_)
{
	NODES_WIDTH = NODES_WIDTH_;
	NODES_HEIGHT = NODES_HEIGHT_;
	
	for (int i = 0; i < NODES_HEIGHT; i++)
	{
		nodes.push_back(std::vector<int> (NODES_WIDTH,0));
	}

	for (int i = 0; i < NODES_HEIGHT; i++)
	{
		oldNodes.push_back(std::vector<int> (NODES_WIDTH,0));
	}
}

int NodeMap::GetSurroundingOnNodes(int i, int j)
{
	int count = 0;
	for (int neighborI = i - 1; neighborI <= i + 1; neighborI++)
	{
		for (int neighborJ = j - 1; neighborJ <= j + 1; neighborJ++)
		{
			if (neighborI != i || neighborJ != j)
			{
				if (neighborI >= 0 && neighborI < NODES_HEIGHT && neighborJ >= 0 && neighborJ < NODES_WIDTH)
				{
					if (oldNodes[neighborI][neighborJ] == 0)
					{
						count++;
					}
				} else
				{
					count++;
				}
			}
		}
	}
	return count;
}

void NodeMap::SmoothMap()
{
	for (int i = 0; i < NODES_HEIGHT; i++)
	{
		for (int j = 0; j < NODES_WIDTH; j++)
		{
			oldNodes[i][j] = nodes[i][j];
		}
	}

	for (int i = 0; i < NODES_HEIGHT; i++)
	{
		for (int j = 0; j < NODES_WIDTH; j++)
		{
			int count = GetSurroundingOnNodes(i, j);
			if (count > 4)
			{
				nodes[i][j] = 0;
			} else if (count < 4)
			{
				nodes[i][j] = 1;
			};
		};
	};
}

void NodeMap::GenerateNodeMap()
{
	srand(time(NULL));
	int percentOn = 50;
	int outLayer = 0;
	// Generating random nodes
	for (int i = 0; i < NODES_HEIGHT; i++)
	{
		for (int j = 0; j < NODES_WIDTH; j++)
		{
			if (i == 0 || j == 0 || i == NODES_HEIGHT - 1 || j == NODES_WIDTH - 1 || rand() % 100 + 1 <= percentOn)
			{
				nodes[i][j] = 0;
			} else
			{
				nodes[i][j] = 1;
			}
		}
	}
	// Smoothing nodes
	for (int i = 0; i < 10; i++)
	{
		SmoothMap();
	}
}

void NodeMap::SetRegionNumbers()
{
	int nextSpreadNum = 2;
	for (int i = 0; i < NODES_HEIGHT; i++)
	{
		for (int j = 0; j < NODES_WIDTH; j++)
		{
			if (nodes[i][j] == 1)
			{
				Spread(i, j, nextSpreadNum);
				nextSpreadNum+=2;
			}
		}
	}
	maxRegionNum = nextSpreadNum - 2;
}

void NodeMap::Spread(int i, int j, int num)
{
	if (nodes[i+1][j] == 0 || nodes[i-1][j] == 0 || nodes[i][j+1] == 0 || nodes[i][j-1] == 0) {
		nodes[i][j] = num+1;
	} else {
		nodes[i][j] = num;
	}

	if (nodes[i + 1][j] != 0 && nodes[i + 1][j] != num && nodes[i + 1][j] != num+1)
	{
		Spread(i + 1, j, num);
	}
	if (nodes[i - 1][j] != 0 && nodes[i - 1][j] != num && nodes[i - 1][j] != num+1)
	{
		Spread(i - 1, j, num);
	}
	if (nodes[i][j + 1] != 0 && nodes[i][j + 1] != num && nodes[i][j + 1] != num+1)
	{
		Spread(i, j+1, num);
	}
	if (nodes[i][j - 1] != 0 && nodes[i][j - 1] != num && nodes[i][j - 1] != num+1)
	{
		Spread(i, j-1, num);
	}
}

void NodeMap::MakePaths() {
	//If more than just a 2/3 Map,
	bool needed = false;
	for (auto row : nodes) {
		for (auto x : row) {
			if (x > 3) {
				needed = true;
			}
		}
	}
	if (!needed) {
		return;
	}
	std::cout<<"needed\n";

	std::vector<std::vector<int>> three_coords;
	for (int i = 0; i < NODES_HEIGHT; i++)
	{
		for (int j = 0; j < NODES_WIDTH; j++)
		{
			if (nodes[i][j] == 3) {
				three_coords.push_back(std::vector<int> {i,j});
			}
		}
	}
	std::cout <<"found: "<<three_coords.size()<<" threes\n"; 

	std::vector<std::vector<int>> other_coords;
	for (int i = 0; i < NODES_HEIGHT; i++)
	{
		for (int j = 0; j < NODES_WIDTH; j++)
		{
			if (nodes[i][j] % 2 == 1 && nodes[i][j] > 3) {
				other_coords.push_back(std::vector<int> {i,j});
			}
		}
	}
	std::cout <<"found: "<<other_coords.size()<<" others\n"; 

	int choices = 10;  
	std::vector<std::vector<int>> best_combs;

	for (int i = 0; i < three_coords.size(); i++) {
		for (int j = 0; j < other_coords.size(); j++) {
			int mDist = abs(other_coords[j][0] - three_coords[i][0]) + abs(other_coords[j][1] - three_coords[i][1]);
			if (best_combs.size() == 0) {
				best_combs.push_back(std::vector<int> {i,j,mDist});
			} else {
				for (int k = 0; k < best_combs.size(); k++) {
					if (mDist < best_combs[k][2]) {
						best_combs.insert(best_combs.begin() + k, std::vector<int> {i,j,mDist});
					}

					if (best_combs.size() > choices) {
						best_combs.pop_back();
					}
				}
			}
		}
	}
	std::cout <<"found: "<<best_combs.size()<<" combs\n"; 

	//Chooses one of those paths
	int randomIndex = rand() % best_combs.size();
	std::vector<int> best = best_combs[randomIndex];

	int startX = three_coords[best[0]][0];
	int startY = three_coords[best[0]][1];
	int endX = other_coords[best[1]][0];
	int endY = other_coords[best[1]][1];

	if (startX > endX) {
		int save = startX;
		startX = endX;
		endX = save;
	}

	if (startY > endY) {
		int save = startY;
		startY = endY;
		endY = save;
	}
	float dX = endX - startX;
	float dY = endY - startY;
	int distance = sqrt(dX*dX + dY*dY);

	std::cout<<startX<<"  "<<startY<<"\n";
	std::cout<<endX<<"  "<<endY<<"\n";

	// Fills the line in with ones, recalcs numbers, runs again.
	for (float x = startX; x <= endX; x += dX/distance) {
		for (float y = startY; y <= endY; y += dY/distance) {
			nodes[round(x)][round(y)] = 1;
		}
	}

	return;

}

void NodeMap::PrintMap(int x, int y) {
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
	for (int i = 0; i < nodes.size(); i++) {
		for (int j = 0; j < nodes[0].size(); j++) {
			auto el = nodes[i][j];
			if (i == x && j== y) {
				std::cout << "X ";
			} else {
				if (el == 0) {
					std::cout << "  ";
				} else {
					std::cout << el << " ";
				}
			}
		}
		std::cout << "\n";
	}
}