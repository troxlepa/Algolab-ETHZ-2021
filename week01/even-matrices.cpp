#include <bits/stdc++.h>

std::array<std::array<int,201>, 201> arr = {};

int sum(int x1, int x2, int y2) {
  return arr[x2][y2] - arr[x1-1][y2] - arr[x2][0] + arr[x1-1][0];
}

void solve(){
  int N; std::cin >> N;
  for(int i = 1; i <= N; i++) {
    for(int j = 1; j <= N; j++){
      int num; std::cin >> num;
      arr[i][j] = arr[i-1][j] + arr[i][j-1] - arr[i-1][j-1] + num;
    }
  }

  long res= 0;

  for(int i = 1; i <= N; i++) {
    for(int j = i;  j <= N; j++) {
      int odd = 0;
      int even = 0;
      for(int x = 1; x <= N; x++) {
        if(sum(i,j,x) % 2 == 1) {
          odd++;
        }else{
          even++;
        }
      }

      res += (even*(even-1))/2 + even + (odd*(odd-1))/2;
    }
  }

  std::cout << res << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) solve();
}