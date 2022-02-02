#include<bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;



void testcase(){
  long x0,y0,n; std::cin >> x0 >> y0 >> n;
  const int PX = 0;
  const int PY = 1;
  const int E = 2;
  
  // create an LP with Ax <= b, lower bound 0 and no upper bounds
  Program lp (CGAL::SMALLER, false, 0, false, 0);
  
  for(int i=0;i<n;++i){
    long a,b,c,v; std::cin >> a >> b >> c >> v;
    if (a * x0 + b * y0 + c > 0) {
        a = -a;
        b = -b;
    } else {
        c = -c;
    }
    long fdiv = (long)std::sqrt(a*a+b*b) * v;
    lp.set_a(PX, i, a); lp.set_a(PY, i, b); lp.set_a(E, i, fdiv); lp.set_b(i, c); // ax + by - e <= -c
  }

  lp.set_l(E, 0);
  lp.set_c(E, -1);
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  assert (s.solves_linear_program(lp));
  std::cout << (-s.objective_value_numerator()/s.objective_value_denominator()).to_double() << std::endl;
}


int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}