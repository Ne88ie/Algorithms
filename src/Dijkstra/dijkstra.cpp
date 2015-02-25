// Задача: дан ориентированный взвешенный граф на n вершинах и m рёбрах (1≤n≤1000, 0≤m≤100000).
// Вес ребра — натуральное число, не превышающее 1000. Последняя строка содержит номера двух вершин u и v.
// Выведите кратчайшее расстояние между вершинами u и v или -1, если в графе нет пути из u в v.

// Sample Input:
// 4 4
// 1 2 1
// 4 1 2
// 2 3 2
// 1 3 5
// 1 3
// Sample Output:
// 3
// Memory Limit: 256 MB
// Time Limit: 5 seconds



#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct node
{
	long long path;
	long long order;
	long long index;
	bool used;

	node(long long p, long long o, long long i)
		: path(p)
		, order(o)
		, index(i)
		, used(0)
	{
	}
};

vector<node> nodes;
long long n, m;

struct edge
{
	node* to;
	long long weight;

	edge(node* n, long long w)
		: to(n)
		, weight(w)
	{
	}
};

vector<vector<edge> > g;

class d_ary_heap
{
	long long d;
	vector<node*> data_;

	void sift(long long ind)
	{
		long long start = (ind + 1) * d - d + 1; // самый левый ребенок
		pair<long long, long long> min_chaild(data_.at(ind)->path, ind);
		for (long long i = start; i < start + d && i < data_.size(); ++i)
		{
			if (data_.at(i)->path < min_chaild.first)
			{
				min_chaild = make_pair(data_.at(i)->path, i);
			}
		}
		if (data_.at(ind)->path > min_chaild.first)
		{
			swap(data_.at(ind), data_.at(min_chaild.second));
			data_.at(ind)->index = ind;
			data_.at(min_chaild.second)->index = min_chaild.second;
			sift(min_chaild.second);
		}
	}

	void min_heapify(long long ind)
	{
		if (ind == 0) return;
		long long parent = (ind - 1)/d;
		if (data_.at(parent)->path > data_.at(ind)->path)
		{
			swap(data_.at(parent), data_.at(ind));
			data_.at(parent)->index = parent;
			data_.at(ind)->index = ind;
			min_heapify(parent);
		}
	}

public:
	// void print()
	// {
	// 	cout << "\tprint heap {";
	// 	for (long long i = 0; i < data_.size(); ++i)
	// 	{
	// 		cout << data_.at(i)->order + 1 << ":" << data_.at(i)->path << ",  "; 
	// 	}
	// 	cout << "}\n";
	// }

	d_ary_heap(long long ary, long long begin)
		: d(ary)
	{
		for (long long i = 0; i < nodes.size(); ++i)
		{
			if (i != begin)
			{
				data_.push_back(&nodes.at(i));
				data_.back()->index = data_.size() - 1;
			}
		}
		data_.push_back(&nodes.at(begin));
		swap(data_.front(), data_.back());
		data_.front()->index = 0;
		data_.back()->index = data_.size() - 1;
		// cout << "make ";
		// print(); 
	}

	long long extract_min()
	{
		swap(data_.front(), data_.back());
		data_.front()->index = 0;
		data_.back()->index = data_.size() - 1;
		long long tmp = data_.back()->order;
		data_.pop_back();
		if (data_.size() > 1) sift(0);
		// cout << "extra";
		// print();
		return tmp;
	}

	void relax(long long from, edge& on)
	{
		long long new_path = nodes.at(from).path + on.weight;
		if (nodes.at(on.to->order).path > new_path)
		{
			nodes.at(on.to->order).path = new_path;
			min_heapify(nodes.at(on.to->order).index);
		}
		// cout << "relax";
		// print();
	}

	bool empty()
	{
		return data_.empty();
	}

};

long long dijkstra(long long begin, long long end)
{
	nodes.at(begin).path = 0;
	long long d = m/n < 2 ? 2 : m/n;
	d_ary_heap heap(d, begin);

	while (!heap.empty())
	{
		long long next = heap.extract_min();
		nodes.at(next).used = 1;
		vector<edge>& edges = g.at(next);
		for (long long i = 0; i < edges.size(); ++i)
		{
			if (!edges.at(i).to->used)
			{
				heap.relax(next, edges.at(i));
			}
		}
	}
	long long result = nodes.at(end).path == m * 1000 + 1 ? -1 : nodes.at(end).path;
	return result;

}


int main()
{
	cin >> n >> m;

	for (long long i = 0; i < n; ++i)
	{
		nodes.push_back(node(m * 1000 + 1, i, 0));
	}

	g.assign(n, vector<edge>());

	for (long long i = 0; i < m; ++i)
	{
		long long v1, v2, w;
		cin >> v1 >> v2 >> w;
		g.at(v1 - 1).push_back(edge(&nodes.at(v2 - 1), w));
	}

	long long u, v;
	cin >> u >> v;

	cout << dijkstra(u-1, v-1) << endl;

	return 0;
}
