#include <bits/stdc++.h>

void testcase(){
  int n;std::cin >> n;
  std::vector<int> p(n);
  for(int i=0;i<n;++i){
    int x; std::cin >> x;
    p[i] = x;
  }
  std::sort(p.begin(),p.end());
  p.push_back(p[n-1]);
  std::vector<int> num(201);
  int maxval = 0;
  int maxlen = INT_MAX;
  std::vector<int> maxlocs;
  int hi = 0;
  int lo = 0;
  for(int i=p[0];i<=p[n-1];++i){
    while(p[hi] <= i+100 && hi != n){
      hi++;
    }
    while((p[lo] < i-100 && lo != n)){
      lo++;
    }
    // new highest number of parasols
    if((hi-lo) > maxval){
      maxlocs.clear();
      maxlocs.push_back(i);
      maxval = hi-lo;
      maxlen = INT_MAX;
      int candlen = 0;
      for(int k=lo;k<hi;++k){
        candlen = std::max(candlen,std::abs(i-p[k]));
      }
      maxlen = candlen;
    // 
    }else if(hi-lo == maxval){
      int candlen = 0;
      for(int k=lo;k<hi;++k){
        candlen = std::max(candlen,std::abs(i-p[k]));
      }
      if(candlen < maxlen){
        maxlocs.clear();
        maxlocs.push_back(i);
        maxlen = candlen;
      }else if(candlen == maxlen){
        maxlocs.push_back(i);
      }
    }
  }

  // max number of parasols
  std::cout << maxval << " " << maxlen << std::endl;
  
  // print optimal locations
  for(unsigned int i=0;i<maxlocs.size();++i){
    std::cout << maxlocs[i] << " ";
  }
  std::cout << std::endl;
}

int main(){
  
  int t; std::cin >> t;
  while(t--) testcase();
}