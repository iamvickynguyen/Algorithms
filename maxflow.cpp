#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
#define all(x) (x).begin(), (x).end()
#define pb push_back

// Reference: https://github.com/stevenhalim/cpbook-code/blob/master/ch8/maxflow.cpp
// Note: a bit slower than stevenhalim's implementation, but more space efficient and
// finding flow value of an edge is easier

const ll INF = 1e18;

class max_flow {
	private:
	int V;
	vector<unordered_map<int, pll>> graph;	// adjacency list with values are pair(cap, flow)
	vi dist, last;

	bool BFS(int s, int t) {					// find augmenting path
		dist.assign(V, -1); dist[s] = 0;
		queue<int> q({s});
		while (!q.empty()) {
			int u = q.front(); q.pop();
			if (u == t) break;
			for (auto it = graph[u].begin(); it != graph[u].end(); it++) {
				int v = it->first;
				auto &[cap, flow] = it->second;
				if ((cap - flow > 0) && (dist[v] == -1)) {
					dist[v] = dist[u] + 1;
					q.push(v);
				}
			}
		}
		return dist[t] != -1;
	}
	
	ll DFS(int u, int t, ll f = INF) {
		if ((u == t) || (f == 0)) return f;
		for (auto &edge: graph[u])	{				// from last edge
			int v = edge.first;
			auto &[cap, flow] = edge.second;
			if (dist[v] != dist[u] + 1) continue;			// not part of the layer graph
			if (ll pushed = DFS(v, t, min(f, cap - flow))) {
				flow += pushed;
				auto &rflow = graph[v][u].second;
				rflow -= pushed;
				return pushed;
			}
		}
		return 0;
	}
	
	public:
	max_flow(int initialV) : V(initialV) {
		graph.assign(V, unordered_map<int, pair<ll, ll>>());
	}

	void add_edge(int u, int v, ll w, bool directed = true) {
		if (u == v) return;
		graph[u][v] = {w, 0};
		graph[v][u] = {directed ? 0 : w, 0};
	}

	ll dinitz(int s, int t) {
		ll mf = 0;
		while (BFS(s, t)) {
			last.assign(V, 0);
			while (ll f = DFS(s, t)) mf += f;
		}
		return mf;
	}

	ll get_flow_edge(int u, int v) {
		return graph[u][v].second;
	}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	max_flow mf(5);
	mf.add_edge(0,1,100);
	mf.add_edge(0,2,100);
	mf.add_edge(1,2,1);
	mf.add_edge(1,3,100);
	mf.add_edge(2,3,99);
	ll flow = mf.dinitz(0,3);
	cout << flow << '\n';

    return 0;
}

