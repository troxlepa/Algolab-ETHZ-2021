#include<bits/stdc++.h>

void t2(){
  int n,k,w; std::cin >> n >> k >> w;
  std::vector<int> c(n);
  for(int i=0;i<n;++i){
    std::cin >> c[i];
  }
  std::vector<std::vector<int>> waterways(w);
  for(int i=0;i<w;++i){
   int l; std::cin >> l;
    waterways[i] = std::vector<int>(l);
    for(int j=0;j<l;++j){
      std::cin >> waterways[i][j];
    }
  }
  
  long maxres = 0;
  long men = k - c[0];
  
  bool checkFirst = true;
  
  if(c[0] >= k){
    checkFirst = false;
  }
  if(checkFirst){
    std::vector<int> DP(men,0);
    
    // for all waterways
    for(int i=0;i<w;++i){
      // for every island from Pyke
      int curr = 0;
      // omit Pyke, start at index 1
      for(int j=1;j<waterways[i].size();++j){
        int island_idx = j;
        int island = waterways[i][j];
        curr += c[island];
        if(curr > men) break; // early termination
        // check if DP[men - curr] + island_idx > max
        if(DP[men-curr] > 0 && DP[men-curr] + island_idx > maxres) maxres = DP[men-curr] + island_idx;
      }
      // for every island from Pyke
      curr = 0;
      for(int j=1;j<waterways[i].size();++j){
        int island_idx = j;
        int island = waterways[i][j];
        curr += c[island];
        if(curr >= men) break;
        DP[curr] = std::max(DP[curr],island_idx);
      }
    }
    
    // add Pyke
    if(maxres > 0) maxres += 1;
  }
  long maxsingle = 0;
  
  
  // check every individual waterway
  // for all waterways
  for(int i=0;i<w;++i){
    // keep left, right pointer
    int left = 0;
    int right = 0;
    int curr = 0;
    // for every island from Pyke
    while(right < waterways[i].size()){
      if(left == right){
        int island = waterways[i][right];
        curr += c[island];
        right++;
        continue;
      }
      if(curr > k){
        int island = waterways[i][left];
        curr -= c[island];
        left++;
      }else if(curr < k){
        int island = waterways[i][right];
        curr += c[island];
        right++;
      }else if(curr == k){ // if curr == k
        if(right-left > maxsingle) maxsingle = right-left;
        int island = waterways[i][left];
        curr -= c[island];
        left++;
      }
    }
  }
  
  long res = std::max(maxsingle,maxres);
  if(res == 0){
    for(int i=0;i<n;++i){
      if(c[i] == k) res = 1;
    }
  }
  
  std::cout << res << std::endl;
}

int main(){
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) t2();
}
















// waterways(n)
// islands(w_idx)
// DP(men)
