#include <bits/stdc++.h>

std::pair<std::pair<long,long>,std::pair<long,long>> rc(std::vector<std::vector<int>>& adj, std::vector<long>& c, int u){
  long x = 0;
  long y = 0;
  long z = 0;
  long w = 0;
  int sz = adj[u].size();

  long diff = 10000000000;

  for(int i=0;i<adj[u].size();++i){
    auto tmp = rc(adj,c,adj[u][i]);
    long new_x = tmp.first.first;
    long new_y = tmp.first.second;
    long new_z = tmp.second.first;
    long new_w = tmp.second.second;

    x += new_x;
    y += new_y;
    z += new_z;
    diff = std::min(diff, new_x - new_y);
  }
  
  
  long tres = c[u]+z;
  return {{tres,std::min(tres,y+diff)},{std::min(tres,y),w}};
}


void t2(){
  int n; std::cin >> n;
  std::vector<std::vector<int>> adj(n);
  
  for(int i=0;i<n-1;++i){
    int x,y; std::cin >> x >> y;
    adj[x].push_back(y);
  }
  std::vector<long> c(n);
  for(int i=0;i<n;++i){
    std::cin >> c[i];
  }
  auto res = rc(adj,c,0);
  std::cout << res.first.second << std::endl;
}


int main(){
  std::ios::sync_with_stdio(false);
  
  int t; std::cin >> t;
  while(t--) t2();
}