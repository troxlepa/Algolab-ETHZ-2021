///2
#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/nearest_neighbor_delaunay_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> DT;
typedef DT::Finite_edges_iterator Edge_iterator;
typedef K::Point_2 Point_2;

struct Person{
  K::Point_2 pos;
  long r;
  int idx;
};

std::vector<Person> check_winner(std::vector<Point_2>& lamps, std::vector<Person>& people,
      int u, int v){

  std::vector<Person> remaining;
  DT t;
  t.insert(lamps.begin()+u,lamps.begin()+v+1);
  
  for(auto p : people){
    auto nearest = t.nearest_vertex(p.pos)->point();
    K::FT dist = CGAL::squared_distance(nearest, p.pos);
    if(dist >= p.r) remaining.push_back(p);
  }
  return remaining;
}

void testcase(){
  int m,n;
  std::cin >> m >> n;
  std::vector<Person> people(m);
  for(int i=0;i<m;++i){
    long x,y,r;
    std::cin >> x >> y >> r;
    people[i] = Person{.pos = K::Point_2(x,y), .r = r, .idx = i};
  }
  int h; std::cin >> h;
  
  std::vector<Point_2> lamps(n);
  for(int i=0;i<n;++i){
    long x,y; std::cin >> x >> y;
    lamps[i] = Point_2(x,y);
  }
  for(int i=0;i<m;++i){
    people[i].r = K::FT(people[i].r + h)*K::FT(people[i].r + h);
  }

  int left = 0;
  int right = n-1;
  while(left < right){
    int mid = (left+right) / 2;
    auto remaining = check_winner(lamps,people,left,mid);
    bool pred = remaining.size() > 0;
    if(pred){
      people = remaining;
      left = mid+1;
    }else{
      right = mid;
    }
  }
  auto remaining = check_winner(lamps,people,left,right);
  if(remaining.size() > 0){
    for(auto p : remaining){
      std::cout << p.idx << " ";
    }
  }else{
    for(auto p : people){
      std::cout << p.idx << " ";
    }
  }

  std::cout << std::endl;
}

int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}