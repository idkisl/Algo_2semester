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

Graph MakeGraph(int cost_a, int cost_b, int M)
{
	Graph graph(M);
	for (uint64_t i = 0; i < M; ++i)
	{
		if ((i + 1) % M == (i * i + 1) % M)
		{
			if (cost_b < cost_a)
				graph.AddEdge(i, (i * i + 1) % M, cost_b);
			else
				graph.AddEdge(i, (i + 1) % M, cost_a);
		}
		else
		{
			graph.AddEdge(i, (i + 1) % M, cost_a);
			graph.AddEdge(i, (i * i + 1) % M, cost_b);
		}
	}
	return graph;
}

int Dijkstra(const Graph& graph, int from, int to)
{
	std::vector<color> color(graph.VertexCount(), WHITE);
	std::vector<int> min_dist(graph.VertexCount(), -1);
	std::multimap<int, int> grey_vertex; // first -min_dist[i], second - number of Edge

	min_dist[from] = 0;
	color[from] = GREY;
	grey_vertex.emplace(0, from);

	while (!grey_vertex.empty())
	{
		auto min_iter = grey_vertex.begin();
		int min_index = min_iter->second;
		int min_distance = min_iter->first;
		grey_vertex.erase(min_iter);
		color[min_index] = BLACK;
		const std::vector<std::pair<int, int>> next = graph.GetNextVertex(min_index);
		for (int i = 0; i < next.size(); ++i)
		{
			int current_dist = min_distance + next[i].second;
			int neighbour = next[i].first;
			if (color[neighbour] == WHITE)
			{
				color[neighbour] = GREY;
				grey_vertex.emplace(current_dist, neighbour);
				min_dist[neighbour] = current_dist;
			}
			else if (color[neighbour] == GREY && current_dist < min_dist[neighbour])
			{
				auto it = grey_vertex.find(min_dist[neighbour]);
				if (it == grey_vertex.end())
				{
					throw std::runtime_error("Mistake in Dijkstra");
				}
				while (it->first == min_dist[neighbour] && it->second != neighbour)
					++it;
				if (it->first == min_dist[neighbour] && it->second != neighbour)
					throw std::runtime_error("Mistake in Dijkstra");
				grey_vertex.erase(it);

				min_dist[neighbour] = current_dist;
				grey_vertex.emplace(current_dist, neighbour);
			}
		}
	}

	return min_dist[to];
}

int main()
{
	int cost_a, cost_b, M, from, to;
	std::cin >> cost_a >> cost_b >> M >> from >> to;
	Graph graph = MakeGraph(cost_a, cost_b, M);
	std::cout << Dijkstra(graph, from, to) << std::endl;
	return 0;
}