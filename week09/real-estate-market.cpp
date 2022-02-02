#include <bits/stdc++.h>

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
typedef  boost::graph_traits<graph>::vertex_descriptor      vertex_desc;
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
  int n,m,s; std::cin >> n >> m >> s;

  graph G(n+m+s);
  edge_adder adder(G); 
  
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_real_sink = boost::add_vertex(G);

  for(int i=0;i<n;++i){
    adder.add_edge(v_source,i,1,0);
  }
  for(int i=0;i<s;++i){
    int l; std::cin >> l;
    adder.add_edge(n+m+i,v_real_sink,l,0);
  }
  for(int i=0;i<m;++i){
    int l; std::cin >> l;
    adder.add_edge(n+i,n+m+l-1,1,0);
  }
  for(int i=0;i<n;++i){
    for(int j=0;j<m;++j){
      int l; std::cin >> l;
      adder.add_edge(i,n+j,1,100-l);
    }
  }

  int flow1 = boost::push_relabel_max_flow(G, v_source, v_real_sink);
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_real_sink);
  int cost1 = boost::find_flow_cost(G);

  std::cout << flow1 << " " << (flow1*100)-cost1 << std::endl;
}

int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}