#include <iostream>

using namespace std;

long long adj[64];

int n, ans = 1;
long long allCovered;

bool search(int start, long long cover, int size) {
  if (cover == allCovered) return true;
  if (size == ans) return false;
  for (int i = start; i < n; i++) {
    if (search(i + 1, cover | adj[i], size + 1)) return true;
  }
  return false;
}

int main() {
  cin >> n;
  allCovered = (1L << n) - 1;
  
  int temp;
  for (int i = 0; i < n; i++) {
    adj[i] = 0;
    for (int j = 0; j < n; j++) {
      cin >> temp;
      adj[i] = (adj[i] << 1) + temp;
      if (i == j) adj[i]++;
    }
  }
  
  while (!search(0, 0L, 0)) ans++;
  
  cout << ans << endl;
  
  return 0;
}

