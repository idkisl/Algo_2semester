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
		graph[to].push_back(std::make_pair(from, weight));
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
	int from, to;
	int cost;
	for (int i = 0; i < M; ++i)
	{
		std::cin >> from >> to >> cost;
		graph.AddEdge(from - 1, to - 1, cost);
	}
	return graph;
}

double FordBellman(const Graph& graph, int from, int to)
{
	const int INF = 200; // инициализация бесконечности

	std::vector<double> probability(graph.VertexCount(), INF);
	probability[from] = 0;
	for (unsigned int i = 0; i < graph.VertexCount(); ++i)
	{
		for (int j = 0; j < graph.VertexCount(); ++j)
		{
			std::vector<std::pair<int, int>> next = graph.GetNextVertex(j); // проходимся по всем ребрам
			for (int k = 0; k < next.size(); ++k)
			{
				int nextK = next[k].first;
				double next_edge = double(next[k].second) / 100;
				double next_probability = probability[j] + next_edge - probability[j] * next_edge;
				if (next_probability < probability[nextK])
				{
					probability[nextK] = next_probability;
				}
			}
		}
	}
	if (probability[to] == INF)
		throw std::runtime_error("There is no way from FROM to TO");
	return probability[to];
}

int main()
{
	int N, M, from, to;
	std::cin >> N >> M >> from >> to;
	Graph graph = MakeGraph(N, M);
	double answer = FordBellman(graph, from - 1, to - 1);
	std::cout << answer;
	return 0;
}
