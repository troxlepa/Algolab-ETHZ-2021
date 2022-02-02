#include <bits/stdc++.h>

long D,T;
std::vector<std::pair<long,long>> dt;
std::vector<std::pair<long,long>> dt1;
std::vector<std::pair<long,long>> dt2;

std::vector<std::pair<long,long>> splitlist(std::vector<std::pair<long,long>>& dtx, int idx, long d_sum, long t_sum, long si){
  int n = dtx.size();
  long long total = 1 << n;
  
  std::vector<std::pair<long,long>> sl(total);

  // Consider all numbers from 0 to 2^n - 1
  for (long long i = 0; i < total; i++) {
    std::pair<long,long> sum = {0,0};

    for (int j = 0; j < n; j++){
      if (i & (1 << j)){
        sum.first += dtx[j].first + si;
        sum.second += dtx[j].second;
      }
    }
    sl[i] = sum;
  }
  return sl;
}

bool ccsolve(int idx, long d_sum, long t_sum, long si){
  int n = dt.size();
  // 1. Split
  int md = n / 2;
  dt1.resize(md);
  dt1.assign(dt.begin(),dt.begin()+md);
  dt2.resize(n-md);
  dt2.assign(dt.begin()+md,dt.end());
  
  // 2.List
  std::vector<std::pair<long,long>> l1 = splitlist(dt1,idx,d_sum,t_sum,si);
  std::vector<std::pair<long,long>> l2 = splitlist(dt2,idx,d_sum,t_sum,si);
  
  // 3. sort l1
  auto cmp = [](std::pair<long,long> a, std::pair<long,long> b){
    if(a.second == b.second){
      return a.first < b.first;
    }else if(a.second < b.second){
      return true;
    }else{
      return false;
    }
  };
  
  // insert empty element
  l1.push_back({0,0});
  l2.push_back({0,0});
  
  std::sort(l1.begin(),l1.end(),cmp);
  
  // 4. set max distance for binary search
  long max_d = 0;
  for(int i=0;i<l1.size();++i){
    if(l1[i].first > max_d){
      max_d = l1[i].first;
    }else{
      l1[i].first = max_d;
    }
  }

  // 5. binary search over all elements of l2
  auto mcmp = [](std::pair<long,long> el,long target){
    return target > el.second;
  };
  for(int i=0;i<l2.size();++i){
    if(l2[i].second >= T) continue;

    auto lower = std::lower_bound(l1.begin(),l1.end(),T-l2[i].second,mcmp);

    if(lower != l1.begin()){
      lower--;
    }
    if(lower != l1.end()){
      if((*lower).first + l2[i].first >= D && (*lower).second + l2[i].second < T){
        return true;
      }
    }
  }
  return false;
}

void testcase(){
  int n,m;
  std::cin >> n >> m >> D >> T;
  dt.resize(n);
  for(int i=0;i<n;++i){
    long d,t; std::cin >> d >> t;
    dt[i] = {d,t};
  }
  std::vector<long> s(m);
  for(int i=0;i<m;++i){
    std::cin >> s[i];
  }

  if(m==0){
    bool isRecFirst = ccsolve(0,0,0,0);
    if(isRecFirst){
      std::cout << "0" << std::endl;
    }else{
      std::cout << "Panoramix captured" << std::endl;
    }
    return;
  }
  
  bool isRecFirst = ccsolve(0,0,0,0);
  if(isRecFirst){
    std::cout << "0" << std::endl;
    return;
  }
  
  int left = 0;
  int right = m-1;
  int middle = -1;
  int newMiddle = (left+right) / 2;
  long minTrue = LONG_MAX;
  while(newMiddle != middle){
    bool isRec = ccsolve(0,0,0,s[newMiddle]);
    if(isRec){
      right = newMiddle;
      middle = newMiddle;
      newMiddle = (left+right)/2;
      minTrue = middle;
    }else{
      left = newMiddle;
      middle = newMiddle;
      newMiddle = (left+right)/2;
    }
  }
  if(minTrue < LONG_MAX-1){
    std::cout << minTrue+1 << std::endl;
  }else{
    std::cout << "Panoramix captured" << std::endl;
  }
  return;
}

int main(){
  std::ios::sync_with_stdio(false);
  
  int t; std::cin >> t;
  while(t--) testcase();
}