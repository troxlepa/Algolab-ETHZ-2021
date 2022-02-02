#include <bits/stdc++.h>

inline int c(int i, int j, int k, int l){
  return i*(5*5*25)+j*(5*25)+k*(25)+l;
}

inline int c(int i, int j1, int j2, int k1, int k2, int l){
  return i*(5*5*5*5*25)+j1*(5*5*5*25)+j2*(5*5*25)+k1*(5*25)+k2*25+l;
}

inline int cf(int nt, int q, int t1){
  std::set<int> s;
  s.insert(nt);
  s.insert(q);
  s.insert(t1);
  s.erase(0);
  return 1000*s.size();
}

inline int cf(int a, int b){
  std::set<int> s;
  s.insert(a);
  s.insert(b);
  s.erase(0);
  return 1000*s.size();
}
  
void testcase(){
  int n,k,m; std::cin >> n >> k >> m;
  int multiplier = 1;
  if(m == 3){
    multiplier = 25;
  }
  std::vector<int> DP(n*5*5*25*multiplier,0);
  std::vector<int> val(n);
  
  for(int i=0;i<n;++i){
    std::cin >> val[i];
  }
  

  int firstval = val[0]+1;
  if(m == 3){
    DP[c(0,firstval,0,0,0,12+1)] = 998;
    DP[c(0,0,0,firstval,0,12-1)] = 998;
  }else{
    DP[c(0,firstval,0,12+1)] = 998;
    DP[c(0,0,firstval,12-1)] = 998;
  }

  
  if(m == 3){
    for(int idx=1;idx<n;++idx){
      for(int j=0;j<25;++j){
        for(int k=0;k<25;++k){
          for(int bal=1;bal<24;++bal){
            if(DP[c(idx-1,k/5,k%5,j/5,j%5,bal)] > 0){
              int j1 = j/5;
              int j2 = j%5;
              int k1 = k/5;
              int k2 = k%5;
              int last = DP[c(idx-1,k1,k2,j1,j2,bal)];
              int newtype = val[idx]+1;
              
              int npropval = last + cf(newtype,k1,k2) - (1<<std::abs(bal-12+1));
  
              
              int nnv = c(idx,newtype,k1,j1,j2,bal+1);
              if(npropval > DP[nnv]){
                DP[nnv] = npropval;
              }
              
              int spropval = last + cf(newtype,j1,j2) - (1<<std::abs(bal-12-1));
              
              int ssv = c(idx,k1,k2,newtype,j1,bal-1);
              if(spropval > DP[ssv]){
                DP[ssv] = spropval;
              }
            }
          }
        }
      }
    }
  }
  else if(m == 2){
    for(int idx=1;idx<n;++idx){
      for(int j=0;j<5;++j){
        for(int k=0;k<5;++k){
          for(int bal=1;bal<24;++bal){
            if(DP[c(idx-1,k,j,bal)] > 0){
              int last = DP[c(idx-1,k,j,bal)];
              int newtype = val[idx]+1;
              int npropval = last + cf(newtype,k) - (1<<std::abs(bal-12+1));
              int nnv = c(idx,newtype,j,bal+1);
              if(npropval > DP[nnv]){
                DP[nnv] = npropval;
              }
              
              int spropval = last + cf(newtype,j) - (1<<std::abs(bal-12-1));
              int ssv = c(idx,k,newtype,bal-1);
              if(spropval > DP[ssv]){
                DP[ssv] = spropval;
              }
            }
          }
        }
      }
    }
  }
  
  int res = 0;
  
  if(m == 2){
    for(int no=0;no<5;++no){
      for(int so=0;so<5;++so){
        for(int b=0;b<25;++b){
          if(DP[c(n-1,no,so,b)] > res){
            res = DP[c(n-1,no,so,b)];
          }
        }
      }
    }
  }else{
    for(int no=0;no<25;++no){
      for(int so=0;so<25;++so){
        for(int b=0;b<25;++b){
          if(DP[c(n-1,no/5,no%5,so/5,so%5,b)] > res){
            res = DP[c(n-1,no/5,no%5,so/5,so%5,b)];
          }
        }
      }
    }
  }
  
  std::cout << res << std::endl;

}

int main(){
  std::ios::sync_with_stdio(false);
  int t;std::cin >> t;
  for(int i=0;i<t;++i){
    testcase();
  }
}