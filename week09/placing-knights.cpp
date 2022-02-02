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
  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

void testcase(){
  int n; std::cin >> n;

  graph G(n*n);
  edge_adder adder(G); 
  
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  
  std::vector<std::pair<int,int>> poss(8);
  poss[0] = {1,2};
  poss[1] = {1,-2};
  poss[2] = {2,1};
  poss[3] = {2,-1};
  poss[4] = {-1,2};
  poss[5] = {-1,-2};
  poss[6] = {-2,1};
  poss[7] = {-2,-1};
  
  std::vector<std::vector<int>> DP(n,std::vector<int>(n,0));
  for(int i=0;i<n;++i){
    for(int j=0;j<n;++j){
      std::cin >> DP[i][j];
    }
  }
  int cnt = 0;
  for(int i=0;i<n;++i){
    for(int j=0;j<n;++j){
      if(!DP[i][j]) continue;
      cnt++;
      bool isWhite = (i+j) % 2 == 0;
      if(isWhite){
        adder.add_edge(v_source,i+n*j,1);
      }else{
        adder.add_edge(i+n*j,v_sink,1);
      }
      for(int k=0;k<poss.size();++k){
        int x = i+poss[k].first;
        int y = j+poss[k].second;
        if(x>=0 && y>= 0 && x < n && y < n){
          if(!DP[x][y]) continue;
          if(isWhite) adder.add_edge(i+n*j,x+n*y,1);
          else adder.add_edge(x+n*y,i+n*j,1);
        }
      }
    }
  }

  int flow = boost::push_relabel_max_flow(G, v_source, v_sink);

  std::cout << cnt-flow << std::endl;
}

int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}