#include <bits/stdc++.h>


int dp[101][100001];

void testcase(){
  int n,m,k; std::cin >> n >> m >> k;
  
  std::vector<int> v(n);
  
  for(int i=0;i<n;++i){
    std::cin >> v[i];
  }
  
  int sum = 0;
  int back_pos = 0;
  
  std::vector<int> f(n);
  
  for(int i=0;i<n;++i){
    sum += v[i];
    while(sum > k){
      sum -= v[back_pos++];
    }
    if(sum == k){
      f[i] = i-back_pos+1;
    }
  }

  for(int i = 0; i <= n; i++) {
    dp[0][i] = 0;
  }
  for(int i = 1; i <= m; i++) {
    dp[i][0] = -1;
  }

  for(int i = 1; i <= m; i++) {
    for(int j = 1; j <= n; j++) {
      int last = f[j-1];
      if (last > 0 && dp[i-1][j-last] != -1) {
        dp[i][j] = std::max(dp[i-1][j-last] + last, dp[i][j-1]);
      } else {
        dp[i][j] = dp[i][j-1];  
      }
    }
  }
  int res = dp[m][n];
  if (res == -1) {
    std::cout << "fail" << std::endl;
  } else {
    std::cout << res << std::endl;
  }
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}