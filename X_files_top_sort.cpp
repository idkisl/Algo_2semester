#include <iostream>
#include <vector>
#include <stack>

enum color{WHITE, GREY, BLACK};

typedef void (*Visit)(int vertex, std::vector<int>&);

class Graph
{
	std::vector <std::vector<int>> graph;
public:
	explicit Graph(unsigned int vertexCount)
	{
		graph.resize(vertexCount);
	}
	void AddEdge(unsigned int a, unsigned int b)
	{
		if (a >= graph.size() || b >= graph.size())
			throw "Vertex number is non available";
		graph[a].push_back(b);
	}
	bool HasEdge(unsigned int from, unsigned int to) const
	{
		if (from >= graph.size())
			return false;
		for (unsigned int i = 0; i < graph[from].size(); ++i)
			if (graph[from][i] == to)
				return true;
		return false;
	}
	const std::vector<int>& GetNextVertex(unsigned int from) const
	{
		return graph[from];
	}
	unsigned int VertexCount()const
	{
		return graph.size();
	}
};

bool TopSort(const Graph& graph, int from, Visit visit, std::vector<int>& topsort)
{
	std::vector<color> color(graph.VertexCount(), WHITE);
	std::stack<int> s;
	bool from_new;

	do
	{
		s.push(from);
		while (!s.empty())
		{
			int vertex = s.top();
			if (color[vertex] == BLACK)
			{
				s.pop();
				continue;
			}
			if (color[vertex] == GREY)
			{
				s.pop();
				color[vertex] = BLACK;
				visit(vertex, topsort);
				continue;
			}

			//if color[verex] == WHITE
			color[vertex] = GREY;
			const std::vector <int> next = graph.GetNextVertex(vertex);
			for (unsigned int i = 0; i < next.size(); ++i)
			{
				if (color[next[i]] == WHITE)
				{
					s.push(next[i]);
				}
				else if (color[next[i]] == GREY)
				{
					//we found circle
					return true;
				}
			}
		}
		//проходимся по color и находим непокрашенную вершину
		from_new = false;
		for (int j = from; j < color.size(); ++j)
			if (color[j] == WHITE)
			{
				from = j;
				from_new = true;
				break;
			}
	} while (from_new);

	//there is no circle
	return false;
}

void SaveVertex(int vertex, std::vector<int>& topsort)
{
	topsort.push_back(vertex);
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
		graph.AddEdge(from, to);
	}
	std::vector<int> topsort;
	if (TopSort(graph, 0, SaveVertex, topsort))
		std::cout << "NO";
	else
	{
		std::cout << "YES" << std::endl;
		for (int i = topsort.size() - 1; i >= 0; --i)
			std::cout << topsort[i] << " ";
	}
	return 0;
}
/*
10 9
0 2
0 3
0 4
1 4
3 5
3 6
6 7
6 8
4 9
*/