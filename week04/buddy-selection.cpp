#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/maximum_weighted_matching.hpp>

using namespace boost;

typedef adjacency_list < vecS, vecS, undirectedS, no_property >graph_t;
typedef graph_traits<graph_t>::vertex_descriptor vertex_t;


void testcase(){
  int n, c, f; std::cin >> n >> c >> f;
  
  std::string s;
  
  std::vector<std::vector<std::string>> v(n,std::vector<std::string>(c));
  for(int i=0;i<n;++i){
    for(int j=0;j<c;++j){
      std::cin >> v[i][j];
    }
  }
  
  for(int i=0;i<n;++i){
    std::sort(v[i].begin(),v[i].end());
  }
  
  graph_t G;

  for(int i=0;i<n;++i){
    std::unordered_set<std::string> ss(v[i].begin(),v[i].end()); 
    for(int j=i+1;j<n;++j){
      int res = std::count_if(v[j].begin(), v[j].end(), [&](std::string k) {return ss.find(k) != ss.end();});
      if(res > f) boost::add_edge(i,j,G);
    }
  }

  std::vector<vertex_t> matemap(n);
  bool success = checked_edmonds_maximum_cardinality_matching(G, &matemap[0]);
  
  int size = matching_size(G, &matemap[0]);
  
  if(size*2 == n){
    std::cout << "not optimal" << std::endl;
  }else{
    std::cout << "optimal" << std::endl;
  }
}

int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0;i<t;++i){
    testcase();
  }
}