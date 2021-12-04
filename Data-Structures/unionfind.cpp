#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

class UF {
	private:
		vi parent, rank;
	public:
		UF(int N) {
			parent.assign(N, 0);
			for (int i = 0; i < N; i++) parent[i] = i;
			rank.assign(N, 0);
		}

		int find(int v) {
			if (parent[v] != v) parent[v] = find(parent[v]);
			return parent[v];
		}

		bool same_set(int a, int b) {
			return find(a) == find(b);
		}

		void union_set(int a, int b) {
			int ra = find(a), rb = find(b);
			if (ra == rb) return;
			if (rank[ra] < rank[rb]) swap(ra, rb);
			parent[rb] = ra;
			if (rank[ra] == rank[rb]) rank[ra]++;
		}
};

int main() {
	UF uf(5);
	uf.union_set(1,2);
	cout << "same_set(1, 2): " << uf.same_set(1,2) << '\n';
	cout << "same_set(1, 3): " << uf.same_set(1, 3) << '\n';
	for (int i = 0; i < 5; i++) cout << "root of " << i << ": " << uf.find(i) << '\n';

	return 0;
}