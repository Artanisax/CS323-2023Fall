#include <omp.h>

const int N = 8e8;
const int MOD = 1e4+7;

int main()
{
    int sum[4]{};
    int n = N / 4;
    #pragma omp parallel for num_thread(4)
    for (int i = 0; i < 3; i++)
    {
        int square, cube;
        for (int j = i * n + 1; j < (i + 1) * n; j++)
        {
            square = i % MOD * i % MOD % MOD;
            cube = i % MOD * i % MOD * i % MOD % MOD;
            sum[i] = (sum[i] + square + cube) % MOD;
        }
    }
    return 0;
}