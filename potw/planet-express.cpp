#include<bits/stdc++.h>
#include <boost/graph/visitors.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>

#include <boost/graph/dijkstra_shortest_paths_no_color_map.hpp>
#include <boost/graph/graph_traits.hpp>

#include <boost/graph/strong_components.hpp>

using namespace boost;

typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::directedS,boost::no_property,boost::property<boost::edge_weight_t, int>> weighted_graph;
typedef graph_traits<weighted_graph>::vertex_descriptor vertex_t;


void testcase(){


// 1. read input
  int n, m ,k ,T;
  std::cin >> n >> m >> k >> T;
  std::vector<int> ttv(T);
  for(int i=0;i<T;++i){
    std::cin >> ttv[i];
  }
  weighted_graph G(n);
  int u,v,c;
  for(int i=0;i<m;++i){
    std::cin >> u >> v >> c;
    boost::add_edge(u,v,c,G);
  }
// 2. construct teleportation network (create new edges)
  std::vector<int> scc_map(n); // exterior property map
  int nscc = boost::strong_components(G,
    boost::make_iterator_property_map(scc_map.begin(),
    boost::get(boost::vertex_index, G)));
    
  std::vector<std::vector<int>> nc(n);
  for(int i=0;i<T;++i){
    int vidx = ttv[i];
    int cp = scc_map[vidx];
    nc[cp].push_back(vidx);
  }
  
  for(int i=0;i<nc.size();++i){
    int s = nc[i].size();
    if(s > 1){
      vertex_t qq = boost::add_vertex(G);
      for(int j=0;j<s;++j){
        boost::add_edge(qq,nc[i][j],s-1,G);
        boost::add_edge(nc[i][j],qq,0,G);
      }
    }
  }
// 3. add new vertex as src with weight 0 to all warehouses
  vertex_t v_src = boost::add_vertex(G);
  for(int i=0;i<k;++i){
    boost::add_edge(v_src,i,0,G);
  }
// 4. shortest path from source to v(n-1)
  std::vector<long> d(num_vertices(G));
  std::vector<vertex_t> p(num_vertices(G));
  dijkstra_shortest_paths_no_color_map(G, v_src,
    predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, G))).
    distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, G))));
  if(d[n-1] <= 1000000){
    std::cout << d[n-1] << std::endl;
  }else{
    std::cout << "no" << std::endl; 
  }
}

int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}