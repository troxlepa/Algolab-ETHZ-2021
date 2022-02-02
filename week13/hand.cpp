#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<long, K>    Vb;
typedef CGAL::Triangulation_data_structure_2<Vb>                    Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>                      Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;

struct Edge{
  long u; long v; long d;
};

long maxComp(std::vector<long> &c, int k){
  if(k == 4){
    if(c[1] >= c[3]) return c[4] + c[3] + ((c[1]-c[3]) / 2 + c[2]) / 2;
    else return c[4] + c[1] + ((c[3]-c[1]) + c[2]) / 2;
  }else if(k == 3){
    if(c[1] >= c[2]) return c[3] + c[2] + (c[1]-c[2]) / 3;
    else return c[3] + c[1] + (c[2]-c[1]) / 2;
  }else if(k == 2){
    return c[2] + c[1] / 2;
  }
  return c[k];
}

void testcase()
{
  // read number of points
  long n, k,f0;
  long s0;
  std::cin >> n >> k >> f0 >> s0;
  // read points
  std::vector<std::pair<K::Point_2,long>> pts(n);
  for (int i = 0; i < n; ++i) {
    long x, y; std::cin >> x >> y;
    pts[i] = {K::Point_2(x, y),i};
  }

  Triangulation t;
  t.insert(pts.begin(), pts.end());
  
  std::vector<Edge> edges;
  for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e){
    Triangulation::Vertex_handle v1 = e->first->vertex((e->second + 1) % 3);
    Triangulation::Vertex_handle v2 = e->first->vertex((e->second + 2) % 3);
    long sd = long(t.segment(e).squared_length());
    if(v1 > v2) std::swap(v1,v2);
    edges.push_back(Edge{.u = v1->info(), .v = v2->info(), .d = sd});
  }
  
  auto cmp = [](auto a, auto b){return a.d < b.d;};
  std::sort(edges.begin(),edges.end(),cmp);
  
  boost::disjoint_sets_with_storage<> uf(n);
  std::vector<long> components(k+1,0);
  std::vector<long> compsize(n,1);
  int n_components = n;
  long num_components = -1;
  long f = -1;
  components[1] = n;
  long s = -1;
  for(int i=0;i<edges.size();++i){
    long v1 = edges[i].u;
    long v2 = edges[i].v;
    int c1 = uf.find_set(v1);
    int c2 = uf.find_set(v2);
    if(c1 != c2){
      
      num_components = maxComp(components,k);
      
      if(num_components >= f0){
        s = edges[i].d;
      }
      
      if(edges[i].d >= s0){
        f = std::max(f, num_components);
      }
      
      uf.link(c1,c2);
      
      int c0 = uf.find_set(v1);
      components[compsize[c1]]--;
      components[compsize[c2]]--;
      compsize[c0] = std::min(k,compsize[c1] + compsize[c2]);
      components[compsize[c0]]++;
      
      if(n_components == 1) break;
      n_components--;
    }
  }
  f = std::max(f, maxComp(components,k));

  std::cout << (long)s << " " << f << std::endl;
}

int main(){
  std::ios::sync_with_stdio(false);
  int t;std::cin >> t;
  while(t--) testcase();
}