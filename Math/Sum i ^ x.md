# Sum i ^ x

```cpp
// O(x^2)
// Function to calculate Bernoulli numbers using Akiyama–Tanigawa algorithm
vector<double> bernoulli_numbers(int n) {
    vector<double> A(n + 1, 0.0);
    vector<double> B(n + 1, 0.0);
    for (int i = 0; i <= n; i++) {
        A[i] = 1.0 / (i + 1);
    }
    for (int m = 1; m <= n; m++) {
        for (int j = m; j >= 1; j--) {
            A[j - 1] = j * (A[j - 1] - A[j]);
        }
        B[m] = A[0]; // B[m] is now the m-th Bernoulli number
    }
    B[0] = 1; // B0 is 1
    return B;
}
// Function to calculate binomial coefficients
long long binomial_coefficient(int n, int k) {
    if (k == 0 || k == n) return 1;
    if (k > n) return 0;
    long long result = 1;
    for (int i = 1; i <= k; i++) {
        result *= (n - (k - i));
        result /= i;
    }
    return result;
}

// Function to calculate the sum of powers using Faulhaber's formula
// n is the number of terms and x is the power where we get sum(i^x)
//complexity is O(x^2)
double sum_of_powers(int n, int x) {
    vector<double> B = bernoulli_numbers(x + 1);
    double sum = 0.0;
    for (int j = 0; j <= x; j++) {
        sum += binomial_coefficient(x + 1, j) * B[j] * pow(n, x + 1 - j);
    }
    return sum / (x + 1);
}
```
