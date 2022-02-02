#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef long IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef long LL;

void testcase(){
  int n,m;
  LL s;
  std::cin >> n >> m >> s;
  std::vector<int> nobles_x(n);
  std::vector<int> nobles_y(n);
  std::vector<int> comms_x(m);
  std::vector<int> comms_y(m);
  LL an_x = 0;
  LL an_y = 0;
  LL ac_x = 0;
  LL ac_y = 0;

  const int A = 0;
  const int C = 1;
  const int D = 2;
  const int Q = 3;
  
  int idx = 0;
  Program lp (CGAL::SMALLER, false, 0, false, 0);
    
  for(int i=0;i<n;++i){
    std::cin >> nobles_x[i] >> nobles_y[i];
    an_x += nobles_x[i];
    an_y += nobles_y[i];
    
    lp.set_a(A,idx,nobles_y[i]);
    lp.set_a(C,idx,1);
    lp.set_b(idx,-nobles_x[i]);
    idx++;
  }
  
  for(int i=0;i<m;++i){
    std::cin >> comms_x[i] >> comms_y[i];
    ac_x += comms_x[i];
    ac_y += comms_y[i];
    
    lp.set_a(A,idx,-comms_y[i]);
    lp.set_a(C,idx,-1);
    lp.set_b(idx,comms_x[i]);
    idx++;
  }
  
  Solution sol = CGAL::solve_linear_program(lp, ET());
  
  if(sol.is_infeasible()){
    std::cout << "Yuck!" << std::endl;
    return;
  }
  
  // \sum pipes <= s
  if(s != -1){
    lp.set_a(A,idx,ac_y - an_y);
    lp.set_a(C,idx,m-n);
    lp.set_b(idx,s - (ac_x - an_x));
    idx++;
    
    Solution sol2 = CGAL::solve_linear_program(lp, ET());
    if(sol2.is_infeasible()){
      std::cout << "Bankrupt!" << std::endl;
      return;
    }
  }
  

  // minimize longest water pipe
  // for every point: minimize distance to water line

  for(int i=0;i<n;++i){
    int x = nobles_x[i];
    int y = nobles_y[i];

    lp.set_a(A,idx,x);
    lp.set_a(D,idx,1);
    lp.set_a(Q,idx,-1);
    lp.set_b(idx,y); 
    idx++;
    
    lp.set_a(A,idx,-x);
    lp.set_a(D,idx,-1);
    lp.set_a(Q,idx,-1);
    lp.set_b(idx,-y);
    idx++;
  }
  for(int i=0;i<m;++i){
    int x = comms_x[i];
    int y = comms_y[i];

    lp.set_a(A,idx,x);
    lp.set_a(D,idx,1);
    lp.set_a(Q,idx,-1);
    lp.set_b(idx,y); 
    idx++;
    
    lp.set_a(A,idx,-x);
    lp.set_a(D,idx,-1);
    lp.set_a(Q,idx,-1);
    lp.set_b(idx,-y); 
    idx++;
  }
  
  lp.set_l(Q,true,0);
  lp.set_c(Q,1);
  sol = CGAL::solve_linear_program(lp, ET());
  

  CGAL::Quotient<ET> res = sol.objective_value();
  std::cout << (long)ceil(CGAL::to_double(res)) << std::endl;
}

int main(){
  std::ios::sync_with_stdio(false);
  int t;std::cin >> t;
  while(t--) testcase();
}