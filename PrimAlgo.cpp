#include <iostream>
#include <vector>
#include <map>

enum color { WHITE, GREY, BLACK };

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
		{
			throw std::runtime_error("Vertex number is non available in function AddEdge");
			std::cout << "Here is mistake in AddEdge";
		}
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
		{
			throw std::runtime_error("Incorrect vertex in GetEdge");
		}
		for (unsigned int i = 0; i < graph[from].size(); ++i)
			if (graph[from][i].first == to)
				return graph[from][i].second;
		return -1;
	}
	std::vector<std::pair<int, int>> GetNextVertex(unsigned int from) const
	{
		if (from >= graph.size())
		{
			throw std::runtime_error("Vertex number is non available in function GetNextVertex");
		}
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

long long PrimMST(const Graph& graph)
{
	const int INF = 200000;
	std::vector<int> key(graph.VertexCount(), INF);
	std::vector<color> color(graph.VertexCount(), WHITE);
	std::multimap<int, int> queue; // first - key, second - number
	key[0] = 0;
	color[0] = GREY;
	queue.emplace(0, 0);
	while (!queue.empty())
	{
		int v = (*queue.begin()).second;
		queue.erase(queue.begin());
		color[v] = BLACK;
		std::vector<std::pair<int, int>> next = graph.GetNextVertex(v);
		for (int j = 0; j < next.size(); ++j)
		{
			int u = next[j].first;
			if (color[u] == WHITE)
			{
				key[u] = graph.GetEdge(v, u);
				queue.emplace(key[u], u);
				color[u] = GREY;
			}
			else if (color[u] == GREY && key[u] > graph.GetEdge(v, u))
			{
				auto it = queue.find(key[u]);
				while (it->first == key[u] && it->second != u)
					++it;
				queue.erase(it);

				key[u] = graph.GetEdge(v, u);
				queue.emplace(key[u], u);
			}
		}
	}
	long long sum = 0;
	for (int i = 0; i < key.size(); ++i)
		sum += key[i];
	return sum;
}

int main()
{
	int N, M;
	std::cin >> N >> M;
	Graph graph = MakeGraph(N, M);
	std::cout << PrimMST(graph);
	return 0;
}


/*
5 7
1 2 3
1 3 4
2 3 5
3 4 2
4 5 7
1 5 1
3 5 6

-------
10
*/