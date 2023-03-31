#include <bits/stdc++.h>

using namespace std;

int trucks_n, pallet_types;
vector<int> trucks;
vector<int> pallets;
int available_dimensions[32];

int solve() {
  int assigned = 0;
  int next_pallet = 0;

  // for (int i = 0; i < trucks_n; i++) {
  //   for (int k = 0; k < 31; k++) {
  //     int search_dim = (1 << k);
  //     available_space[k]+= trucks[i] & search_dim;
  //   }
  // }

  for (int k = 0; k < 31; k++) {
    int search_dim = (1 << k);

    // assign weights up to this one
    for (int i = 0; i < trucks_n; i++) {
      // the available space is...
      int space = trucks[i] & search_dim;

      int pallet_size = (1 << next_pallet);
      while (space >= pallet_size) {
        while (next_pallet < pallet_types && pallets[next_pallet] == 0) {
          // find the next assignable pallet
          next_pallet++;
          pallet_size = (1 << next_pallet);
        }
        if (next_pallet >= pallet_types || pallets[next_pallet] == 0) {
          // we ran out of pallet types...
          break ;
        }
        // printf("assigning pallets of sz %d, %d available, space is %d\n", pallet_size, pallets[next_pallet], space);

        // we have some pallets of type next_pallet available and enough space
        int to_assign = min(pallets[next_pallet], space / pallet_size);
        // printf("Assigning %d\n", to_assign);
        space-= to_assign * pallet_size;
        // trucks[i]-= to_assign * pallet_size;
        pallets[next_pallet]-= to_assign;
        assigned+= to_assign;
      }
    }
  }

  // for (int k = 0; k < 31; k++) {
  //   // either occupy all available_space[k] or use up all pallet[k]
  //   int pallet_size = (1 << next_pallet);
  //   int search_dim = (1 << k);
  //   while (next_pallet <= k) {
  //     while (next_pallet < pallet_types && next_pallet <= k && pallets[next_pallet] == 0) {
  //       next_pallet++;
  //       pallet_size = (1 << next_pallet);
  //     }


  //   }
  // }

  return assigned;
}

long long riciclo(int N, int M, vector<int> T, vector<int> P) {
  trucks_n = N;
  pallet_types = M;
  trucks = T;
  pallets = P;

  return solve();
}
