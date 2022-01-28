#include <iostream>
#include <vector>

void testcase(){
  int n; std::cin >> n;
  int max = 0;
  int res = n;
  for(int i=0;i<n;++i){
    int h; std::cin >> h;
    if(max<=i && max > 0 && res == n){
      res = i;
    }
    max = std::max(max,i+h);
  }
  std::cout << res << std::endl;
  
}

int main(){
  int t; std::cin >> t;
  while(t--) testcase;
}