#include <boost/config.hpp>
#include <bits/stdc++.h>
#include <boost/graph/biconnected_components.hpp>
#include <boost/graph/adjacency_list.hpp>

namespace boost
{
  enum edge_component_t { edge_component };
    BOOST_INSTALL_PROPERTY(edge, component);
}

using namespace boost;

  typedef adjacency_list < vecS, vecS, undirectedS,
    no_property, property < edge_component_t, std::size_t > >graph_t;


void testcase(){
  int n,m;
  std::cin >> n >> m;
  graph_t G(n);
  for(int i=0;i<m;++i){
    int x,y;
    std::cin >> x >> y;
    boost::add_edge(x,y,G);
  }

  boost::property_map < graph_t, edge_component_t >::type
  component = get(edge_component, G);

  std::size_t num_comps = biconnected_components(G, component);
  graph_traits < graph_t >::edge_iterator ei, ei_end;
  
  std::vector<int> cs(num_comps,0);
  
  for (boost::tie(ei, ei_end) = edges(G); ei != ei_end; ++ei){
    cs[component[*ei]]++;
  }
  // output
  std::vector<std::pair<int,int>> bridges;
  for(boost::tie(ei, ei_end) = edges(G); ei != ei_end; ++ei){
    if(cs[component[*ei]] == 1){
      int u = source(*ei,G);
      int v = target(*ei,G);
      bridges.push_back({std::min(u,v),std::max(u,v)});
    }
  }
  std::sort(bridges.begin(),bridges.end());
  std::cout << bridges.size() << std::endl;
  for(int i=0;i<bridges.size();++i){
    std::cout << bridges[i].first << " " << bridges[i].second << std::endl;
  }
}

int main(){
  std::ios::sync_with_stdio(false);
  int t;std::cin >> t;
  for(int i=0;i<t;++i){
    testcase();
  }
}