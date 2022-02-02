#include <CGAL/squared_distance_2.h>
#include<bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Triangulation_vertex_base_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel      K;
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_2<K>                   Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT,K>     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;
typedef Triangulation::Face_handle                             Face_handle;
typedef long int LL;

void testcase(){
  int n,m;
  K::FT r;
  std::cin >> n >> m >> r;
  std::vector<K::Point_2> trees(n);
  for(int i=0;i<n;++i){
    long x,y; std::cin >> x >> y;
    trees[i] = K::Point_2(x,y);
  }
  
  Triangulation t;
  t.insert(trees.begin(),trees.end());

  std::priority_queue<std::pair<K::FT,Face_handle>> q;

  for(auto f = t.all_faces_begin();f != t.all_faces_end();++f){
    if(t.is_infinite(f)){
      q.push({std::numeric_limits<double>::max(), f});
    }else{
      const K::FT face_len_squared = squared_radius(f->vertex(0)->point(), f->vertex(1)->point(), f->vertex(2)->point());
      q.push({face_len_squared, f});
    }
  }
  
  while(!q.empty()){
    auto el = q.top(); q.pop();
    K::FT radius = el.first;
    auto f = el.second;
    
    if(f->info() >= radius) continue;
    f->info() = radius;
    
    for(int i=0;i<3;++i){
      Face_handle f2 = f->neighbor(i);
      if(t.is_infinite(f2) || f2->info() != 0) continue;
      auto v1 = f->vertex((i+1)%3)->point();
      auto v2 = f->vertex((i+2)%3)->point();
      K::FT dist = CGAL::squared_distance(v1,v2);
      if(radius < dist) dist = radius;
      q.push({dist,f2});
    }
  }

  for(int i=0;i<m;++i){
    long x,y;
    K::FT s;
    std::cin >> x >> y >> s;
    K::Point_2 p(x,y);
    
    auto nearest = t.nearest_vertex(p);
    K::FT cr = K::FT(s+r);
    K::FT clearance = cr * cr;
    if(CGAL::squared_distance(nearest->point(),p) < clearance){
      std::cout << "n";
      continue;
    }
    
    auto face = t.locate(p);
    K::FT new_radius = 4*clearance;
    if(face->info() >= new_radius){
      std::cout << "y";
    }else{
      std::cout << "n";
    }
  }
  std::cout << std::endl;
}

int main(){
  std::ios::sync_with_stdio(false);
  int t;std::cin >> t;
  while(t--) testcase();
}