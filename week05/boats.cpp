#include <bits/stdc++.h>

void testcase(){
  int n; std::cin >> n;
  int l,p;
  std::vector<std::pair<int,int>> v(n);
  
  for(int i=0;i<n;++i){
    std::cin >> l >> p;
    v[i] = {l,p};
  }
  auto comp = [](std::pair<int,int> a, std::pair<int,int> b){
    return a.second < b.second;
  };
  std::sort(v.begin(),v.end(),comp);
  
  int minstart = INT_MAX;
  int minidx = -1;
  for(int i=0;i<n;++i){
    if(v[i].second < minstart){
      minstart = v[i].second;
      minidx = i;
    }
  }
  int pos = minstart;
  int count = 1;
  
  for(int i=0;i<n;++i){
    if(i == minidx) continue;
    int l = v[i].first;
    int p = v[i].second;
    
    if(pos <= p){
      int lowest_finish = INT_MAX;
      int lfi = -1;
      int the_finish = std::max(pos+l, p);
      int j=i+1;
      
      while(v[j].second <= the_finish&&j<n){
        if(j == minidx){
          j++;
          continue;
        }
        int cand_lowest_finish = std::max(pos+v[j].first, v[j].second);
        if(cand_lowest_finish < lowest_finish){
          lowest_finish = cand_lowest_finish;
          lfi = j;
        }
        j++;
      }
      if(lowest_finish < the_finish){
        pos = lowest_finish;
        i=lfi;
        count++;
        continue;
      }
      pos = the_finish;
      count++;
    }
  }
  std::cout << count << std::endl;
  
}

int main(){
  std::ios::sync_with_stdio(false);
  int t;std::cin >> t;
  while(t--){
    testcase();
  }
}