#include <iostream>
#include <vector>
#include <string>

class Graph
{
	std::vector <std::vector<int>> graph;
public:
	explicit Graph(unsigned int vertexCount)
	{
		graph.resize(vertexCount);
	}
	void AddEdge(unsigned int from, unsigned int to, int weight = 1)
	{
		if (from >= graph.size() || to >= graph.size())
			throw std::runtime_error("Vertex number is non available in function AddEdge");
		graph[from].push_back(to);
		graph[to].push_back(from);
	}
	bool HasEdge(unsigned int from, unsigned int to) const
	{
		if (from >= graph.size() || to >= graph.size())
			return false;
		for (unsigned int i = 0; i < graph[from].size(); ++i)
			if (graph[from][i] == to)
				return true;
		return false;
	}
	std::vector<int> GetNextVertex(unsigned int from) const
	{
		if (from >= graph.size())
		{
			std::cout << "from" << from << "  size = " << graph.size() << std::endl;
			throw std::runtime_error("Vertex number is non available in function GetNextVertex");

		}
		return graph[from];
	}
	unsigned int VertexCount()const
	{
		return graph.size();
	}
};

std::vector<std::vector<bool>> MakeTable(int n, int m)
{
	std::vector<std::vector<bool>> table(n);
	for (int i = 0; i < n; ++i)
		table[i].resize(m);
	std::string line;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> line;
		for (int j = 0; j < line.size(); ++j)
		{
			if (line[j] == '*')
				table[i][j] = false; // дырка
			else
				table[i][j] = true;
		}
	}
	return table;
}

Graph MakeGraphRelationship(const std::vector<std::vector<bool>>& table,int n, int m)
{
	Graph graph(n * m);
	for (int i = 0; i < table.size(); ++i)
	{
		for (int j = 0; j < table[i].size(); ++j)
		{
			if (table[i][j] == false)
			{
				if ((i + 1) < n && table[i + 1][j] == false)
					graph.AddEdge(i * m + j, (i + 1) * m + j);
				if ((j + 1) < m && table[i][j + 1] == false)
					graph.AddEdge(i * m + j, i * m + j + 1);
			}
		}
	}
	return graph;
}

bool DFS(const Graph& graph, std::vector<int>& px, std::vector<int>& py, std::vector<bool>& vis, int x)
{
	if (vis[x] == true)
		return false;
	vis[x] = true;
	// (x,y) in E
	std::vector<int> next = graph.GetNextVertex(x);
	for (int i = 0; i < next.size(); ++i)
	{
		int y = next[i];
		if (py[y] == -1)
		{
			py[y] = x;
			px[x] = y;
			return true;
		}
		else if (DFS(graph, px, py, vis, py[y]))
		{
			py[y] = x;
			px[x] = y;
			return true;
		}
	}
	return false;
}

std::vector<int> fordFulkerson(int n, int m, const Graph& graph)
{
	std::vector<int> px(n * m, -1);
	std::vector<int> py(n * m, -1);
	bool isPath = true;
	while (isPath)
	{
		isPath = false;
		std::vector<bool> vis(n * m, false);
		for (int i = 0; i < graph.VertexCount(); ++i)
		{
			// for x in L
			if ((i % m + int(i / m)) % 2 == 0 && graph.GetNextVertex(i).size() > 0)
			{
				int x = i;
				if (graph.GetNextVertex(x).size() > 0)
				{
					if (px[x] == -1)
						if (DFS(graph, px, py, vis, x))
							isPath = true;
				}
			}
		}
	}
	return px;
}

long long calculateMinTime(int cost_a, int cost_b,int n, int m, std::vector<int>& pairs, std::vector<std::vector<bool>>& table)
{
	if (2 * cost_b < cost_a)
		pairs.clear(); // проверка, что 2 * b < a
	long long sum = 0;
	for (int i = 0; i < pairs.size(); ++i)
	{
		if (pairs[i] != -1)
		{
			if ((table[(i - i % m) / m][i % m] || table[(pairs[i] - pairs[i] % m) / m][pairs[i] % m]) == false)
				sum += cost_a;
			table[(i - i % m) / m][i % m] = true;
			table[(pairs[i] - pairs[i] % m) / m][pairs[i] % m] = true;
		}
	}
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (table[i][j] == false)
				sum += cost_b;
	return sum;
}

int main()
{
	int n, m, a, b;
	std::cin >> n >> m >> a >> b;
	auto table = MakeTable(n, m);
	Graph graph = MakeGraphRelationship(table, n, m);
	std::vector<int> pairs = fordFulkerson(n, m, graph);
	std::cout << calculateMinTime(a, b, n, m, pairs, table);
}