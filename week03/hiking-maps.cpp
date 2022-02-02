#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Triangle_2 T;
typedef K::Segment_2 S;
typedef K::Line_2 L;

void testcase(){
  int n,m;
  std::cin >> m >> n;
  std::vector<P> p(m);
  double x,y;
  for(int i=0;i<m;++i){
    std::cin >> x >> y;
    p[i] = P(x,y);
  }
  
  std::vector<std::vector<bool>> cs(n, std::vector<bool>(m-1,false));
  double q0,p0,q1,p1,q2,p2,q3,p3,q4,p4,q5,p5;
  L l0,l1,l2;
  P t1,t2,t3;
  T ti;
  for(int i=0;i<n;++i){
    
    std::cin >> q0 >> p0 >> q1 >> p1 >> q2 >> p2 >> q3 >> p3 >> q4 >> p4 >> q5 >> p5;

    l0 = L(P(q0,p0),P(q1,p1));
    l1 = L(P(q2,p2),P(q3,p3));
    l2 = L(P(q4,p4),P(q5,p5));
    auto o = CGAL::intersection(l0,l1);
    t1 = *(boost::get<P>(&*o));
    o = CGAL::intersection(l1,l2);
    t2 = *(boost::get<P>(&*o));
    o = CGAL::intersection(l0,l2);
    t3 = *(boost::get<P>(&*o));

    ti = T(t1,t2,t3);
    bool last_passed = false;
    
    for(int s=1;s<m-1;s+=2){
      if(CGAL::do_intersect(ti,p[s])){
        if(last_passed || CGAL::do_intersect(ti,p[s-1])){
          cs[i][s-1] = true;
        }
        if(CGAL::do_intersect(ti,p[s+1])){
          cs[i][s] = true;
          last_passed = true;
        }else{
          last_passed = false;
        }
      }else{
        last_passed = false;
      }
    }
    if(CGAL::do_intersect(ti,p[m-2]) && CGAL::do_intersect(ti,p[m-1])){
      cs[i][m-2] = true;
    }
  }

  std::vector<int> segcov(m-1,0);
  int best = std::numeric_limits<int>::max();
  int l = 0;
  int r = 0;
  int non_zero_count = m-1;
  while(non_zero_count > 0 && r < n){
    for(int i=0;i<m-1;++i){
      if(cs[r][i]){
        if(segcov[i] == 0) non_zero_count--;
        segcov[i]++;
      }
    } 
    ++r;
  }

  
  while(r <= n){
    if(non_zero_count > 0){
      if(r == n){
        break;
      }
      for(int i=0;i<m-1;++i){
        if(cs[r][i]){
          if(segcov[i] == 0) non_zero_count--;
          segcov[i]++;
        }
      }
      r++;
    }else{
      if(r-l < best){
        best = r-l;
      }
      if(best == 1) break;
      for(int i=0;i<m-1;++i){
        if(cs[l][i]){
          segcov[i]--;
          if(segcov[i] == 0) non_zero_count++;
        }
      }
      l++;
    }
  }
  std::cout << best << std::endl;
}

int main(){
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
  int t;std::cin >> t;
  for(int i=0;i<t;++i){
    testcase();
  }
}