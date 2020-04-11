#include <iostream>
#include <vector>

class Graph
{
	std::vector <std::vector<std::pair<int, int>>> graph; // first is next, second is weight
public:
	explicit Graph(unsigned int vertexCount)
	{
		graph.resize(vertexCount);
	}
	void AddEdge(unsigned int from, unsigned int to, int weight = 1)
	{
		if (from >= graph.size() || to >= graph.size())
			throw std::runtime_error("Vertex number is non available in function AddEdge");
		graph[from].push_back(std::make_pair(to, weight));
	}
	bool HasEdge(unsigned int from, unsigned int to) const
	{
		if (from >= graph.size() || to >= graph.size())
			return false;
		for (unsigned int i = 0; i < graph[from].size(); ++i)
			if (graph[from][i].first == to)
				return true;
		return false;
	}
	int GetEdge(unsigned int from, unsigned int to) const
	{
		if (from >= graph.size() || to >= graph.size())
			throw std::runtime_error("Incorrect vertex in GetEdge");
		for (unsigned int i = 0; i < graph[from].size(); ++i)
			if (graph[from][i].first == to)
				return graph[from][i].second; // weight
		return -1;
	}
	std::vector<std::pair<int, int>> GetNextVertex(unsigned int from) const
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

Graph MakeGraph(int N, int M)
{
	Graph graph(N);
	int from, to, cost;
	for (int i = 0; i < M; ++i)
	{
		std::cin >> from >> to >> cost;
		graph.AddEdge(from - 1, to - 1, cost);
	}
	return graph;
}

int FordBellman(const Graph& graph, int from, int to, int K)
{
	const int INF = 2000000; // инициализация бесконечности
	std::vector<int> dist(graph.VertexCount(), INF);
	dist[from] = 0;
	for (int i = 0; i < K; ++i)
	{
		std::vector<int> new_dist = dist;
		for (int j = 0; j < graph.VertexCount(); ++j)
		{
			std::vector<std::pair<int, int>> next = graph.GetNextVertex(j); // проходимся по всем ребрам
			for (int k = 0; k < next.size(); ++k)
			{
				int nextK = next[k].first;
				int next_edge = next[k].second;
				if (dist[nextK] > dist[j] + next_edge)
				{
					new_dist[nextK] = dist[j] + next_edge;
				}
			}
		}
		dist = new_dist;
	}

	return dist[to] == INF ? -1 : dist[to];
}

int main()
{
	int N, M, from, to, K;
	std::cin >> N >> M >> K >> from >> to;
	Graph graph = MakeGraph(N, M);
	std::cout << FordBellman(graph, from - 1, to - 1, K);
	return 0;
}
