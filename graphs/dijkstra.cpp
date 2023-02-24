#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
constexpr int INF = 1e9;

/* 
 * Graph:
 * 4 5
 * 0 1 5
 * 0 2 2
 * 0 3 10
 * 2 3 3
 * 1 3 1
 * src=0
 */

int main() {
	// create a graph
	int n = 4, s = 0;
	vector<vector<pair<int, int>>> graph(4);
	graph[0].push_back({1, 5});
	graph[1].push_back({0, 5});
	graph[0].push_back({2, 2});
	graph[2].push_back({0, 2});
	graph[0].push_back({3, 10});
	graph[3].push_back({0, 10});
	graph[1].push_back({3, 1});
	graph[3].push_back({1, 1});
	graph[2].push_back({3, 3});
	graph[3].push_back({2, 3});
	
	vector<int> dist(n, INF);
	dist[s] = 0;
	priority_queue<ii, vector<ii>, greater<ii>> pq;
	pq.push({0, s});

	// (Modified) Dijkstra's algorithm
	while (!pq.empty()) {
		auto [d, u] = pq.top();
		pq.pop();
		if (d > dist[u]) continue;
		for (auto &[v, w]: graph[u]) {
			if (dist[u] + w >= dist[v]) continue;
			dist[v] = dist[u] + w; // relax
			pq.push({dist[v], v});
		}
	}

	for (int i = 0; i < n; ++i) {
		cout << "Dist. from " << s << " to " << i << ": " << dist[i] << '\n';
	}

	return 0;
}
