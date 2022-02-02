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
  int h,w; std::cin >> h >> w;
  std::string s; std::cin >> s;
  
  int target_length = s.size();
  char first = 'A';
  char last = 'Z';
  int fv = first;
  int fl = last;
  int num_chars = fl-fv+1;
  
  graph G(num_chars+(num_chars*num_chars));
  edge_adder adder(G);
  
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);

  std::vector<int> occ(num_chars,0);
  for(int i=0;i<s.size();++i){
    occ[((int)s[i])-fv]++;
  }
  
  std::vector<std::string> front(h);
  std::vector<std::string> back(h);
  std::string line;
  
  std::vector<std::vector<int>> DP(num_chars, std::vector<int> (num_chars,0));
  
  for(int i=0;i<h;++i){
    std::cin >> front[i];
  }
  for(int i=0;i<h;++i){
    std::cin >> back[i];
  }
  
  int ef,eb;
  int sub = 0;
  // front page
  for(int i=0;i<h;++i){
    for(int j=0;j<w;++j){
      ef = ((int)front[i][j]) - fv;
      eb = ((int)back[i][w-j-1]) - fv;
      if(occ[ef] == 0 && occ[eb] == 0){
      
      }
      else if(ef == eb){
        occ[ef]--;
        sub++;
      }else if(occ[ef] == 0){
        occ[eb]--;
        sub++;
      }else if(occ[eb] == 0){
        occ[ef]--;
        sub++;
      }else if(ef > eb){
        DP[ef][eb]++;
      }else{
        DP[eb][ef]++;
      }
    }
  }
  int cnt = 0;
  for(int i=0;i<num_chars;++i){
    for(int j=0;j<i;++j){
      if(DP[i][j] != 0){
        adder.add_edge(i,num_chars+cnt,DP[i][j]);
        adder.add_edge(j,num_chars+cnt,DP[i][j]);
        adder.add_edge(num_chars+cnt,v_sink,DP[i][j]);
        cnt++;
      }
    }
  }
  
  for(int i=0;i<num_chars;++i){
    if(occ[i] != 0)
      adder.add_edge(v_source,i,occ[i]);
  }
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  if(flow+sub == target_length){
    std::cout << "Yes" << std::endl;
  }else{
    std::cout << "No" << std::endl;
  }
}

int main(){
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
  int t; std::cin >> t;
  while(t--) testcase();
}