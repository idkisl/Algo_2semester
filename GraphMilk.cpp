#include <iostream>
#include <vector>
#include <queue>

typedef void (*Visit)(int a, int b, std::vector<int>&);

class Graph
{
	std::vector <std::vector<int>> graph;
public:
	Graph(unsigned int vertexCount)
	{
		graph.resize(vertexCount);
	}
	void AddEdge(unsigned int a, unsigned int b)
	{
		if (a >= graph.size() || b >= graph.size())
			throw "Vertex number is non available";
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	bool HasEdge(unsigned int from, unsigned int to)
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

void BFS(const Graph& graph, int from, Visit visit, std::vector<int>& d)
{
	std::queue<int> qu;
	std::vector<int> color(graph.VertexCount(), 0); // 0 - белый; 1- серый; 2 - черный
	do
	{
		qu.push(from);
		color[from] = 1;
		while (!qu.empty())
		{
			int vertex = qu.front();
			qu.pop();
			color[vertex] = 2;
			const std::vector <int>& next = graph.GetNextVertex(vertex);
			for (unsigned int i = 0; i < next.size(); ++i)
			{
				if (color[next[i]] == 0)
				{
					qu.push(next[i]);
					color[next[i]] = 1;
					visit(vertex, next[i],d);
				}
			}
			//visit(vertex, next);
		}
		//проходимся по color и находим непокрашенную вершину
		from = -1;
		for (unsigned int j = 0; j < color.size(); ++j)
			if (color[j] == 0)
			{
				from = j;
				break;
			}
	} while (from != -1);
}

void Distance(int vertex, int neighbour,std::vector<int>& d)
{
	d[neighbour] = d[vertex] + 1;
}

int FindAnswer(Graph& graph, int Leon, int Matilda, int Milk)
{
	std::vector<int> dMilk(graph.VertexCount(),0);
	std::vector<int> dLeon(graph.VertexCount(), 0);
	std::vector<int> dMatilda(graph.VertexCount(), 0);

	BFS(graph, Milk, Distance, dMilk);
	BFS(graph, Leon, Distance, dLeon);
	BFS(graph, Matilda, Distance, dMatilda);

	int min = dMilk[0] + dMatilda[0] + dLeon[0];
	for (unsigned int i = 1; i < graph.VertexCount(); ++i)
		if (dMilk[i] + dMatilda[i] + dLeon[i] < min)
			min = dMilk[i] + dMatilda[i] + dLeon[i];
	return min;
}

int main()
{
	int count_vertex, count_edge, matilda, milk, leon;
	std::cin >> count_vertex >> count_edge >> leon >> matilda >> milk;
	Graph graph(count_vertex);
	for (int i = 0; i < count_edge; ++i)
	{
		int from, to;
		std::cin >> from >> to;
		graph.AddEdge(from - 1, to - 1);
	}
	std::cout << FindAnswer(graph, leon - 1, matilda - 1, milk - 1) << std::endl;
	return 0;
}
