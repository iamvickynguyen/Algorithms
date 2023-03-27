#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

void find_paths(vector<vector<int>>& paths, vector<int>& path, vector<vector<int>>& parents, const int n, const int u) {
	if (u == -1) {
		paths.push_back(path);
		return;
	}	
	
	for (int p: parents[u]) {
		path.push_back(u);
		find_paths(paths, path, parents, n, p);
		path.pop_back();
	}
}

vector<vector<int>> get_paths(vector<vector<int>>& graph, const int n, const int src, const int dest) {
	vector<vector<int>> paths;
	vector<int> path;
	vector<vector<int>> parents(n);

	vector<int> dist(n, INT_MAX);

	// bfs
	queue<int> q;
	q.push(src);
	dist[src] = 0;
	parents[src].push_back(-1);

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int v: graph[u]) {
			if (dist[v] > dist[u] + 1) {
				dist[v] = dist[u] + 1;
				q.push(v);
				parents[v].clear();
				parents[v].push_back(u);
			} else if (dist[v] == dist[u] + 1) {
				parents[v].push_back(u);
			}
		}
	}

	// recursively find paths
	find_paths(paths, path, parents, n, dest);
	
	return paths;
}

int main() {
	const int n = 6;
	
	vector<vector<int>> graph(n);
	vector<pair<int, int>> edges = {{0,1}, {0,2}, {1,3}, {1,4}, {2,3}, {3,5}, {4,5}};

	for (auto& [u, v]: edges) {
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	// get all shortest paths from 0 to 5
	vector<vector<int>> paths = get_paths(graph, n, 0, 5);

	// output
	for (auto& path: paths) {
		for (int i = path.size() - 1; i >= 0; --i) cout << path[i] << " ";
		cout << '\n';
	}

	return 0;
}
