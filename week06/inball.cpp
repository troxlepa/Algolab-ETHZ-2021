#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void testcase(int n){
  int d;
  std::cin >> d;
  std::vector<std::vector<int>> lines(n,std::vector<int>(d));
  std::vector<int> b(n);
  std::vector<int> anorm(n,0);
  
  Program lp (CGAL::SMALLER, false, 0, false, 0);
  
  for(int i=0;i<n;++i){
    for(int j=0;j<d;++j){
      std::cin >> lines[i][j];
      anorm[i] += lines[i][j] * lines[i][j];
    }
    std::cin >> b[i];
    anorm[i] = (int)std::sqrt((double)anorm[i]);
  }
  for(int i=0;i<n;++i){
    for(int j=0;j<d;++j){
      lp.set_a(j,i,lines[i][j]);
    }
    lp.set_a(d,i,anorm[i]);
    lp.set_b(i,b[i]);
  }
  lp.set_c(d,-1);
  for(int j=0;j<d+1;++j){
    lp.set_l(j,0);
  }
  
  Solution s1 = CGAL::solve_linear_program(lp, ET());
  
  if(s1.is_infeasible()){
    std::cout << "none" << std::endl;
  }else if(s1.is_unbounded()){
    std::cout << "inf" << std::endl;
  }
  else{
    CGAL::Quotient<ET> res = s1.objective_value();
    res *= -1;
    if(res < 1){
      std::cout << "none" << std::endl;
      return;
    }
    long finalres = (long)ceil((res.numerator()/res.denominator()).to_double());
    if(finalres <= 0){
      std::cout << "none" << std::endl;
    }else{
      std::cout << finalres << std::endl;
    }
  }
}


int main(){
  std::ios::sync_with_stdio(false);
  int n;
  while(true){
    std::cin >> n;
    if(n==0) break;
    testcase(n);
  }
}