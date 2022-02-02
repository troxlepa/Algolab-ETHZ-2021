#include<bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

#include <CGAL/nearest_neighbor_delaunay_2.h>

#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel    K;
typedef int                                                    Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  DT;
typedef DT::Vertex_handle Vertex_handle;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;


typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;
typedef std::pair<K::Point_2,Index> IPoint;


void testcase(int ttt){
  int n,m; K::FT r;
  std::cin >> n >> m >> r;
  std::vector<IPoint> pts(n);
  for(Index i=0;i<n;++i){
    int x,y; std::cin >> x >> y;
    pts[i] = {K::Point_2(x,y),i};
  }
  std::vector<std::pair<K::Point_2,K::Point_2>> ab(m);
  for(int i=0;i<m;++i){
    int a,b,c,d;
    std::cin >> a >> b >> c >> d;
    ab[i] = {K::Point_2(a,b),K::Point_2(c,d)};
  }
  boost::disjoint_sets_with_storage<> uf(n);
  
  
  K::FT r_sq = r*r;
  DT t;
  t.insert(pts.begin(), pts.end());
  
  graph G(n);
  
  std::vector<bool> vis(n,false);
  std::vector<int> color(n,0);
  
  const int BLACK = 0;
  const int WHITE = 1;
  std::queue<Vertex_handle> q;
  for (auto ut = t.finite_vertices_begin(); ut != t.finite_vertices_end(); ++ut) {
    Vertex_handle u = ut;
    int j = ut->info();
    if(vis[j]) continue;
    q.push(u);
    int cuc = WHITE;
    while(!q.empty()){
      int curr_size = q.size();
      for(int i=0;i<curr_size;++i){
        Vertex_handle v = q.front(); q.pop();
        int el = v->info();
        if((color[el] > 0) && (color[el] != cuc)){
          for(int i=0;i<m;++i){
            std::cout << "n";
          }
          std::cout << std::endl;
          return;
        }
        if(vis[el]) continue;
        vis[el] = true;
        color[el] = cuc;
        auto nb = t.incident_vertices(v);
        do{
          if(!t.is_infinite(nb) && CGAL::squared_distance(v->point(),nb->point()) <= r_sq){
            q.push(nb);
          }
        }while(++nb != t.incident_vertices(v));
      }
      cuc = std::abs(cuc-1);
    }
  }
  std::vector<Vertex_handle> neighbor_set;
  for(auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v) {
    neighbor_set.clear();

    auto c = t.incident_vertices(v);
    do {
      if (!t.is_infinite(c)){
        neighbor_set.push_back(c);
      }
    } while (++c != t.incident_vertices(v));

    for(int i = 0; i < (int)neighbor_set.size(); i++) {
      for(int j = i+1; j < (int)neighbor_set.size(); j++) {
        const auto v1 = neighbor_set[i];
        const auto v2 = neighbor_set[j];
        if (CGAL::squared_distance(v1->point(), v2->point()) <= r_sq && color[v1->info()] == color[v2->info()]) {
          for(int i=0;i<m;++i){
            std::cout << "n";
          }
          std::cout << std::endl;
          return;
        }
      }
    }
  }
  
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    if(t.segment(e).squared_length() <= r*r){
      Index i1 = e->first->vertex((e->second+1)%3)->info();
      Index i2 = e->first->vertex((e->second+2)%3)->info();

      int c1 = uf.find_set(i1);
      int c2 = uf.find_set(i2);
      if(c1 != c2){
        uf.link(c1,c2);
      }
    }
  }

  for(int i=0;i<m;++i){
    K::Point_2 p1 = ab[i].first;
    K::Point_2 p2 = ab[i].second;
    auto n1 = t.nearest_vertex(p1);
    auto n2 = t.nearest_vertex(p2);
    
    Index i1 = n1->info();
    Index i2 = n2->info();
    
    auto d1 = CGAL::squared_distance(n1->point(),p1);
    auto d2 = CGAL::squared_distance(n2->point(),p2);
    
    auto bbd = CGAL::squared_distance(p1,p2);
    
    if(bbd <= r*r){
      std::cout << "y";
      continue;
    }
    
    if(d1 > r*r || d2 > r*r){
      std::cout << "n";
      continue;
    }
    
    int c1 = uf.find_set(i1);
    int c2 = uf.find_set(i2);
    if(c1 == c2){
      std::cout << "y";
    }else{
      std::cout << "n";
    }
  }
  std::cout << std::endl;
}


int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase(t);
}