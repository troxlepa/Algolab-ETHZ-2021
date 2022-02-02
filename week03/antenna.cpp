#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>


typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt SK;
typedef CGAL::Min_circle_2_traits_2<SK> Traits;
typedef CGAL::Min_circle_2<Traits> MC;


int main(){
  std::ios_base::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(0);
  
  int n;std::cin >> n;
  std::vector<SK::Point_2> xy;
  
  while(n != 0){
    xy.clear();
    for(int i=0;i<n;++i){
      long x,y;
      std::cin >> x >> y;
      xy.push_back(SK::Point_2(x,y));
    }
    MC mc(xy.begin(),xy.end(), true);
    SK::FT pres = CGAL::sqrt((mc.circle()).squared_radius());
    double res = std::ceil(CGAL::to_double(pres));
    while(res-1 > pres) res--;
    while(res < pres) res++;
    std::cout << res << std::endl;
    std::cin >> n;
  }
}