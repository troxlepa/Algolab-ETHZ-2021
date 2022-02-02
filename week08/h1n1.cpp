#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<double,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> DT;
typedef K::Point_2 Point_2;
typedef DT::Vertex_handle Vertex_handle;
typedef DT::Face_handle Face_handle;


void sc(DT & t) {
  std::priority_queue<std::pair<double, Face_handle>> q;

  for(auto f = t.all_faces_begin(); f != t.all_faces_end(); ++f) {
    if (t.is_infinite(f)) {
      q.emplace(std::numeric_limits<long>::max(), f);
    }
    f->info() = 0;
  }

  while(!q.empty()) {
    auto p = q.top(); q.pop();
    const auto cost = p.first;
    auto handle = p.second;
    if (handle->info() >= cost) {
      continue;
    }
    handle->info() = cost;
    for(int i = 0; i < 3; i++) {
      const auto neighbor = handle->neighbor(i);
      if (t.is_infinite(neighbor) || neighbor->info() != 0) {
        continue;
      }
      const auto& v1 = handle->vertex((i+1)%3)->point();
      const auto& v2 = handle->vertex((i+2)%3)->point();
      const double min_cost = std::min(CGAL::squared_distance(v1, v2), cost);
      q.emplace(min_cost, neighbor);
    }
  }
}

int main(){
  std::ios::sync_with_stdio(false);
  int n;
  while(std::cin >> n && n > 0){
    int x,y;
    std::vector<Point_2> infected(n);
    for(int i=0;i<n;++i){
      std::cin >> x >> y;
      infected[i] = Point_2(x,y);
    }
    
    DT dt;
    dt.insert(infected.begin(),infected.end());
    sc(dt);
    int m; std::cin >> m;
    for(int i=0;i<m;++i){
      long d;
      std::cin >> x >> y >> d;
      Point_2 p(x,y);
      auto np = dt.nearest_vertex(p)->point();
      if(CGAL::squared_distance(np,p) < d){
        std::cout << 'n';
        continue;
      }
      double mel = 4*d;
      if(dt.locate(p)->info() >= mel){
        std::cout << 'y';
      }else{
        std::cout << 'n';
      }
    }
    std::cout << std::endl;
  }
  
}
