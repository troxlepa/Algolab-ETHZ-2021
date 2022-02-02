#include <bits/stdc++.h>

void testcase(){
  int n,m;
  long x;
  int k;
  std::cin >> n >> m >> x >> k;
  
  int u,v;
  long p;
  std::vector<std::vector<std::pair<int,long>>> adj(n,std::vector<std::pair<int,long>>());
  for(int i=0;i<m;++i){
    std::cin >> u >> v >> p;
    adj[u].push_back({v,p});
  }
  
  for(int i=0;i<n;++i){
    if(adj[i].size() == 0){
      for(unsigned int j=0;j<adj[0].size();++j){
        auto el = adj[0][j];
        adj[i].push_back(el);
      }
    }
  }
  
  std::vector<long> DP1(n,-1);
  DP1[0] = 0;
  int start_idx = -1;
  
  for(int i=0;i<k;++i){
    std::vector<long> DP2(n,-1);
    for(int j = 0;j<n;++j){
      if(DP1[j] != -1){
        for(unsigned int nb = 0; nb < adj[j].size();++nb){
          auto dest = adj[j][nb];
          DP2[dest.first] = std::max(DP2[dest.first],DP1[j] + dest.second);
          if(DP2[dest.first] >= x && start_idx == -1){
            start_idx = i;
            break;
          }
        }
      }
    }
    DP1 = DP2;
  }
  
  if(start_idx >= 0){
    std::cout << start_idx+1 << std::endl;
  }else{
    std::cout << "Impossible" << std::endl;
  }
}

int main(){
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  int t; std::cin >> t;
  while(t--) testcase();
}