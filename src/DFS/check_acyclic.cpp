// Задача: дан ориентированный граф на n вершинах и m рёбрах (1≤n,m≤1000). Необходимо вывести True, если граф
// содержит цикл, и False в противном случае.

// Sample Input:
// 4 4
// 1 2
// 4 1
// 2 3
// 3 1
// Sample Output:
// True
// Memory Limit: 256 MB
// Time Limit: 5 seconds



#include <iostream>
#include <vector>
#include <utility>

using namespace std;

vector<size_t> used;
vector<vector<size_t> > g;

bool dfs(size_t v)
{	
	used[v] = 1;
	for (vector<size_t>::iterator it = g[v].begin(); it != g[v].end(); ++it)
	{
		if (used[*it] == 0)
		{
			if (dfs(*it))
			{
				return true;
			}
		}
		else if (used[*it] == 1)
		{
			return true;
		}
	}
	used[v] = 2;
	return false;
}


int main()
{
	size_t n, m;
	cin >> n >> m;

	g.assign(n, vector<size_t>());

	for (size_t i = 0; i < m; ++i)
	{
		size_t v1, v2;
		cin >> v1 >> v2;
		g[v1-1].push_back(v2-1);

	}

	used.assign(n, 0);

	for (size_t i = 0; i < n; ++i)
	{
		if (used[i] == 0)
		{
			if (dfs(i))
			{
				cout << "True" << endl;
				return 0;
			}
		}
	}

	cout << "False" << endl;

	return 0;
}
