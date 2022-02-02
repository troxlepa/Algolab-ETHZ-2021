#include <bits/stdc++.h>

typedef long LL;
typedef std::pair<int,int> PII;
typedef std::vector<int> V1;
typedef std::vector<V1> V2;
typedef std::vector<V2> V3;

void testcase(){
  int n, m;
  LL a,b;
  LL p, h,w;
  std::cin >> n >> m;
  std::cin >> a >> b;
  std::cin >> p >> h >> w;

  LL pi, hi;
  std::vector<std::pair<LL,LL>> AA(n);
  for(int i=0;i<n;++i){
    std::cin >> pi >> hi;
    AA[i] = {pi,hi};
  }
  
  LL wi;
  std::vector<LL> BB(m);
  for(int i=0;i<m;++i){
    std::cin >> wi;
    BB[i] = wi;
  }

  std::sort(BB.begin(),BB.end());
  std::reverse(BB.begin(),BB.end());

  std::vector<LL> nWPotions(n+1,-1);
  for(int j=0;j<n+1;++j){
    LL bPotionsNeeded = -1;
    LL bPotSum = 0;
    for(int i=0;i<m;++i){
      if(bPotSum >= w+(j*a) && bPotionsNeeded == -1){
        bPotionsNeeded = i;
      }
      bPotSum += BB[i];
    }
    if(bPotSum >= w+(j*a) && bPotionsNeeded == -1){
      bPotionsNeeded = m;
    }
    nWPotions[j] = bPotionsNeeded;
  }
  
  std::vector<std::vector<LL>> DP(n+1,std::vector<LL>(h+1,-1));
  // base case
  DP[0][0] = 0;
  
  for(int i=0;i<n;++i){ // for all potions
    for(int k=n;k>=0;--k){
      for(int j=0;j<h+1;++j){
        if(DP[k][j] != -1){
          if(DP[k+1][std::min(h,j+AA[i].second)] <= DP[k][j] + AA[i].first){
            DP[k+1][std::min(h,j+AA[i].second)] = DP[k][j] + AA[i].first;
          }
        }
      }
    }
  }
  
  LL pmin = LONG_MAX;
  bool changed = false;
  for(int i=0;i<n+1;++i){
    if(nWPotions[i] != -1){
      if(DP[i][h] >= p + nWPotions[i] * b){
        pmin = std::min(i+nWPotions[i], pmin);
        changed = true;
      }
    }
  }
  if(!changed){
      std::cout << -1 << std::endl;
      return;
  }

  std::cout << pmin << std::endl;
}


int main(){
  std::ios::sync_with_stdio(false);
  int t;std::cin >>t;
  while(t--) testcase();
}