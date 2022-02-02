#include <bits/stdc++.h>

void testcase(){
  int n; std::cin >> n;

  std::vector<int> t(n);
  for(int i=0;i<n;++i){
    std::cin >> t[i];
  }
  
  
  if(n == 1){
    std::cout << "yes" << std::endl;
    return;
  }
  if(n == 2){
    if(std::max(t[0],t[1]) >= 2)
      std::cout << "yes" << std::endl;
    else
      std::cout << "no" << std::endl;
    return;
  }
  
  auto cmp = [&t](int a, int b){
    return t[a] < t[b];
  };
  std::priority_queue<int, std::vector<int>, decltype(cmp)> q(cmp);
  q.push(0);
  int count = n;

  while(!q.empty()){
    int idx = q.top(); q.pop();
    int val = t[idx];
    if(val < count){
      std::cout << "no" << std::endl;
      return;
    }
    count--;
    if(idx*2+1 < n) q.push(idx*2+1);
    if(idx*2+2 < n) q.push(idx*2+2);
    
  }
  std::cout << "yes" << std::endl;
  return;
}

int main(){
  int t; std::cin >> t;
  while(t--){
    testcase();
  }
}