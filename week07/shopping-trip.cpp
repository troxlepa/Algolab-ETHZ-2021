#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

// Custom edge adder class, highly recommended
class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = capacity; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

void testcase(){
  int n, m, s; std::cin >> n >> m >> s;
  std::vector<int> stores(s);
  
  graph G(n);
  edge_adder adder(G);
  
  for(int i=0;i<s;++i){
    std::cin >> stores[i];
  }
  int u,v;
  for(int i=0;i<m;++i){
    std::cin >> u >> v;
    adder.add_edge(u,v,1);
  }
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  for(int i=0;i<s;++i){
    adder.add_edge(stores[i],v_sink,1);
  }
  adder.add_edge(v_source,0,INT_MAX);
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  
  if(flow == s){
    std::cout << "yes" << std::endl;
  }else{
    std::cout << "no" << std::endl;
  }
  
  
}

int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}