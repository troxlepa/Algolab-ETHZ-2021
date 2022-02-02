#include <bits/stdc++.h>

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

  std::vector<std::vector<int>> dp(2,std::vector<int>(n+1));

  for(int i = 0; i <= n; i++) {
    dp[0][i] = 0;
  }
  
  for(int i = 1; i <= m; i++) {
    dp[1][0] = -1;
    for(int j = 1; j <= n; j++) {
      int last = f[j-1];
      if (last && dp[0][j-last] != -1) {
        dp[1][j] = std::max(dp[0][j-last] + last, dp[1][j-1]);
      } else {
        dp[1][j] = dp[1][j-1];  
      }
    }
    dp[0] = dp[1];
    std::fill(dp[1].begin(),dp[1].end(),0);
  }
  int res = dp[0][n];
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