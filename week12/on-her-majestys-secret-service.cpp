#include<bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
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

std::vector<int> dijkstra_dist(const weighted_graph &WG, int s) {
  std::vector<int> dist_map(boost::num_vertices(WG));
  boost::dijkstra_shortest_paths(WG, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, WG))));
  return dist_map;
  
}

bool isFeasibleTwo(std::vector<std::vector<int>> &M, int a, int s, int t, int d){
  graph G(a+s+s);
  edge_adder adder(G);
  auto v_src = boost::add_vertex(G);
  auto v_dst = boost::add_vertex(G);
  for(int i=0;i<a;++i){
    adder.add_edge(v_src,i,1,0);
  }
  for(int i=0;i<s+s;++i){
    adder.add_edge(a+i,v_dst,1,0);
  }
  for(int i=0;i<a;++i){
    for(int j=0;j<s;++j){
      if(M[i][j] <= t){
        adder.add_edge(i,a+j,1,0);
        if(d >= 0 && M[i][j] + d <= t){
          adder.add_edge(i,a+s+j,1,0);
        }
      }
    }
  }
  int flow = boost::push_relabel_max_flow(G, v_src, v_dst);
  return flow == a;
}

void testcase(){
  int n,m,a,s,c,d;
  std::cin >> n >> m >> a;
  std::cin >> s >> c >> d;
  
  weighted_graph WG(n+s);
  
  for(int i=0;i<m;++i){
    char w;
    int x,y,z;
    std::cin >> w >> x >> y >> z;
    boost::add_edge(x,y,z,WG);
    if(w == 'L'){
      boost::add_edge(y,x,z,WG);
    }
  }
  std::vector<int> va(a);
  for(int i=0;i<a;++i){
    std::cin >> va[i];
  }
  std::vector<int> vs(s);
  for(int i=0;i<s;++i){
    int si; std::cin >> si;
    boost::add_edge(si,n+si,d,WG);
    vs[i] = n+si;
  }

  std::vector<std::vector<int>> MAT(a,std::vector<int>(s));
  std::set<int> vals_set;
  for(int i=0;i<a;++i){
    int src = va[i];
    std::vector<int> dist_map = dijkstra_dist(WG, src);
    for(int j=0;j<s;++j){
      MAT[i][j] = dist_map[vs[j]];
      vals_set.insert(dist_map[vs[j]]);
      if(c==2)vals_set.insert(dist_map[vs[j]]+d);
    }
  }
  std::vector<int> vals(vals_set.begin(),vals_set.end());
  int left = 0;
  int right = vals.size()-1;
  int mid = right;
  while(left < right){
    mid = (left+right) / 2;
    int cap = c==2 ? d : -1;
    bool feasible = isFeasibleTwo(MAT,a,s,vals[mid],cap);
    if(feasible){
      right = mid;
    }else{
      left = mid+1;
    }
  }
  std::cout << vals[left] << std::endl;
}

int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}