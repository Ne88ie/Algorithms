// Задача: дан взвешенный ориентированный граф на n вершинах и m рёбрах (1≤n≤1000, 0≤m≤10000). Вес ребра — целое
// число, по модулю не превышающее 1000. Выведите True, если в графе есть цикл отрицательного веса, и False в
// противном случае.

// Sample Input:
// 4 4
// 1 2 1
// 4 1 2
// 2 3 2
// 3 1 -5
// Sample Output:
// True
// Memory Limit: 256 MB
// Time Limit: 10 seconds


#include <iostream>
#include <vector>
#include <string>

using namespace std;

long long n, m;

struct node
{
	long long order;
	long long path;

	node(long long o, long long p)
		: order(o)
		, path(p)
	{
	}
};

vector<node> nodes;

struct edge
{
	node* from;
	node* to;
	long weight;

	edge(node* f, node* t, size_t w)
		: from(f)
		, to(t)
		, weight(w)
	{
	}
};

vector<edge> edges;

bool relax(edge& e)
{
	if(e.to->path > e.from->path + e.weight)
	{
		e.to->path = e.from->path + e.weight;
		return true;
	}
	return false;
}

string belman_ford()
{
	bool is_negative_cycle = false;

	nodes.at(0).path = 0;

	for (long long i = 0; i < n - 1; ++i)
	{
		for (long long e = 0; e < edges.size(); ++e)
		{
			relax(edges.at(e));
		}
	}

	for (long long e = 0; e < edges.size(); ++e)
	{
		if (relax(edges.at(e)))
		{
			is_negative_cycle = true;
			break;
		}
	}

	return is_negative_cycle ? "True" : "False";
}


int main()
{
	cin >> n >> m;

	for (long long i = 0; i < n; ++i)
	{
		nodes.push_back(node(i, m * 1000));
	}

	long u, v, w;
	for (long long i = 0; i < m; ++i)
	{	
		cin >> u >> v >> w;
		edges.push_back(edge(&nodes.at(u - 1), &nodes.at(v - 1), w));

	}

	cout << belman_ford() << endl;

	return 0;
}
