#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::FT LL;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

void testcase(int n){
  long int x,y,a,b;
  std::cin >> x >> y >> a >> b;
  
  P start(x,y), end(a,b);
  R ray(start, end);
  S to_last(start,end);
  P its;
  
  bool lp_set = false;
  std::vector<S> SEGS;
  for(int i=0;i<n;++i){
    long int r,s,t,u;
    std::cin >> r >> s >> t >> u;
    S l(P(r,s),P(t,u));
    SEGS.push_back(l);
  }
  std::random_shuffle(SEGS.begin(),SEGS.end());
  
  for(int i=0;i<n;++i){
    S l = SEGS[i];
    if(!lp_set){
      if(CGAL::do_intersect(ray,l)){
        auto o = CGAL::intersection(ray,l);
        lp_set = true;
        if(const P* op = boost::get<P>(&*o)){
          its = *op;
        }else if(const S* os = boost::get<S>(&*o)){
          if(CGAL::compare_distance_to_point (start,os->source(),os->target()) == CGAL::SMALLER){
            its = os->source();
          }else{
            its = os->target();
          }
        }
        to_last = S(start,its);
      }
    }else{
      if(CGAL::do_intersect(to_last,l)){
        auto o = CGAL::intersection(to_last,l);
        if(const P* op = boost::get<P>(&*o)){
          its = *op;
        }else if(const S* os = boost::get<S>(&*o)){
          if(CGAL::compare_distance_to_point(start,os->source(),os->target()) == CGAL::SMALLER){
            its = os->source();
          }else{
            its = os->target();
          }
        }
        to_last = S(start,its);
      }
    }
  }
  if(lp_set){
    K::FT pres1 = to_last.target().x();
    double res1 = std::floor(CGAL::to_double(pres1));
    while(res1 > pres1) res1--;
    while(res1+1 <= pres1) res1++;
    
    K::FT pres2 = to_last.target().y();
    double res2 = std::floor(CGAL::to_double(pres2));
    while(res2 > pres2) res2--;
    while(res2+1 <= pres2) res2++;
    
    std::cout << std::fixed << std::setprecision(0) << res1 << " " << res2 << std::endl;
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
