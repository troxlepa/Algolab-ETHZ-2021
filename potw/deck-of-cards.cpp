#include <iostream>
#include <vector>
#include <limits>

void testcase(){
  int n; std::cin >> n;
  long long int k; std::cin >> k;
  int tmax = std::numeric_limits<int>::max();
  std::vector<int> v;
  std::vector<long long int> cumsum(n);
  for(int i=0;i<n;++i){
    long long int vi; std::cin >> vi;
    if(i == 0){
      cumsum[i] = vi;
    }else{
      cumsum[i] = cumsum[i-1]+vi;
    }
    v.push_back(vi);
  }
  int diff = tmax;
  long long int resi = 0;
  long long int resj = 0;
  int j = 0;
  int i = 0;
  while(true){
    int newsum = std::abs(cumsum[i]-cumsum[j])+v[i];
    if(std::abs(k-newsum) < diff){
      diff = std::abs(k-newsum);
      resi = i;
      resj = j;
    }
    if(newsum < k){
      // add element
      if(j == n-1){
        break;
      }
      j++;
    }else{
      // remove element
      if(i == j){
        if(j == n-1){
          break;
        }
        j++;
      }else{
        i++;
      }
    }

  }
  std::cout << resi;
  std::cout << " ";
  std::cout << resj << std::endl;
}

int main(){
  int t;std::cin >> t;
  for(int i=0;i<t;++i){
    testcase();
  }

}