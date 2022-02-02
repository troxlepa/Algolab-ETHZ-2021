#include <bits/stdc++.h>

void testcase(){
  int n,m;
  std::cin >> n >> m;
  int si,wi;
  std::vector<int> s(n);
  std::vector<int> w(m);
  for(int i=0;i<n;++i){
    std::cin >> si;
    s[i] = si;
  }
  for(int i=0;i<m;++i){
    std::cin >>  wi;
    w[i] = wi;
  }

  std::sort(w.begin(),w.end(),[](int a, int b){return a > b;});
  std::sort(s.begin(),s.end(),[](int a, int b){return a > b;});

  if(w[0] > s[0]){
    std::cout << "impossible" << std::endl;
    return;
  }
  for(int r=1;r<m+n;++r){
    int flag = 0;
    
    for(int i=0;i<n;++i){
      if(i*r+r-1 >= m-1){ // last box || spare workers
        if(w[i*r] > s[i]){ // last box too heavy
          flag = 1;
        }else{
          flag = 2;
        }
        break;
      }else{
        if(w[i*r] > s[i]){ // if last box to carry
          flag = 1;
          break;
        }
      }
    }
    if(flag == 0 || flag == 1){ // not enough ppl || 
      continue;
    }
    std::cout << (r-1)*3 + 2 << std::endl;
    return;
  }
}

int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--){
    testcase();
  }
}