#include <iostream>

void testcase(){
  int n; std::cin >> n;
  int even = 0;
  int odd = 0;
  int part = 0;
  for(int i=0;i<n;++i){
    int a; std::cin >> a;
    part += a;
    if(part % 2 == 0){
      even++;
    }
    else{
      odd++;
    }
  }
  std::cout << ((even * (even-1) / 2) + (odd * (odd-1) / 2) + even) << std::endl;
}


int main(){
  int t; std::cin >> t;
  while(t--) testcase();
}