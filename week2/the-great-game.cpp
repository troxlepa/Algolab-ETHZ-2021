#include <bits/stdc++.h>

int dmin(int n, int pos);
int dmax(int n, int pos);

std::vector<int> DP_min;
std::vector<int> DP_max;
std::vector<std::vector<int>> vec;

int dmin(int n, int pos){
  if(pos == n) return 0;
  if(DP_min[pos]!=-1) return DP_min[pos];
  int res = INT_MAX;
  for(int el : vec[pos]){
    res = std::min(res, 1+dmax(n, el));
  }
  DP_min[pos] = res;
  return res;
}

int dmax(int n, int pos){
  if(pos == n) return 0;
  if(DP_max[pos]!=-1) return DP_max[pos];
  int res = -1;
  for(int el : vec[pos]){
    res = std::max(res, 1+dmin(n, el));
  }
  DP_max[pos] = res;
  return res;
}

void testcase(){
  int n, m, r, b;
  std::cin >> n >> m >> r >> b;
  
  vec.clear();
  DP_min.clear();
  DP_max.clear();
  vec.resize(n);
  DP_min.resize(n+1,-1);
  DP_max.resize(n+1,-1);
  
  for(int i=0;i<m;++i){
    int u,v;
    std::cin >> u >> v;
    vec[u].push_back(v);
  }

  int res_red = dmin(n, r);
  int res_bla = dmin(n, b);
  

  if(res_red == res_bla){
    if(res_red % 2 == 0){
      std::cout << 1 << std::endl; 
    }else{
      std::cout << 0 << std::endl; 
    }
    return;
  }
  int rr = res_red<res_bla?0:1;
  std::cout << rr << std::endl; 

}

int main(){
  std::ios::sync_with_stdio(false);
  int t;std::cin >> t;
  for(int i=0;i<t;++i){
    testcase();
  }
}