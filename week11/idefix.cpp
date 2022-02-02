#include<bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef int Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef K::Point_2 Point;
typedef std::pair<K::Point_2, Index> IPoint;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS    // Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
    >          graph;
typedef boost::graph_traits<graph>::vertex_descriptor    vertex_desc;    // Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).  
typedef boost::graph_traits<graph>::edge_iterator    edge_it;    // to iterate over all edges

using universal_edge = std::tuple<Index, Index, K::FT, bool>;

void testcase(){
  int n, m,k;
  K::FT s;
  std::cin >> n >> m >> s >> k;
  std::vector<IPoint> trees;
  for(int i=0;i<n;++i){
    int x,y;
    std::cin >> x >> y;
    trees.emplace_back(K::Point_2(x,y),i);
  }
  
  std::vector<universal_edge> edges;
  
  Triangulation t;
  t.insert(trees.begin(),trees.end());
  
  std::vector<int> num_bones(n,0);
  boost::disjoint_sets_with_storage<> uf(n);
 
  std::vector<K::Point_2> bones(m);
  for(int i=0;i<m;++i){
    int x,y;
    std::cin >> x >> y;
    bones[i] = K::Point_2(x,y);
    
    // for each bone, mark closest tree as +1
    auto nearest = t.nearest_vertex(bones[i]);
    auto dist = 4*CGAL::squared_distance(bones[i],nearest->point());
    edges.emplace_back(nearest->info(),nearest->info(),dist,true);
    if(dist <= s){
      Index v = nearest->info();
      num_bones[v]++;
    }
  }
  
  graph G(n);
  // construct boost tree from trees
  for(auto e = t.finite_edges_begin(); e != t.finite_edges_end();++e){
    
    Index i1 = e->first->vertex((e->second+1)%3)->info();
    Index i2 = e->first->vertex((e->second+2)%3)->info();
    
    if(i1>i2) std::swap(i1,i2);
    double dist = t.segment(e).squared_length();
    
    edges.emplace_back(i1,i2,dist,false);
    if(dist <= s){
      Index c1 = uf.find_set(i1);
      Index c2 = uf.find_set(i2);
      
      if(c1 != c2){
        uf.link(c1,c2);
        num_bones[uf.find_set(i1)] = num_bones[c1] + num_bones[c2];
      }
    }
  }
  
  int max_reach = 0;
  for(int i=0;i<num_bones.size();++i){
    max_reach = std::max(max_reach,num_bones[i]);
  }
  double min_radius = 0;
  
  auto cmp = [](universal_edge& a, universal_edge& b){
    return std::get<2>(a) < std::get<2>(b);
  };
  
  std::sort(edges.begin(),edges.end(),cmp);
  
  uf = boost::disjoint_sets_with_storage<>(n);
  std::fill(num_bones.begin(),num_bones.end(),0);
  
  for(universal_edge& e : edges){
    Index i1 = std::get<0>(e);
    Index i2 = std::get<1>(e);
    double dist = std::get<2>(e);
    bool is_bone = std::get<3>(e);
    
    if(is_bone){
      Index c1 = uf.find_set(i1);
      num_bones[c1]++;
      if(num_bones[c1] >= k){
        min_radius = dist;
        break;
      }
    }else{
      Index c1 = uf.find_set(i1);
      Index c2 = uf.find_set(i2);
      
      if(c1 != c2){
        uf.link(c1,c2);
        Index cnew = uf.find_set(i1);
        num_bones[cnew] = num_bones[c1] + num_bones[c2];
        if(num_bones[cnew] >= k){
          min_radius = dist;
          break;
        }
      }
    }
  }
  std::cout << max_reach << " " << (long)min_radius << std::endl;
}


int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}