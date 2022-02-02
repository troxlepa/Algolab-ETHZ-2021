#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

#include <CGAL/squared_distance_2.h> //for 2D functions
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                   DT;
typedef K::Point_2 Point_2;

typedef std::tuple<int,int,double,bool> universal_edge;

void testcase(){
  int n,m;
  long p;
  std::cin >> n >> m >> p;
  boost::disjoint_sets_with_storage<> uf(n);
  std::vector<universal_edge> edges;
  
  std::vector<std::pair<Point_2,int>> jammers;
  for(int i=0;i<n;++i){
    int x,y; std::cin >> x >> y;
    jammers.push_back({Point_2(x,y),i});
  }

  DT dt;
  dt.insert(jammers.begin(),jammers.end());
  for (auto e = dt.finite_edges_begin(); e != dt.finite_edges_end(); ++e) {
      int i1 = e->first->vertex((e->second+1)%3)->info();
      int i2 = e->first->vertex((e->second+2)%3)->info();
      
      double dist = dt.segment(e).squared_length();
      edges.emplace_back(i1,i2,dist,false);
    
    if(dist <= p){
      // ensure smaller int comes first
      if (i1 > i2) std::swap(i1, i2);
      int c1 = uf.find_set(i1);
      int c2 = uf.find_set(i2);
      if(c1 != c2){
        uf.link(c1,c2);
      }
    }
  }
  auto cmp = [](universal_edge& a, universal_edge& b){
    return std::get<2>(a) < std::get<2>(b);
  };
  std::sort(edges.begin(),edges.end(),cmp);
  
  double max_radius = 0;
  double min_radius = 0;
  boost::disjoint_sets_with_storage<> low(n);
  boost::disjoint_sets_with_storage<> high(n);
  
  std::string out = "";
  
  for(int i=0;i<m;++i){
    int x0,y0,x1,y1;
    std::cin >> x0 >> y0 >> x1 >> y1;
    Point_2 fst = Point_2(x0,y0);
    Point_2 snd = Point_2(x1,y1);
    
    auto nearest1 = dt.nearest_vertex(fst);
    auto nearest2 = dt.nearest_vertex(snd);
    double dist1 = CGAL::squared_distance(nearest1->point(),fst);
    double dist2 = CGAL::squared_distance(nearest2->point(),snd);
    max_radius = std::max(max_radius, 4*dist1);
    max_radius = std::max(max_radius, 4*dist2);
    
    bool hasX = 4*dist1 <= p;
    bool hasY = 4*dist2 <= p;
    int c1 = uf.find_set(nearest1->info());
    int c2 = uf.find_set(nearest2->info());
    bool sameSet = c1 == c2;
    if(hasX && hasY && sameSet){
      out += "y";

      min_radius = std::max(min_radius, 4*dist1);
      min_radius = std::max(min_radius, 4*dist2);
      double dist = 0;
      for(auto& edge : edges){
        int q1 = high.find_set(nearest1->info());
        int q2 = high.find_set(nearest2->info());
        if(q1 == q2){
          min_radius = std::max(min_radius, dist);
          break;
        }
        int i1 = std::get<0>(edge);
        int i2 = std::get<1>(edge);
        dist = std::get<2>(edge);
        
        int k1 = high.find_set(i1);
        int k2 = high.find_set(i2);
        if(k1 != k2){
          high.link(k1,k2);
        }
      }
      
    }else{
      out += "n";

      double dist = 0;
      for(auto& edge : edges){
        int q1 = low.find_set(nearest1->info());
        int q2 = low.find_set(nearest2->info());
        if(q1 == q2){
          max_radius = std::max(max_radius, dist);
          break;
        }
        int i1 = std::get<0>(edge);
        int i2 = std::get<1>(edge);
        dist = std::get<2>(edge);
        
        int k1 = low.find_set(i1);
        int k2 = low.find_set(i2);
        if(k1 != k2){
          low.link(k1,k2);
        }
      }
    }
  }
  std::cout << out << std::endl;
  
  
  // a
  std::cout << (long)max_radius << std::endl;
  
  // b
  std::cout << (long)min_radius << std::endl;
}

int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}