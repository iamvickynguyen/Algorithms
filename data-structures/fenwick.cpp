#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

// Reference:
// https://github.com/mission-peace/interview/blob/master/src/com/interview/tree/FenwickTree.java
class FenwickTree {
private:
  vll ft;

  /**
   * To get next
   * 1) 2's complement of get minus of index
   * 2) AND this with index
   * 3) Add it to index
   */
  int getNext(int idx) { return idx + (idx & -idx); }

  /**
   * To get parent
   * 1) 2's complement to get minus of index
   * 2) AND this with index
   * 3) Subtract that from index
   */
  int getParent(int idx) { return idx - (idx & -idx); }

public:
  FenwickTree(int n) { ft.assign(n + 1, 0); }
  FenwickTree(const vll &input) { create(input); }

  void update(ll val, int idx) {
    idx++;
    while (idx < ft.size()) {
      ft[idx] += val;
      idx = getNext(idx);
    }
  }

  void create(const vll &input) {
    int n = input.size();
    ft.assign(n + 1, 0);
    for (int i = 0; i < n; i++) {
      update(input[i], i);
    }
  }

  // get sum from [0, idx-1]
  ll getSum(int idx) {
    ll sum = 0;
    while (idx > 0) {
      sum += ft[idx];
      idx = getParent(idx);
    }
    return sum;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  FenwickTree ft(5);
  ft.update(2, 0);
  ft.update(1, 1);
  ft.update(-5, 2);
  ft.update(20, 3);
  ft.update(1, 4);
  cout << "Fenwick Tree after update: [2,1,-5,20,1] \n";
  cout << "sum [0, 4] = " << ft.getSum(5) << '\n';
  cout << "sum [0, 2] = " << ft.getSum(3) << '\n';

  cout << "Fenwick Tree with initial vector [1,2,-5,3,4]\n";
  vll v = {1, 2, -5, 3, 4};
  FenwickTree t(v);
  cout << "sum [0, 3] = " << t.getSum(4) << '\n';
  cout << "sum [1, 4] = " << (t.getSum(5) - t.getSum(1)) << '\n';

  return 0;
}
