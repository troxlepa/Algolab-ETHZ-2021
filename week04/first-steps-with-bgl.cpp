#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;


void testcase(){
  int n,m;
  std::cin >> n >> m;
  weighted_graph G(4);
  weight_map weights = boost::get(boost::edge_weight, G);

  edge_desc e;
  
  for(int i=0;i<m;++i){
    int u,v,w; std::cin >> u >> v >> w;
    e = boost::add_edge(u, v, G).first; weights[e]=w;
  }
  std::vector<edge_desc> mst;    // vector to store MST edges (not a property map!)

  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
  int tw = 0;
  for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
    tw += weights[*it];
  }
  int mx = 0;
  std::vector<int> dist_map(n);
  auto s = boost::vertex(0,G);
  boost::dijkstra_shortest_paths(G, s, boost::distance_map(boost::make_iterator_property_map(dist_map.begin(),boost::get(boost::vertex_index, G))));
  for(int i=0;i<n;++i){
    if(dist_map[i] > mx){
      mx = dist_map[i];
    }
  }
  std::cout << tw << " " << mx << std::endl;
}

int main(){
  int t;std::cin >> t;
  for(int i=0;i<t;++i){
    testcase();
  }
}