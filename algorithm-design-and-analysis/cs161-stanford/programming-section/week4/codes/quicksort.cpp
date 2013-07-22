#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>

using namespace std;

typedef vector<int> VI;

VI arr;

int partition(int start, int end) {
  int pivot = start;
  bool flag = false;
  for (int i = start + 1; i < end; i++) {
    if (arr[i] < arr[start] || (arr[i] == arr[start] && (flag = !flag))) swap(arr[++pivot], arr[i]);
  }
  swap(arr[start], arr[pivot]);
  return pivot;
}

void quicksort(int start, int end) {
  if (start >= end - 1) return;
  swap(arr[start], arr[start + (rand() % (end - start))]);
  int pivot = partition(start, end);
  quicksort(start, pivot);
  quicksort(pivot + 1, end);
}

int main() {
  int n;
  cin >> n;
  arr = VI(n);
  for (int i = 0; i < n; i++) cin >> arr[i];
  
  quicksort(0, n);
  
  for (int i = 0; i < n; i++) cout << arr[i] << endl;
  
  return 0;
}

