#include <iostream>
#include <vector>

template <class T>
void Print(const std::vector<std::vector<T>> vec)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		for (int j = 0; j < vec[i].size(); ++j)
			std::cout << vec[i][j];
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

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
			throw std::runtime_error("Vertex number is non available in function GetNextVertex");
		return graph[from];
	}
	unsigned int VertexCount()const
	{
		return graph.size();
	}
};

Graph MakeGraph(int N)
{
	Graph graph(N);
	std::string line;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> line;
		for (int j = 0; j < line.size(); ++j)
			if (line[j] == '1')
				graph.AddEdge(i, j);
	}
	return graph;
}

std::vector<std::vector<int>> Floyd(const Graph& graph)
{
	const int INF = 3;
	std::vector<std::vector<int>> dist(graph.VertexCount());
	for (int i = 0; i < graph.VertexCount(); ++i)
		dist[i].resize(graph.VertexCount(), INF);
	for (int i = 0; i < graph.VertexCount(); ++i)
	{
		std::vector<int> next = graph.GetNextVertex(i);
		for (int j = 0; j < next.size(); ++j)
			dist[i][next[j]] = 1;
	}
	for (int i = 0; i < graph.VertexCount(); ++i)
	{
		for (int u = 0; u < graph.VertexCount(); ++u)
		{
			for (int v = 0; v < graph.VertexCount(); ++v)
			{
				if (dist[u][i] + dist[i][v] < dist[u][v])
				{
					dist[u][v] = 1; // (dist[u][i] + dist[i][v]) % 2;
				}
			}
		}
	}
	for (int i = 0; i < dist.size(); ++i)
	{
		for (int j = 0; j < dist[i].size(); ++j)
		{
			if (dist[i][j] == 3)
				dist[i][j] = 0;
			else
				dist[i][j] = 1;
		}
	}
	return dist;
}

int main()
{
	int N;
	std::cin >> N;
	Graph graph = MakeGraph(N);
	Print(Floyd(graph));
	return 0;
}
