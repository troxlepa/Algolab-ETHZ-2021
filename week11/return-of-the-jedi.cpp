#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/pending/disjoint_sets.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

int quasi_kruskal(std::vector<std::tuple<int,int,int>>& edges, int ignore, int n, std::vector<int>& mst) {
  boost::disjoint_sets_with_storage<> uf(n);
  int out = 0;
  int cnt = 0;
  for(int i=0;i<edges.size();++i){
    if(i == ignore) continue;
    int u = std::get<0>(edges[i]);
    int v = std::get<1>(edges[i]);
    if(uf.find_set(u) != uf.find_set(v)){
      uf.union_set(u,v);
      out += std::get<2>(edges[i]);
      mst.push_back(i);
      cnt++;
      if(cnt == n-1) break;
    }
  }
  return out;
}

void testcase(){
  int n,q; std::cin >> n >> q;
  
  std::vector<std::tuple<int,int,int>> edges;
  for(int i=0;i<n-1;++i){
    for(int j=i+1;j<n;++j){
      int k; std::cin >> k;
      edges.emplace_back(i,j,k);
    }
  }
  
  auto cmp = [](auto& a, auto& b){return std::get<2>(a) < std::get<2>(b);};
  
  std::sort(edges.begin(), edges.end(), cmp);
  std::vector<int> mst;
  int base = quasi_kruskal(edges, -1,n, mst);
  int min_val = INT_MAX;
  
  for(int i=0;i<mst.size();++i){
    std::vector<int> empty;
    min_val = std::min(min_val,quasi_kruskal(edges,mst[i],n,empty));
    if(min_val == base) break;
  }
  std::cout << min_val << std::endl;
}

int main(){
  std::ios::sync_with_stdio(false);
  int t;std::cin >> t;
  while(t--) testcase();
}