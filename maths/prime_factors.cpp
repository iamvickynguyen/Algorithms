#include <iostream>
#include <unordered_map>
using namespace std;

unordered_map<int, int> prime_factors(int n) {
	unordered_map<int, int> power;
	while (n % 2 == 0) {
		++power[2];
		n >>= 1;
	}

	for (int i = 3; i * i <= n; i += 2) {
		while (n % i == 0) {
			++power[i];
			n /= i;
		}
	}

	if (n != 1) power[n] = 1;
	return power;
}

int main() {
	int n = 4800;
	unordered_map<int, int> power = prime_factors(n);
	for (auto& [k, v]: power) cout << k << ":" << v << '\n';
	return 0;
}
