///3
#include<bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor             vertex_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};

void testcase(){
  int c,g,k,a;
  long b;
  std::cin >> c >> g >> b >> k >> a;
  
  graph G(c);
  edge_adder adder(G);  
  auto c_map = boost::get(boost::edge_capacity, G);
  auto r_map = boost::get(boost::edge_reverse, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  
  for(int i=0;i<g;++i){
    int x,y,d,e;
    std::cin >> x >> y >> d >> e;
    adder.add_edge(x,y,e,d);
  }
  
  vertex_desc v_src = boost::add_vertex(G);
  
  adder.add_edge(v_src,k,10e9,0);
  
  long max = 10e9;
  long min = 0;
  long mid;
  long flow;
  while(min < max){
    mid = (max+min) / 2;
    
    auto v_dest = boost::add_vertex(G);
    adder.add_edge(a,v_dest,mid,0);
    
    boost::successive_shortest_path_nonnegative_weights(G, v_src, v_dest);
    long cost = boost::find_flow_cost(G);
    flow = 0;
    out_edge_it e, eend;
    for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_src,G), G); e != eend; ++e) {
        flow += c_map[*e] - rc_map[*e];     
    }
    
    bool valid = cost <= b;
    if(flow != mid){
      max = mid;
      continue;
    }
    if(valid){
      min = mid+1;
    }else{
      max = mid;
    }
  }
  
  auto v_dest = boost::add_vertex(G);
  adder.add_edge(a,v_dest,mid,0);
  
  boost::successive_shortest_path_nonnegative_weights(G, v_src, v_dest);
  long cost = boost::find_flow_cost(G);
  flow = 0;
  out_edge_it e, eend;
  for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_src,G), G); e != eend; ++e) {
      flow += c_map[*e] - rc_map[*e];     
  }
  
  bool valid = cost <= b;
  if(valid && flow == mid){
    std::cout << mid << std::endl;
  }else{
    std::cout << mid-1 << std::endl;
  }
}

int main(){
  std::ios::sync_with_stdio(false);
  int t;std::cin >> t;
  while(t--) testcase();
}