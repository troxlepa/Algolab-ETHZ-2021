#include <bits/stdc++.h>

void testcase(){
  int n,q; std::cin >> n >> q;
  std::unordered_map<std::string,std::pair<int,std::string>> name;
  for(int i=0;i<n;++i){
    std::string s;
    std::cin >> s;
    int a; std::cin >> a;
    name.insert({s,std::make_pair(a,"")});
  }
  
  for(int i=0;i<n-1;++i){
    std::string s,p;
    std::cin >> s >> p;
    name[s].second = p;
  }
  
  int max_levels = 9;
  std::vector<std::unordered_map<std::string,std::pair<int,std::string>>> skip(max_levels);
  skip[0] = name;
  
  for(int level=1;level < max_levels;++level){
    skip[level].reserve(skip[level-1].size());
    skip[level].rehash(skip[level-1].size());
    for(auto& fq: skip[level-1]){
      std::string src = fq.first;
      std::string dest = fq.first;
      for(int i=0;i<3;++i){
        if(dest == "" || dest == "-1") break;
        dest = (skip[level-1])[dest].second;
      }
      if(dest == "" || dest == "-1"){
        skip[level].insert({src,std::make_pair(0,"-1")});
        continue;
      }
      int res_age = (skip[level-1])[dest].first;
      std::string res_name = level == 1 ? dest : (skip[level-1])[dest].second;
      skip[level].insert({src,std::make_pair(res_age,res_name)});
    }
  }
  std::string temp;
  for(int i=0;i<q;++i){
    std::string s;
    int a;
    std::cin >> s >> a;
    
    std::string younger = s;
    
    std::string older = s;
    for(int level=max_levels-1;level>=1;--level){
      while(true){
        auto q = (skip[level])[older];
        if(q.first > a || q.second == "-1" || q.second == "") break;
        younger = older;
        older = q.second;
      }
    }
    
    while(name[older].first <= a && name[older].second != ""){
      std::string temp = older;
      older = name[older].second;
      younger = temp;
    }
    
    if(name[older].second == "" && name[older].first <= a){
      std::cout << older << " ";
    }else{
      std::cout << younger << " ";
    }
      
  }
  std::cout << std::endl;
  
}


int main(){
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
  int t; std::cin >> t;
  while(t--) testcase();
}