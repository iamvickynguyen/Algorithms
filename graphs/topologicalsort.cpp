#include <bits/stdc++.h>
using namespace std;

/* Graph with directed edges
 * 0 1
 * 1 2
 * 1 3
 * 2 4
 * 3 4
 */

int main() {
	// create a graph
	int n = 5;
	vector<vector<int>> graph(n);
	graph[0].push_back(1);
	graph[1].push_back(2);
	graph[1].push_back(3);
	graph[2].push_back(4);
	graph[3].push_back(4);

	// Topological sort
	// Take edges with 0 in-degree
	// Need to implement the in-degree vector when solving actual problem
	vector<int> indegree(n);
	indegree[0] = 0;
	indegree[1] = 1;
	indegree[2] = 1;
	indegree[3] = 1;
	indegree[4] = 2;

	priority_queue<int, vector<int>, greater<int>> pq;
	for (int i = 0; i < n; ++i) {
		if (indegree[i] == 0) {
			pq.push(i);
		}
	}

	while (!pq.empty()) {
		int u = pq.top();
		pq.pop();

		cout << u << " ";

		for (auto &v: graph[u]) {
			--indegree[v];
			if (indegree[v] == 0) pq.push(v);
		}
	}
	
	return 0;
}
