#include <iostream>
#include <vector>
#include <algorithm>

enum color { WHITE, BLACK };

struct DSU
{
	std::vector<int> set;
	explicit DSU(int N)
	{
		set.resize(N);
		for (int i = 0; i < N; ++i)
			set[i] = i;
	}
	int GetRoot(int vertex)
	{
		if (vertex != set[vertex])
			set[vertex] = GetRoot(set[vertex]);
		return set[vertex];
	}
	void UnitSet(int a, int b)
	{
		int a_root = GetRoot(a);
		int b_root = GetRoot(b);
		if (a_root != b_root)
			set[a_root] = b_root;
	}
};

struct Edge
{
	long long value = 0;
	int from = -1;
	int to = -1;
	Edge(long long value, int from, int to) : value(value), from(from), to(to) {}
	Edge() {}
	bool operator<(const Edge& right) const { return value < right.value; }
};

std::vector<Edge> MakeEdges(int N_edge)
{
	std::vector<Edge> edges(N_edge);
	for (int i = 0; i < N_edge; ++i)
	{
		std::cin >> edges[i].from >> edges[i].to >> edges[i].value;
		--edges[i].from;
		--edges[i].to;
	}
	return edges;
}

std::vector<Edge> KruskalMST(std::vector<Edge> edges, int N_vertex)
{
	DSU set(N_vertex);
	std::vector<Edge> MST;
	int count_sets = N_vertex;
	std::sort(edges.begin(), edges.end());
	long long sum = 0;

	for (int i = 0; i < edges.size(); ++i)
	{
		if (set.GetRoot(edges[i].from) != set.GetRoot(edges[i].to))
		{
			MST.push_back(edges[i]);
			sum += edges[i].value;
			--count_sets;
			set.UnitSet(edges[i].from, edges[i].to);
		}
		if (count_sets == 1)
			break;
	}
	//return sum; - минимальная сумма веса остовного дерева
	return MST;
}

long long sumValueRelatedGraph(int n, int m)
{
	std::vector<long long> vertex(n);
	int min_vertex = -1;
	long long min = 0;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> vertex[i];
		if (min > vertex[i] || i == 0)
		{
			min = vertex[i];
			min_vertex = i;
		}
	}

	std::vector<Edge> edges = KruskalMST(MakeEdges(m), n); // компоненты связанности в специальных предложениях
	std::vector<color> color(n, WHITE);
	int size = edges.size();
	for (int i = 0; i < size; ++i)
	{
		if (edges[i].value > (vertex[edges[i].from] + vertex[edges[i].to]))
			edges[i].value = (vertex[edges[i].from] + vertex[edges[i].to]);
		edges.push_back(Edge((min + vertex[edges[i].from]), edges[i].from, min_vertex));
		edges.push_back(Edge((min + vertex[edges[i].to]), edges[i].to, min_vertex));
		color[edges[i].from] = BLACK;
		color[edges[i].to] = BLACK;
	}

	for (int i = 0; i < n; ++i)
	{
		if (color[i] == WHITE)
		{
			color[i] = BLACK;
			if (min_vertex != i)
				edges.push_back(Edge((min + vertex[i]), min_vertex, i));
		}
	}
	edges = KruskalMST(edges, n);
	long long sum = 0;
	for (int i = 0; i < edges.size(); ++i)
		sum += edges[i].value;
	return sum;
}

int main()
{
	int n, m;
	std::cin >> n >> m;
	std::cout << sumValueRelatedGraph(n, m) << std::endl;
	return 0;
}