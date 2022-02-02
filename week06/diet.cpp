#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void testcase(int n, int m){
  std::vector<int> nmin(n);
  std::vector<int> nmax(n);
  std::vector<int> p(m);
  std::vector<std::vector<int>> c(m,std::vector<int>(n));
  
  Program lp (CGAL::SMALLER, true, 0, false, 0);
  for(int i=0;i<n;++i){
    std::cin >> nmin[i];
    std::cin >> nmax[i];
  }
  for(int i=0;i<m;++i){
    std::cin >> p[i];
    lp.set_c(i,p[i]); // top row
    
    for(int j=0;j<n;++j){
      std::cin >> c[i][j];
      lp.set_a(i,j,c[i][j]);
      lp.set_a(i,n+j,-c[i][j]);
    }
  }

  for(int i=0;i<n;++i){
    lp.set_b(i,nmax[i]);
    lp.set_b(n+i,-nmin[i]);
  }
  
  Solution s1 = CGAL::solve_linear_program(lp, ET());
  
  if(s1.is_infeasible()){
    std::cout << "No such diet." << std::endl;
  }else if(s1.is_unbounded()){
    std::cout << "Unbound" << std::endl;
  }
  else{
    CGAL::Quotient<ET> res = s1.objective_value();
    std::cout << (long)ceil((res.numerator()/res.denominator()).to_double()) << std::endl;
  }
}

int main(){
  std::ios::sync_with_stdio(false);
  int n,m;
  while(true){
    std::cin >> n >> m;
    if(n == 0 && m == 0){
      return 0;
    }else{
      testcase(n,m);
    }
  }
}