#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int main(){
  std::ios::sync_with_stdio(false);
  int p;
  
  const int X = 0;
  const int Y = 1;
  const int Z = 2;
  
  Program lp (CGAL::SMALLER, true, 0, false, 0);

  lp.set_a(X,0,1); lp.set_a(Y,0,1); lp.set_b(0,4);
  lp.set_a(X,1,4); lp.set_a(Y,1,2); 
  lp.set_a(X,2,-1); lp.set_a(Y,2,1); lp.set_b(2,1);
  
  
  Program lp2 (CGAL::LARGER, false, 0, true, 0);
  
  lp2.set_a(X,0,1); lp2.set_a(Y,0,1); lp2.set_a(Z,0,0); lp2.set_b(0,-4);
  lp2.set_a(X,1,4); lp2.set_a(Y,1,2); lp2.set_a(Z,1,1); 
  lp2.set_a(X,2,-1); lp2.set_a(Y,2,1); lp2.set_a(Z,2,0); lp2.set_b(2,-1);
  
  while(true){
    std::cin >> p;
    if(p == 0) break;
    int a,b; std::cin >> a >> b;
    if(p == 1){

      lp.set_b(1,a*b);
      
      lp.set_c(X, a);
      lp.set_c(Y, -b);
      lp.set_c0(0);
      
      Solution s1 = CGAL::solve_linear_program(lp, ET());
      
      if(s1.is_infeasible()){
        std::cout << "no" << std::endl;
      }else if(s1.is_unbounded()){
        std::cout << "unbounded" << std::endl;
      }else{
        CGAL::Quotient<ET> res = s1.objective_value();
        res *= -1;
        std::cout << (long)ceil((res.numerator()/res.denominator()).to_double()) << std::endl;
      }
      
    }
    if(p == 2){
      lp2.set_b(1,-a*b);
      lp2.set_c(X,a);
      lp2.set_c(Y,b);
      lp2.set_c(Z,1);
      lp2.set_c0(0);
      Solution s2 = CGAL::solve_linear_program(lp2, ET());
      
      if(s2.is_infeasible()){
        std::cout << "no" << std::endl;
      }else if(s2.is_unbounded()){
        std::cout << "unbounded" << std::endl;
      }else{
        CGAL::Quotient<ET> res = s2.objective_value();
        std::cout << (long)ceil((res.numerator()/res.denominator()).to_double()) << std::endl;
      }
    }
  }
}
