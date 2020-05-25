#include <iostream>
#include <vector>
#include <algorithm>

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
	int value;
	int from;
	int to;
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

long long KruskalMST(std::vector<Edge>& edges, int N_vertex)
{
	DSU set(N_vertex);
	int count_sets = N_vertex;
	std::sort(edges.begin(), edges.end());
	long long sum = 0;

	for (int i = 0; i < edges.size(); ++i)
	{
		if (set.GetRoot(edges[i].from) != set.GetRoot(edges[i].to))
		{
			sum += edges[i].value;
			--count_sets;
			set.UnitSet(edges[i].from, edges[i].to);
		}
		if (count_sets == 1)
			break;
	}
	return sum;
}

int main()
{
	int N, M;
	std::cin >> N >> M;
	std::vector<Edge> edges = MakeEdges(M);
	std::cout << KruskalMST(edges,N);
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