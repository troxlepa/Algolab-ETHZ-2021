#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/nearest_neighbor_delaunay_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> DT;
typedef DT::Finite_edges_iterator Edge_iterator;
typedef K::Point_2 Point_2;

int main(){
  std::ios::sync_with_stdio(false);
  int n;
  while(std::cin >> n && n > 0){
    int l,b,r,t;
    std::cin >> l >> b >> r >> t;
    std::vector<Point_2> ps(n);
    int x,y;
    for(int i=0;i<n;++i){
      std::cin >> x >> y;
      ps[i] = Point_2(x,y);
    }
    
    DT dt;
    dt.insert(ps.begin(), ps.end());
    
    std::vector<long> lens;
    
    for(auto v = dt.vertices_begin(); v != dt.vertices_end(); ++v){
      auto closest = CGAL::nearest_neighbor(dt,v->handle());
      double length = LONG_MAX;
      double sq = (v->point().x() - closest->point().x()) * (v->point().x() - closest->point().x())
                  + (v->point().y() - closest->point().y()) * (v->point().y() - closest->point().y());
      length = std::sqrt(sq) / 2.0;
      
      long xmin = std::min(v->point().x() - l,r - v->point().x());
      long ymin = std::min(t - v->point().y(),v->point().y() - b);
      long xymin = std::min(xmin,ymin);

      double tmin = std::min((double)xymin,length);
      
      if(tmin > 0.5){
        lens.push_back(std::ceil(std::sqrt(tmin-0.5)));
      }else{
        lens.push_back(0);
      }
      
    }
    
    std::sort(lens.begin(),lens.end());
    std::cout << lens[0] << " " << lens[lens.size()/2] << " " << lens[lens.size()-1] << std::endl;
  }
}