#include <bits/stdc++.h>
// BGL includes
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
  int n; std::cin >> n;
  
  graph G(n);
  edge_adder adder(G);
  auto c_map = boost::get(boost::edge_capacity, G);
  auto r_map = boost::get(boost::edge_reverse, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  
  int all_m = 0;
  std::vector<std::pair<int,int>> menu(n);
  for(int i=0;i<n;++i){
      int ai,ci; std::cin >> ai >> ci;
      
      adder.add_edge(v_source,i, ai,ci);
      
      menu[i] = {ai,ci};
      all_m += ai;
  }
  int all_s = 0;
  std::vector<std::pair<int,int>> student(n);
  for(int i=0;i<n;++i){
    int si,pi; std::cin >> si >> pi;
    
    adder.add_edge(i,v_sink, si,20-pi);
    
    student[i] = {si,pi};
    all_s += si;
  }

  std::vector<std::pair<int,int>> freezer(n-1);
  for(int i=0;i<n-1;++i){
    int vi,ei; std::cin >> vi >> ei;
    
    adder.add_edge(i,i+1,vi,ei);
    
    freezer[i] = {vi,ei};
  }
  
  int num_served = 0;
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
  int cost = boost::find_flow_cost(G);
  num_served = flow;
  if(num_served == all_s){
    std::cout << "possible ";
  }else{
    std::cout << "impossible ";
  }
  std::cout << num_served << " ";
  
  std::cout << -cost+20*flow << std::endl;
  
}

int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}