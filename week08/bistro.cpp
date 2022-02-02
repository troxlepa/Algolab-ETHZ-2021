#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include <CGAL/squared_distance_2.h> //for 2D functions

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> DT;
typedef K::Point_2 Point_2;

int main(){
  std::ios::sync_with_stdio(false);
  int n;
  
  while(true){
    std::cin >> n;
    if(n == 0) break;
    
    std::vector<Point_2> ps;
    int x,y;
    for(int i=0;i<n;++i){
      std::cin >> x >> y;
      ps.push_back(Point_2(x,y));
    }
      
    DT dt;
    dt.insert(ps.begin(), ps.end());
    
    int m; std::cin >> m;
    for(int j=0;j<m;++j){
      std::cin >> x >> y;
      Point_2 p(x,y);
      auto nearest = dt.nearest_vertex(K::Point_2(x, y));
      
      std::cout << (long)CGAL::squared_distance(nearest->point(),p) << std::endl;

    }
  }
}