#include <iostream>
#include <vector>
#include <utility>

void testcase(){
  int n;std::cin >> n;
  std::vector<std::vector<int>> mDP(n+1,std::vector<int>(n+1,0));
  std::vector<std::vector<int>> yDP(n+1,std::vector<int>(n+1,0));

  std::vector<int> v(n);
  for(int i=0;i<n;++i){
    int vi;std::cin >> vi;
    v[i] = vi;
  }
  v.push_back(0);
  
  for(int i=0;i<=n;++i){
    for(int j=0;j<=n-i;++j){
      if(i==0){
        mDP[j][j] = v[j];
        yDP[j][j] = 0;
      }else{
        mDP[j][j+i] = std::max(yDP[j+1][j+i] + v[j],yDP[j][j+i-1]+ v[j+i]);
        yDP[j][j+i] = std::min(mDP[j+1][j+i],mDP[j][j+i-1]);
      }
    }
  }
  
  int res = mDP[0][n-1];
  std::cout << res << std::endl;
}

int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0;i<t;++i){
    testcase();
  }
}