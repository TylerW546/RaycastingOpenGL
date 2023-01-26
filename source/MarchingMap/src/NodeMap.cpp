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
	int percentOn = 55;
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
	
	for (int i = 0; i < NODES_HEIGHT; i++)
	{
		for (int j = 0; j < NODES_WIDTH; j++)
		{
			if (nodes[i][j] > 1) {
				nodes[i][j] = 1;
			}
		}
	}

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

	int numGroup = round(num/2)*2;

	if (nodes[i + 1][j] == 1 && round(nodes[i + 1][j]/2)*2 != numGroup)
	{
		Spread(i + 1, j, num);
	}
	if (nodes[i - 1][j] == 1 && round(nodes[i - 1][j]/2)*2 != numGroup)
	{
		Spread(i - 1, j, num);
	}
	if (nodes[i][j + 1] == 1 && round(nodes[i][j + 1]/2)*2 != numGroup)
	{
		Spread(i, j+1, num);
	}
	if (nodes[i][j - 1] == 1 && round(nodes[i][j - 1]/2)*2 != numGroup)
	{
		Spread(i, j-1, num);
	}

	if (nodes[i + 1][j+1] == 1 && round(nodes[i + 1][j+1]/2)*2 != numGroup)
	{
		Spread(i + 1, j+1, num);
	}
	if (nodes[i - 1][j+1] == 1 && round(nodes[i - 1][j+1]/2)*2 != numGroup)
	{
		Spread(i - 1, j+1, num);
	}
	if (nodes[i+1][j + 1] == 1 && round(nodes[i+1][j + 1]/2)*2 != numGroup)
	{
		Spread(i+1, j+1, num);
	}
	if (nodes[i-1][j - 1] == 1 && round(nodes[i-1][j - 1]/2)*2 != numGroup)
	{
		Spread(i-1, j-1, num);
	}
}

bool NodeMap::MakePaths() {
	SetRegionNumbers();
	//If more than just a 2/3 Map,
	bool needed = false;
	for (auto row : nodes) {
		for (auto x : row) {
			if (x > 3) {
				needed = true;
				break;
			}
		}
		if (needed) {
			break;
		}
	}
	if (!needed) {
		return false;
	}

	std::vector<std::vector<int>> three_coords;
	three_coords.clear();
	for (int i = 0; i < NODES_HEIGHT; i++)
	{
		for (int j = 0; j < NODES_WIDTH; j++)
		{
			if (nodes[i][j] == 3) {
				three_coords.push_back(std::vector<int> {i,j});
			}
		}
	}
	if (three_coords.size() < 1) {
		PrintMap(0,0);
	} 

	std::vector<std::vector<int>> other_coords;
	other_coords.clear();
	for (int i = 0; i < NODES_HEIGHT; i++)
	{
		for (int j = 0; j < NODES_WIDTH; j++)
		{
			if (nodes[i][j] % 2 == 1 && nodes[i][j] > 3) {
				other_coords.push_back(std::vector<int> {i,j});
			}
		}
	}

	int choices = 10;  
	std::vector<std::vector<int>> best_combs = {};
	best_combs.clear();
	for (int i = 0; i < three_coords.size(); i++) {
		for (int j = 0; j < other_coords.size(); j++) {
			bool included = false;
			
			int mDist = abs(other_coords[j][0] - three_coords[i][0]) + abs(other_coords[j][1] - three_coords[i][1]);
			if (best_combs.size() > 0) {
				for (int k = 0; k < best_combs.size(); k++) {
					if (mDist < best_combs[k][2]) {
						best_combs.insert(best_combs.begin() + k, std::vector<int> {i,j,mDist});
						included = true;
						break;
					}
				}
			}
			if (best_combs.size() < choices-1 && !included) {
				best_combs.push_back(std::vector<int> {i,j,mDist});
			}
			if (best_combs.size() > choices) {
				best_combs.pop_back();
			}
		}
	}

	//Chooses one of those paths
	srand (time(NULL));
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

	// Fills the line in with ones, recalcs numbers, runs again.
	float y = startY;
	for (float x = startX; x <= endX && y <= endY; x += dX/distance) {
		nodes[round(x+.5)][round(y+.5)] = 1;
		y += dY/distance;
	}
	return true;
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
					std::cout << "# ";
				} else {
					std::cout << "  ";
				}
			}
		}
		std::cout << "\n";
	}
}