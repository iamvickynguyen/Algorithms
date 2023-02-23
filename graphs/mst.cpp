#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using iii = tuple<int, int, int>;

class UF {
private:
  vi parent, rank;

public:
  UF(int N) {
    parent.assign(N, 0);
    for (int i = 0; i < N; i++)
      parent[i] = i;
    rank.assign(N, 0);
  }

  int find(int v) {
    if (parent[v] != v)
      parent[v] = find(parent[v]);
    return parent[v];
  }

  bool is_same_set(int a, int b) { return find(a) == find(b); }

  void union_set(int a, int b) {
    int ra = find(a), rb = find(b);
    if (ra == rb)
      return;
    if (rank[ra] < rank[rb])
      swap(ra, rb);
    parent[rb] = ra;
    if (rank[ra] == rank[rb])
      rank[ra]++;
  }
};

// Kruskal's algorihm
class MST {
public:
  int N;
  vector<iii> EL;

  MST(const int n) : N(n), uf(n) {}

  void add_edge(const int u, const int v, const int w) {
    EL.push_back({w, u, v});
  }

  void run_mst() {
    sort(EL.begin(), EL.end());

    int edge_count = 0;
    for (auto [w, u, v] : EL) {
      if (edge_count == (N - 1))
        break;
      if (!uf.is_same_set(u, v)) {
        uf.union_set(u, v);
        ++edge_count;
        mst_cost += w;
        mst_edges.push_back({u, v, w}); // order: u, v, w
      }
    }
  }

  int get_mst_cost() { return mst_cost; }

  vector<iii> get_mst_edges() { return mst_edges; }

private:
  UF uf;
  vector<iii> mst_edges;
  int mst_cost = 0;
};

/*
input: n, m; n: number of nodes, m: number of edges. Then follow m lines, each
line consisting of u, v and w indicating that there is an edge between u and v
in the graph with weight w
4 4
0 1 1
1 2 2
1 3 3
2 3 0
output: minimum spanning tree cost, and edges in lexicographic order
3
0 1
1 2
2 3
*/

int main() {
  MST mst(4);
  mst.add_edge(0, 1, 1);
  mst.add_edge(1, 2, 2);
  mst.add_edge(1, 3, 3);
  mst.add_edge(2, 3, 0);

  mst.run_mst();
  cout << mst.get_mst_cost() << '\n';

  vector<iii> mst_edges = mst.get_mst_edges();

  // order u, v
  for (auto &[u, v, w] : mst_edges) {
    if (u > v)
      swap(u, v);
  }

  sort(mst_edges.begin(), mst_edges.end());

  for (auto &[u, v, w] : mst_edges) {
    cout << u << " " << v << '\n';
  }

  return 0;
}
