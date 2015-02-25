// Задача: дан неориентированный граф на n вершинах и m рёбрах (1≤n,m≤100000), а также номера вершин u и v.
// Выведите количество рёбер на кратчайшем пути между вершинами u и v или -1, если пути между ними в графе нет.

// Sample Input:
// 4 4
// 1 2
// 4 1
// 2 3
// 3 1
// 2 4
// Sample Output:
// 2
// Memory Limit: 256 MB
// Time Limit: 5 seconds



#include <iostream>
#include <vector>
#include <queue>

using namespace std;
vector<vector<long long> > g;

vector<bool> used;
vector<long long> length;
queue<long long> go;

void walk(long long start, long long finish)
{	
	vector<long long>& v = g.at(start);

	for (long long i = 0; i < v.size(); ++i)
	{
		if (!used.at(v.at(i)))
		{
			used.at(v.at(i)) = 1;	
			length.at(v.at(i)) = length.at(start) + 1;
			go.push(v.at(i));
		}
	}
}

long long bfs(long long start, long long finish)
{
	go.push(start);
	while (!go.empty())
	{
		if (used.at(finish))
		{
			return length.at(finish);
		}
		walk(go.front(), finish);
		go.pop();
		
	}
	return -1;		
}


int main()
{
	long long n, m;
	cin >> n >> m;

	g.assign(n, vector<long long>());
	length.assign(n, m + 1);
	used.assign(n, 0);

	for (long long i = 0; i < m; ++i)
	{
		long long v1, v2;
		cin >> v1 >> v2;
		g.at(v1 - 1).push_back(v2 - 1);
		g.at(v2 - 1).push_back(v1 - 1);
	}

	cin >> n >> m;

	length.at(n-1) = 0;

	cout << bfs(n-1, m-1) << endl;

	return 0;
}
