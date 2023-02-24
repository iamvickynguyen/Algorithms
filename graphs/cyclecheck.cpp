#include <bits/stdc++.h>
using namespace std;

enum {UNVISITED = -1, EXPLORED = -2, VISITED = -3};
vector<vector<int>> graph;
vector<int> status;
vector<int> parents;

bool cyclecheck(int u) {
	status[u] = EXPLORED;
	bool hascycle = false;
	for (auto v: graph[u]) {
		if (status[v] == UNVISITED) {
			parents[v] = u;
			hascycle |= cyclecheck(v);
		} else if (status[v] == EXPLORED) {
			if (v == parents[u]) // bidirectional
				continue;
			else // back edge (cycle)
				hascycle = true;
		} else if (status[v] == VISITED) {
				continue;
		}
	}
	status[u] = VISITED;
	return hascycle;
}

/* Graph with bidirectional edges
 * 0 4
 * 4 5
 * 1 2
 * 1 3
 * 2 3
 */

int main() {
	// create a graph
	int n = 6;
	graph.resize(n);
	graph[0].push_back(4);
	graph[4].push_back(0);
	graph[4].push_back(5);
	graph[5].push_back(4);
	graph[1].push_back(2);
	graph[2].push_back(1);
	graph[1].push_back(3);
	graph[3].push_back(1);
	graph[2].push_back(3);
	graph[3].push_back(2);

	status.assign(n, UNVISITED);
	parents.assign(n, -1);
	for (int i = 0; i < n; ++i) {
		if (status[i] == UNVISITED) {
			if (cyclecheck(i)) cout << i << ": cycle\n";
			else cout << i << ": no cycle\n";
		}
	}

	return 0;
}
