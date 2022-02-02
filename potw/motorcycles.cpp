#include <bits/stdc++.h>
#include <CGAL/Gmpq.h>

typedef long int ll;

struct RX{
  ll y0;
  ll x1;
  ll y1;
  int i;
};

CGAL::Gmpq gsl(RX ray){
  return CGAL::Gmpq(ray.y1-ray.y0, ray.x1);
}

void testcase(){
  int n; std::cin >> n;
  std::vector<RX> rays(n);
  ll y0,x1,y1;
  for(int i=0;i<n;++i){
    std::cin >> y0 >> x1 >> y1;
    RX q; q.y0 = y0; q.x1 = x1; q.y1 = y1; q.i = i;
    rays[i] = q;
  }
  
  auto comp = [](RX& a, RX& b){return a.y0 < b.y0;};
  
  std::sort(rays.begin(),rays.end(),comp);
  
  std::vector<bool> poss(n,true);
  std::vector<CGAL::Gmpq> slopes;
  for(int i=0;i<n;++i){
    slopes.push_back(gsl(rays[i]));
  }
  CGAL::Gmpq best = slopes.front();
  for(int i=1;i<n;++i){
    if(CGAL::abs(slopes[i]) < CGAL::abs(best) || (CGAL::abs(slopes[i]) == CGAL::abs(best) && slopes[i] > best)){
      best = slopes[i];
    }else if(slopes[i] < best){
      poss[i] = false;
    }
  }
  
  best = slopes.back();
  for(int i = n-2; i >= 0; --i){
    if(CGAL::abs(slopes[i]) <= CGAL::abs(best)){
      best = slopes[i];
    }else if(slopes[i] > best){
      poss[i] = false;
    }
  }
  
  std::vector<int> res;
  for(int i=0;i<n;++i){
    if(poss[i]) res.push_back(rays[i].i);
  }
  std::sort(res.begin(),res.end());
  for(int r : res) std::cout << r << " ";
  
  std::cout << std::endl;
}

int main(){
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
  int t; std::cin >> t;
  while(t--) testcase();
}