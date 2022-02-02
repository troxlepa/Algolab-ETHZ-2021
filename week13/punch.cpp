#include<bits/stdc++.h>

typedef long int LL;
std::vector<std::vector<LL>> DP(101,std::vector<LL>(10001));
void testcase(){
  int n, k; std::cin >> n >> k;
  std::vector<std::pair<int,int>> cv(n);
  for(int i=0;i<n;++i){
    int x,y;
    std::cin >> x >> y;
    cv[i] = {x,y};
  }
  for(int i=0;i<101;++i){
    for(int j=0;j<10001;++j){
      DP[i][j] = 100000000;
    }
  }
  
  std::vector<std::vector<int>> DIFF(n+1,std::vector<int>(k+1,0));
  DP[0][0] = 0;
  DIFF[0][0] = 0;

  for(int i=1;i<n+1;++i){
    int c = cv[i-1].first;
    int v = cv[i-1].second;
    for(int j=0;j<k+1;++j){
      DP[i][j] = DP[i-1][j];
      DIFF[i][j] = DIFF[i-1][j];
      if(j < v){
        if(DP[i][j] > c){
          DP[i][j] = c;
          DIFF[i][j] = 1;
        }
      }else{
        if(DP[i][j] > DP[i-1][j-v]+c){
          DP[i][j] = DP[i-1][j-v]+c;
          DIFF[i][j] = DIFF[i-1][j-v] + 1;
        }else if(DP[i][j] == DP[i-1][j-v]+c){
          if(DIFF[i][j] < DIFF[i-1][j-v] + 1) DIFF[i][j]= DIFF[i-1][j-v] + 1;
        }
        if(DP[i][j] > DP[i][j-v]+c){
          DP[i][j] = DP[i][j-v]+c;
          DIFF[i][j] = DIFF[i][j-v];
        }else if(DP[i][j] == DP[i][j-v]+c){
          if(DIFF[i][j] < DIFF[i][j-v]) DIFF[i][j]= DIFF[i][j-v];
        }
      }
    }
    for(int j = k-v;j<k+1;++j){
      if(DP[i][k] > DP[i-1][j]+c){
        DP[i][k] = DP[i-1][j]+c;
        DIFF[i][k] = DIFF[i-1][j] + 1;
      }else if(DP[i][k] == DP[i-1][j]+c){
        if(DIFF[i][k] < DIFF[i-1][j] + 1) DIFF[i][j]= DIFF[i-1][j] + 1;
      }
      if(DP[i][k] > DP[i][j]+c){
        DP[i][k] = DP[i][j]+c;
        DIFF[i][k] = DP[i][j];
      }else if(DP[i][k] == DP[i][j]+c){
        if(DIFF[i][k] < DIFF[i][j]) DIFF[i][k]= DIFF[i][j];
      }
    }
  }
  
  std::cout << DP[n][k] << " " << DIFF[n][k] << std::endl;
}


int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}