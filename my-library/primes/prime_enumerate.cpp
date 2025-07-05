#include "primes.hpp"
#include <bits/stdc++.h>

using namespace std;

vector<int> prime_enumerate(int N) {
  vector<bool> is_prime(N + 1, true);
  vector<int> primes;

  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i * i <= N; i++) {
    if (is_prime[i]) {
      // i * k (k < i)はすでにふるい分けされている
      for (int j = i * i; j <= N; j += i) {
        is_prime[j] = false;
      }
    }
  }

  for (int i = 2; i <= N; ++i) {
    if (is_prime[i])
      primes.push_back(i);
  }
  return primes;
}