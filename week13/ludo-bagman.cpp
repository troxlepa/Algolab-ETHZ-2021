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
typedef boost::graph_traits<graph>::vertex_descriptor           vertex_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

// Custom edge adder class
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
  int e, w, m, d;
  std::cin >> e >> w >> m >> d;
  int p,l; std::cin >> p >> l;
  
  graph G(2*(w+e));
  edge_adder adder(G);
  
  vertex_desc v_src = boost::add_vertex(G);
  vertex_desc v_nxt = boost::add_vertex(G);
  vertex_desc v_dst = boost::add_vertex(G);
  vertex_desc v_fdd = boost::add_vertex(G);
  
  adder.add_edge(v_src,v_nxt,p-(l*e),0);
  adder.add_edge(v_fdd,v_dst,p-(l*w),0);
  
  for(int i=0;i<e;++i){
    adder.add_edge(v_src,i,l,0);
    adder.add_edge(v_nxt,i,p-(l*e),0);
    adder.add_edge(v_nxt,e+i,p-(l*e),0);
  }
  
  for(int i=0;i<w;++i){
    adder.add_edge((2*e)+i,v_dst,l,0);
    adder.add_edge((2*e)+i,v_fdd,p-(l*w),0);
    adder.add_edge((2*e)+w+i,v_fdd,p-(l*w),0);
  }
  
  for(int i=0;i<m;++i){
    int u,v,r; std::cin >> u >> v >> r;
    adder.add_edge(u,(2*e)+v,1,r);
  }
  
  for(int i=0;i<d;++i){
    int u,v,r; std::cin >> u >> v >> r;
    adder.add_edge(e+u,(2*e)+w+v,1,r);
  }
  
  long flow = boost::push_relabel_max_flow(G, v_src, v_dst);
  
  if(flow == p){
    boost::successive_shortest_path_nonnegative_weights(G, v_src, v_dst);
    int cost = boost::find_flow_cost(G);
    std::cout << cost << "\n";
  }else{
    std::cout << "No schedule!" << std::endl;
  }
}

int main(){
  std::ios::sync_with_stdio(false);
  
  int t;std::cin >> t;
  while(t--) testcase();
}