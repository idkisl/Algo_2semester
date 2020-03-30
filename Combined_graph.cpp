#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
template<class T>
const T& max(const T& a, const T& b)
{
	return (a < b) ? b : a;
}

typedef void (*Visit)(int vertex, std::vector<int>&);

class Graph
{
	std::vector <std::vector<int>> graph;
public:
	Graph(unsigned int vertexCount)
	{
		graph.resize(vertexCount);
	}
	void AddEdge(unsigned int from, unsigned int to)
	{
		if (from >= graph.size() || to >= graph.size())
			throw "Vertex number is non available in function AddEdge";
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
	const std::vector<int> GetNextVertex(unsigned int from) const
	{
		if (from >= graph.size())
			throw "Vertex number is non available in function GetNextVertex";
		return graph[from];
	}
	unsigned int VertexCount()const
	{
		return graph.size();
	}
	void TransposeGraph()
	{
		std::vector<std::vector<int>> transposed_graph(graph.size());
		for (int i = 0; i < graph.size(); ++i)
			for (int j = 0; j < graph[i].size(); ++j)
				transposed_graph[graph[i][j]].push_back(i);
		graph = transposed_graph;
	}
};

int HowManyEdgesAdd(Graph& graph)
{
	if (graph.VertexCount() == 1)
		return 0;
	int count_root_vertex = 0;
	int count_leaf_vertex = 0;
	for (int i = 0; i < graph.VertexCount(); ++i)
	{
		std::vector<int> next = graph.GetNextVertex(i);
		if (next.empty())
			++count_root_vertex;
	}
	graph.TransposeGraph();
	for (int i = 0; i < graph.VertexCount(); ++i)
	{
		std::vector<int> next = graph.GetNextVertex(i);
		if (next.empty())
			++count_leaf_vertex;
	}
	graph.TransposeGraph();
	return max(count_leaf_vertex, count_root_vertex);
}

void DFS(const Graph& graph, int from, Visit visit, std::vector<int>& color, std::vector<int>& t_out)
{
	std::stack<int> s;
	s.push(from);
	while (!s.empty())
	{
		int vertex = s.top();
		if (color[vertex] == 2)
		{
			s.pop();
			continue;
		}
		if (color[vertex] == 1)
		{
			s.pop();
			color[vertex] = 2;
			visit(vertex, t_out);
			continue;
		}

		//if color[verex] == 0
		color[vertex] = 1;
		const std::vector <int> next = graph.GetNextVertex(vertex);
		for (unsigned int i = 0; i < next.size(); ++i)
		{
			if (color[next[i]] == 0)
			{
				s.push(next[i]);
			}
		}
	}
}

void SaveVertex(int vertex, std::vector<int>& save)
{
	save.push_back(vertex);
}

int FindComponentCombined(Graph& graph, std::vector<int>& combined_vertex)
{
	std::vector<int> color(graph.VertexCount(), 0); // 0 - белый; 1 - серый; 2 - черный
	std::vector<int> t_out;
	for (unsigned int i = 0; i < color.size(); ++i)
		if (color[i] == 0)
		{
			DFS(graph, i, SaveVertex, color, t_out);
		}

	graph.TransposeGraph();

	for (int i = 0; i < color.size(); ++i)
	{
		color[i] = 0;
	}

	int count_layers = 0;
	for (int i = t_out.size() - 1; i >= 0; --i)
	{
		if (color[t_out[i]] == 0)
		{
			std::vector<int> t_out_transpose;
			DFS(graph, t_out[i], SaveVertex, color, t_out_transpose);
			for (int j = 0; j < t_out_transpose.size(); ++j)
			{
				combined_vertex[t_out_transpose[j]] = count_layers;
			}
			++count_layers;
		}
	}
	graph.TransposeGraph();
	return count_layers;
}

int FindAnswer(Graph& graph)
{
	std::vector<int> combined_vertex(graph.VertexCount());
	int count_component = FindComponentCombined(graph, combined_vertex);

	Graph component_graph(count_component);
	for (unsigned int i = 0; i < graph.VertexCount(); ++i)
	{
		std::vector<int> next = graph.GetNextVertex(i);
		std::unordered_set<int> set;
		for (unsigned int j = 0; j < next.size(); ++j)
		{
			if (combined_vertex[next[j]] != combined_vertex[i])
				set.insert(next[j]); // граф с вершинами - компонентами связанности
		}
		for (int k : set)
		{
			component_graph.AddEdge(combined_vertex[i], combined_vertex[k]);
		}
		set.clear();
	}
	return HowManyEdgesAdd(component_graph);
}

int main()
{
	int N, M;
	std::cin >> N; // вершины.
	std::cin >> M; // ребра.
	int from, to;
	Graph graph(N);
	for (int i = 0; i < M; ++i)
	{
		std::cin >> from >> to;
		--from;
		--to;
		graph.AddEdge(from, to);
	}
	std::cout << FindAnswer(graph);
	return 0;
}
