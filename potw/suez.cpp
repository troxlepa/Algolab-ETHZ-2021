#include <bits/stdc++.h>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef int LL;

void testcase(){
  int n,m,h,w;
  std::cin >> n >> m >> h >> w;
  
  std::vector<std::pair<LL,LL>> f(n);
  std::vector<std::pair<LL,LL>> o(m);
  
  LL x,y;
  for(int i=0;i<n;++i){
    std::cin >> x >> y;
    f[i] = {x,y};
  }

  for(int i=0;i<m;++i){
    std::cin >> x >> y;
    o[i] = {x,y};
  }
  
  Program lp (CGAL::SMALLER, true, 1, false, 0);
  int NQ = 0;
  for(int i=0;i<n;++i){
    for(int j=i+1;j<n;++j){
      ET diff1 = std::abs(f[i].first - f[j].first);
      ET diff2 = std::abs(f[i].second - f[j].second);
      lp.set_a(i,NQ,1); lp.set_a(j,NQ,1); lp.set_b(NQ,std::max(2*(diff1/w), 2*(diff2/h)));
      NQ++;
    }
    ET best = -1;
    for(int j=0;j<m;++j){
      ET diffX = std::abs(o[j].first-f[i].first);
      ET diffY = std::abs(o[j].second-f[i].second);
      
      ET mm = std::max(2*(diffX/w)-1, 2*(diffY/h)-1);
      if(best == -1 || mm < best) best = mm;
    }
    if(m>0){
      lp.set_a(i,NQ,1); lp.set_b(NQ,best);
      NQ++;
    }
    
    lp.set_c(i, -2 * (h + w));
  }
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  long res = std::ceil(CGAL::to_double(-s.objective_value()));
  std::cout << res << std::endl;
}

int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}