int fast_Fibonacci(int n)
{
 int i = 1, h = 1, j = 0, k = 0, t;
 while (n > 0)
 {
 if (n % 2 == 1)
 t = j * h, j = i * h + j * k + t, i = i * k + t;
 t = h * h, h = 2 * k * h + t, k = k * k + t, n = n / 2;
 }
 return j;
}
