#include <bits/stdc++.h>

void testcase(){
  int n, m, k; std::cin >> n >> m >> k;
  
  std::vector<int> x(n);
  for(int i=0;i<n;++i){
    std::cin >> x[i];
  }
  int rem = (n%m)>k ? 1: 0;
  int rounds = (n/m)+rem;
  std::vector<std::vector<std::pair<int,int>>> DP(rounds,std::vector<std::pair<int,int>>(n,std::make_pair(-1,-1)));
  
  for(int r=0;r<rounds;++r){
    // fixed size: number of coins to choose from
    int fsize = (n-1-k)%m+(r*m);
    for(int s=0;s<n-fsize;++s){
      if(r==0){
        DP[r][s].first = std::max(x[s],x[s+fsize]); 
        DP[r][s].second = std::max(x[s],x[s+fsize]); 
      }else{
        // check only those who overlap
        int hi = std::numeric_limits<int>::max();
        int lo = std::numeric_limits<int>::max();

        for(int j=s;j<=s+m;++j){

          int cmax = std::max(DP[r-1][j].first,DP[r-1][j].second);
          if(j==s){ // first subarray
            hi = std::min(hi,cmax);
          }else if(j==s+m){ // last subarray
            lo = std::min(lo,cmax);
          }else{
            lo = std::min(lo,cmax);
            hi = std::min(hi,cmax);
          }
        }
        DP[r][s].first = lo+x[s];
        DP[r][s].second = hi+x[s+fsize];
      }
    }
  }
  int result = std::numeric_limits<int>::max();
  // take min of max of last DP row
  for(int i=0;i<n;++i){
    int cmax = std::max(DP[rounds-1][i].first,DP[rounds-1][i].second);
    if(cmax > 0 && cmax < result_f){
      result = cmax;
    }
  }
  std::cout << result << std::endl;
}

int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0;i<t;++i){
    testcase();
  }
}