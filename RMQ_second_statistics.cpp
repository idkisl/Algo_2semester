#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class SparseTable
{
    std::vector<std::vector<int>> table;
    std::vector<std::vector<int>> table_2min;
    std::vector<int> vec;
    void _makeAllTable()
    {
        const int size_k = int(std::log2(vec.size()) + 1);
        table.resize(size_k);
        table_2min.resize(size_k);
        for (int i = 0; i < vec.size(); ++i)
        {
            table[0].push_back(i);
            table_2min[0].push_back(-1);
        }
        for (int k = 1; k < size_k; ++k)
        {
            for (int i = 0; i < table[k - 1].size(); ++i)
            {
                int interval1 = table[k - 1][i];
                int pow_ = pow(2, k - 1);
                if (i + pow_ >= table[k - 1].size())
                    continue;
                int interval2 = table[k - 1][i + pow_];
                int max_i;
                if (vec[interval1] > vec[interval2])
                {
                    table[k].push_back(interval2);
                    max_i = interval1;
                }
                else
                {
                    table[k].push_back(interval1);
                    max_i = interval2;
                }
                if (table_2min[k - 1][i + pow_] != -1 && vec[max_i] > vec[table_2min[k - 1][i + pow_]])
                    max_i = table_2min[k - 1][i + pow_];
                if (table_2min[k - 1][i] != -1 && vec[max_i] > vec[table_2min[k - 1][i]])
                    max_i = table_2min[k - 1][i];
                table_2min[k].push_back(max_i);
            }
        }
    }
public:
    SparseTable(const std::vector<int>& vec) : vec(vec)
    {
        _makeAllTable();
    }
    int GetMin2OnInterval(int start, int finish) const
    {
        int k = int(std::log2(finish - start + 1));
        int inter1 = table[k][start];
        int inter2 = table[k][finish - pow(2, k) + 1];
        int inter_1 = table_2min[k][start];
        int inter_2 = table_2min[k][finish - pow(2, k) + 1];
        int min = inter1;
        int min2 = inter2;
        std::vector<int> find_min = { inter1 , inter2, inter_1 , inter_2 };
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (vec[find_min[j]] > vec[find_min[j + 1]])
                    std::swap(find_min[j], find_min[j + 1]);
            }
        }
        for (int i = 1; i < 4; ++i)
        {
            if (find_min[i] != find_min[i - 1])
                return vec[find_min[i]];
        }
    }
    void PrintTable() const
    {
        for (int i = 0; i < table.size(); ++i)
        {
            for (int j = 0; j < table[i].size(); ++j)
            {
                std::cout << "(" << vec[table[i][j]] << ", " << (table_2min[i][j] == -1 ? -1: vec[table_2min[i][j]]) << ")  ";
            }
            std::cout << std::endl;
        }
    }
};

SparseTable FillTable(int N)
{
    std::vector<int> vec;
    for (int i = 0; i < N; ++i)
    {
        int current;
        std::cin >> current;
        vec.push_back(current);
    }
    return SparseTable(vec);
}

void GetStatistics(const SparseTable& RMQ, int M)
{
    int from, to;
    for (int i = 0; i < M; ++i)
    {
        std::cin >> from >> to;
        std::cout << RMQ.GetMin2OnInterval(from - 1, to - 1) << std::endl;
    }
}

int main()
{
    int N, M;
    std::cin >> N >> M;
    SparseTable RMQ = FillTable(N);
    GetStatistics(RMQ, M);
    return 0;
}