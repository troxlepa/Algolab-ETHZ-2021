#include<bits/stdc++.h>

struct NL{
  long t;
  long n;
  long g;
  long l;
  long z;
};

struct N{
  long t;
  long n;
  long g;
  long z;
};
  
N compute(const std::vector<std::vector<std::pair<int,int>>>& adj, int n, const std::vector<long>& g, int q){
  // leaf node
  if(adj[q].size() == 0){
    N out = N{.t = 0,.n = 1,.g = g[q],.z = 0};
    return out;
  }
  std::vector<NL> children;
  for(auto i : adj[q]){
    N c = compute(adj,n,g,i.first);
    NL cl{.t=c.t,.n=c.n,.g=c.g,.l=i.second,.z=c.z};
    children.push_back(cl);
  }
  
  auto cmp = [](NL a, NL b){
    return (a.z+a.l) * b.n < (b.z+b.l) * a.n;
  };
  
  std::sort(children.begin(),children.end(),cmp);
  
  long t = 0;
  long nodes = 0;
  long gold = g[q];
  long z = 0;
  
  for(auto c : children){
    t += c.l;
    nodes += c.n;
    gold += c.g - (t*c.n);
    t += c.t;
    t += c.l;
    z += c.l + c.z;
  }
  return N{.t = t,.n = nodes+1,.g = gold,.z=zac};
}

void testcase(){
  int n; std::cin >> n;
  std::vector<long> g(n+1);
  g[0] = 0;
  for(int i=1;i<n+1;++i){
    std::cin >> g[i];
  }
  std::vector<std::vector<std::pair<int,int>>> adj(n+1, std::vector<std::pair<int,int>>());
  for(int i=0;i<n;++i){
    int u,v,l; std::cin >> u >> v >> l;
    adj[u].push_back({v,l});
  }
  
  N result = compute(adj,n,g,0);
  
  std::cout << result.g << std::endl;
}


int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}