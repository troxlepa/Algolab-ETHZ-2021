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
  int m, n, k, c; std::cin >> m >> n >> k >> c;
  int u,v;
  int preval = n*m;
  graph G(n*m+preval);
  edge_adder adder(G);

  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  
  for(int fst = 0; fst < (n-1)*m; ++fst){
    adder.add_edge(fst,preval+fst+n,1);
    adder.add_edge(fst+n,preval+fst,1);
  }
  for(int col = 0;col < n*m-1;++col){
    if(col % n == n-1) continue;
    adder.add_edge(col,preval+col+1,1);
    adder.add_edge(col+1,preval+col,1);
  }
  
  for(int i=0;i<k;++i){
    std::cin >> u >> v;
    int idx = u*n+v;
    adder.add_edge(v_source,preval+idx,1);
  }
  
  // add edges to sink
  for(int i=0;i<m;++i){
    for(int j=0;j<n;++j){
      if(i==0 || j==0 || i==m-1 || j==n-1){
        int f1 = i==0;
        f1 += j==0;
        f1 += i==m-1;
        f1 += j==n-1;
        adder.add_edge(i*n+j,v_sink,f1);
      }
    }
  }
  
  for(int i=0;i<n*m;++i){
    adder.add_directed_edge(preval+i,i,c);
  }
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  std::cout << flow << std::endl;
}

int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}