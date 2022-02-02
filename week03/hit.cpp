#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef long int LL;

void testcase(int n){
  LL x,y,a,b; std::cin >> x >> y >> a >> b;
  
  K::Point_2 start(x,y), end(a,b);
  K::Ray_2 seg(start, end);
  bool flag = true;
  for(int i=0;i< n;++i){
    LL r,s,t,u; std::cin >> r >> s >> t >> u;
    K::Point_2 p(r,s), q(t,u);
    K::Segment_2 l(p,q);
    if(flag && CGAL::do_intersect(seg,l)){
      flag = false;
    }
  }
  if(!flag){
    std::cout << "yes" << std::endl;
  }else{
    std::cout << "no" << std::endl;    
  }
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int n;
  while(std::cin >> n){
    if(n==0){
      break;
    }
    testcase(n);
  }
}
