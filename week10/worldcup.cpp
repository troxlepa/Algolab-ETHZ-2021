#include<bits/stdc++.h>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

struct WA{
    K::Point_2 p;
    int s;
    int a;
};

struct ST{
    K::Point_2 p;
    int d;
    int u;
};

void testcase(){
    int n,m,c; std::cin >> n >> m >> c;
    std::vector<WA> warehouses(n);
    std::vector<K::Point_2> wp(n);
    for(int i=0;i<n;++i){
        int x,y,s,a; std::cin >> x >> y >> s >> a;
        warehouses[i] = WA{.p = K::Point_2(x,y),.s=s,.a=a};
        wp[i] = K::Point_2(x,y);
    }
    
    std::vector<ST> stadiums(m);
    std::vector<K::Point_2> sp(m);
    for(int i=0;i<m;++i){
        int x,y,d,u; std::cin >> x >> y >> d >> u;
        stadiums[i] = ST{.p = K::Point_2(x,y),.d=d,.u=u};
        sp[i] = K::Point_2(x,y);
    }

    std::vector<std::vector<int>> revenue(n, std::vector<int>(m));
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            std::cin >> revenue[i][j];
            revenue[i][j] *= 100;
        }
    }

    std::vector<K::Point_2> contoures;
    std::vector<K::FT> radii;

    if(c != 0){
      Triangulation dt;
      dt.insert(wp.begin(),wp.end());
      dt.insert(sp.begin(),sp.end());
      
      for(long i=0;i<c;++i){
        int x,y; std::cin >> x >> y;
        K::FT r; std::cin >> r;
        K::Point_2 p(x,y);
        auto nearest = dt.nearest_vertex(p);
        if(CGAL::squared_distance(nearest->point(),p) < r*r){
          contoures.push_back(p);
          radii.push_back(r*r);
        }
      }
      
      std::vector<std::vector<int>> crosses(n,std::vector<int>(m,0));
      for(int k=0;k<contoures.size();++k){
        K::Point_2 p = contoures[k];
        K::FT r2 = radii[k];
        for(int i=0;i<m;++i){
          bool si = CGAL::squared_distance(p, stadiums[i].p) < r2;
          for(int j=0;j<n;++j){
            bool wi = CGAL::squared_distance(p, warehouses[j].p) < r2;
            if(wi != si) crosses[j][i]++;
          }
        }
      }
      
      for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
          revenue[j][i] -= crosses[j][i];
        }
      }

    }
    auto q = [n,m](int i, int j){
        if(i * n + j > n*m) std::cout << "index fail";
        return i * n + j;
    };

    Program lp (CGAL::SMALLER, true, 0, false, 0); 
    int NEQ = 0;
    
    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            lp.set_a(q(i,j), NEQ, 1);
        }
        lp.set_b(NEQ,stadiums[i].d);
        NEQ++;
    }
    
    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            lp.set_a(q(i,j), NEQ, -1);
        }
        lp.set_b(NEQ,-stadiums[i].d);
        NEQ++;
    }
    
    for(int j=0;j<n;++j){
        for(int i=0;i<m;++i){
            lp.set_a(q(i,j), NEQ, 1);
        }
        lp.set_b(NEQ, warehouses[j].s);
        NEQ++;
    }

    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            lp.set_a(q(i,j), NEQ, warehouses[j].a);
        }
        lp.set_b(NEQ,stadiums[i].u*100);
        NEQ++;
    }
    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            lp.set_c(q(i,j),-revenue[j][i]);
        }
    }

    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_infeasible()){
        std::cout << "RIOT!" << std::endl;
        return;
    }


    auto ov = CGAL::to_double(s.objective_value()/100);
    auto res = -(long)std::ceil(ov);
    
    std::cout << res<< std::endl; 
    

}

int main(){
    std::ios::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}
