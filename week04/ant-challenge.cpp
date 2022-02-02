#include <bits/stdc++.h>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace boost;

typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::undirectedS,boost::no_property,boost::property<boost::edge_weight_t, int>> weighted_graph;
typedef long long int LL;
typedef boost::graph_traits<weighted_graph>::edge_iterator edge_it;

struct Edge{
  int x;
  int y;
  int w;
  Edge(int nx,int ny,int nw){
    x = nx;
    y = ny;
    w = nw;
  }
};

bool operator<(const Edge& a, const Edge& b) {
  return a.w > b.w;
}


LL dijkstra_dist(const weighted_graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<LL> dist_map(n); //exterior property
  boost::dijkstra_shortest_paths(G, s,
  boost::distance_map(boost::make_iterator_property_map(dist_map.begin(),
  boost::get(boost::vertex_index, G))));
  return dist_map[t];
}

void testcase(){
  int n,e,s,a,b;
  std::cin >> n >> e >> s >> a >> b;
  int t1,t2;
  std::vector<std::pair<int,int>> tx(e);
  std::vector<std::vector<int>> w(e,std::vector<int>(s,-1));
  weighted_graph G(n);
  for(int i=0;i<e;++i){
    std::cin >> t1 >> t2;
    tx[i] = {t1,t2};
    for(int j=0;j<s;++j){
       std::cin >> w[i][j];
    }
  }
  
  std::vector<int> hives(s);
  for(int i=0;i<s;++i){
    std::cin >> hives[i];
  }

  std::vector<Edge> ES;
  for(int i=0;i<s;++i){
    weighted_graph sg(n);
    for(int j=0;j<e;++j){
      boost::add_edge(tx[j].first,tx[j].second,w[j][i],sg);
    }
    
    std::vector<bool> visited(n,false);
    
    visited[hives[i]] = true;
    edge_it e_beg, e_end;
    std::priority_queue<Edge> Q;
    for(int q=0;q<e;++q){
      if(tx[q].first == hives[i] || tx[q].second == hives[i])
        Q.push(Edge(tx[q].first,tx[q].second,w[q][i]));
    }
    while(!Q.empty()){
      Edge ne = Q.top();
      Q.pop();
      if(visited[ne.x] && visited[ne.y]){
        continue;
      }else{
        int vx = visited[ne.y] ? ne.x : ne.y;
        visited[ne.x] = true;
        visited[ne.y] = true;
        ES.push_back(ne);
        for(int q=0;q<e;++q){
          if(tx[q].first == vx || tx[q].second == vx){
            if(!(visited[tx[q].first] && visited[tx[q].second])){
              Q.push(Edge(tx[q].first,tx[q].second,w[q][i]));
            }
          }
        }
      }
      
    }
    for(int aa=0;aa < ES.size();++aa){
      boost::add_edge(ES[aa].x,ES[aa].y,ES[aa].w, G);
    }
  }
  
  LL atob = dijkstra_dist(G,a,b);
  std::cout << atob << std::endl;
}

int main(){
  int t; std::cin >> t;
  for(int i=0;i<t;++i){
    testcase();
  }
}