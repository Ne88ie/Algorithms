#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<int> topsort, comp;
vector<bool> used;
vector<vector<int> > graph, graphT;

void dfs1(int v)
{
  used[v]=true;
  for (vector<int>::iterator it = graphT[v].begin(); it !=graphT[v].end(); ++it)
    if (!used[*it])
      dfs1(*it);
  topsort.push_back(v);
}


void dfs2(int v)
{
  used[v] = true;
  comp.push_back(v);
  for (vector<int>::iterator it = graph[v].begin(); it != graph[v].end(); ++it)
    if (!used[*it])
      dfs2(*it);
}

int main(int argc, char const *argv[])
{
  int n;
  int m;
  cin >> n >> m;
  graph.assign(n, vector<int>(0));
  graphT.assign(n, vector<int>(0));
  vector<int> scc(n, 0);


  int vertex1;
  int vertex2;

  vector<pair<int, int> > eds;
  for (size_t i = 0; i < m; ++i)
  {
    cin >> vertex1 >> vertex2;
    vertex1--;
    vertex2--;
    graph[vertex1].push_back(vertex2);
    graphT[vertex2].push_back(vertex1);
    eds.push_back(make_pair(vertex1, vertex2));
  }

  used.assign(n, false);
  for (size_t i = 0; i < n; ++i)
    if (!used[i])
      dfs1(i);

  int c = 0;
  used.assign(n, false);
  for (size_t i = 0; i < n; ++i)
  {
    int v = topsort[n - 1 -i];
    if (!used[v])
    {
      dfs2(v);
      for (size_t j = 0; j < comp.size(); ++j)
        scc[comp[j]] = c;
      ++c;
      comp.clear();
    }
  }

  set<pair<int, int> > edges;
  for (size_t i = 0; i < m; ++i)
    if (scc[eds[i].first] != scc[eds[i].second])
      edges.insert(make_pair(scc[eds[i].first], scc[eds[i].second]));

  cout << edges.size() << endl; // вернуть число рёбер в конденсированном графе

  return 0;
}
