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
  void add_directed_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
  
  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

void testcase(){
  int n, m; std::cin >> n >> m;
  
  graph G(n+m);
  edge_adder adder(G);
  
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  
  std::vector<int> winners(n,0);
  int a,b,c;
  int cs = 0;
  for(int i=0;i<m;++i){
    int idx = n+i;
    std::cin >> a >> b >> c;
    if(c==1){
      winners[a]++;//adder.add_edge(a,idx,1);
    }else if(c==2){
      winners[b]++;//adder.add_edge(b,idx,1);
    }else{
      adder.add_edge(a,idx,1);
      adder.add_edge(b,idx,1);
      adder.add_edge(idx,v_sink,1);
      cs++;
    }
  }
  long sum = 0;
  long wh_sum = 0;
  int si;
  bool flag = false;
  for(int i=0;i<n;++i){
    std::cin >> si;
    adder.add_edge(v_source, i, si-winners[i]);
    if(si-winners[i] < 0){
      flag = true;
    }
    sum += (si-winners[i]);
  }
  if(flag || sum != cs){
    std::cout << "no" << std::endl;
    return;
  }
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  if(flow == sum){
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