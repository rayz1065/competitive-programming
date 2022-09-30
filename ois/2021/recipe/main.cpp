#include <bits/stdc++.h>

using namespace std;

int n_ingredients, m_recipes;
double total_weights[1005];
int weights[1005];

int main () {
    cin >> n_ingredients >> m_recipes;
    for (int i = 0; i < m_recipes; i++) {
        double normalizer = 0;
        for (int j = 0; j < n_ingredients; j++) {
            cin >> weights[j];
            normalizer += weights[j];
        }
        normalizer = 1000000 / normalizer;

        for (int j = 0; j < n_ingredients; j++) {
            total_weights[j] += weights[j] * normalizer;
        }
    }

    for (int j = 0; j < n_ingredients; j++) {
        cout << (int)(total_weights[j] / m_recipes) << " ";
    }
    cout << "\n";
}