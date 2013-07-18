#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> VI;

VI arr;

long long count(int start, int end) {
  if (start >= end - 1) return 0;
  int mid = (start + end) / 2;
  long long ans = count(start, mid) + count(mid, end);
  
  VI merge(end - start);
  int lidx = start, uidx = mid, midx = 0;
  while (lidx < mid && uidx < end) {
    if (arr[lidx] > arr[uidx]) {
      ans += mid - lidx;
      merge[midx++] = arr[uidx++];
    } else merge[midx++] = arr[lidx++];
  }
  
  while (lidx < mid) merge[midx++] = arr[lidx++];
  while (uidx < end) merge[midx++] = arr[uidx++];
  
  for (int i = 0; i < merge.size(); i++) arr[start + i] = merge[i];
  
  return ans;
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int temp;
    cin >> temp;
    arr.push_back(temp);
  }
  
  cout << count(0, n) << endl;
  
  return 0;
}

