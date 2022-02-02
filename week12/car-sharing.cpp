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
  int n,ns;
  std::cin >> n >> ns;
  std::vector<int> init(ns);
  int num_cars = 0;
  for(int i=0;i<ns;++i){
    std::cin >> init[i];
    num_cars += init[i];
  }
  
  std::vector<std::vector<int>> si(ns,std::vector<int>());
  for(int i=0;i<ns;++i){
    si[i].push_back(0);
  }

  std::vector<std::vector<int>> qt(n);
  
  for(int i=0;i<n;++i){
    int s,t,d,a,p;
    std::cin >> s >> t >> d >> a >> p;
    si[s-1].push_back(d);
    si[t-1].push_back(a);
    qt[i] = {s-1,t-1,d,a,p};
  }
  
  std::vector<int> sZs(ns);
  long cum = 0;
  for(int i=0;i<ns;++i){
    sZs[i] = cum;
    cum += si[i].size();
  }
  
  graph G(cum);
  edge_adder adder(G);
  
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  
  for(int i=0;i<ns;++i){
    adder.add_edge(v_source,sZs[i],init[i],0);
  }
  
  for(int i=0;i<ns;++i){
    std::sort(si[i].begin(),si[i].end());
  }
  
  for(int i=0;i<n;++i){
    int len = qt[i][3] - qt[i][2];
    int start_offset = sZs[qt[i][0]];
    int desti_offset = sZs[qt[i][1]];
    if(qt[i][2] >= cum) std::cout << qt[i][2] << " " << cum << std::endl;
    qt[i][2] += start_offset;
    qt[i][3] += desti_offset;
    adder.add_edge(qt[i][2],qt[i][3],1,(len*100)-qt[i][4]);
  }
  

  
  for(int j=0;j<ns;++j){
    for(int i=0;i<si[j].size()-1;++i){
      long diff = si[j][i+1] - si[j][i];
      if(diff <= 0) continue;
      adder.add_edge(si[j][i],si[j][i+1],10000,diff*100);
    }
    int last = si[j][si[j].size()-1];
    long dist = 100000 - last;
    adder.add_edge(last,v_sink,10000,dist*100);
  }


  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
  int cost = boost::find_flow_cost(G);
  long sub = num_cars*(100*100000);
  std::cout << -(cost-sub) << std::endl;
  
}

int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}