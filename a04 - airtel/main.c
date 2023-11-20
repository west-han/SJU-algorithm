#include <stdio.h>
#include <stdint.h>
#include <windows.h>

#define MAX     30

int A[MAX] = { 0, };
int H[MAX] = { 0, };

int airtelDC(const int n, const int s, const int d);
int airtelDP(const int n, const int s, const int d);

int main()
{
    LARGE_INTEGER freq, start, end;
    double diff = 0.0;
    int minCost = 0;
    QueryPerformanceFrequency(&freq);

    A[1] = 1;
    for (int i = 2; i < MAX; i++)
    {
        A[i] = A[i - 1] + A[i - 1] % 5 + 3;
    }
    H[1] = 5;
    for (int i = 2; i < MAX; i++)
    {
        H[i] = (H[i - 1] + i) % 9 + 1;
    }

    printf("\tn\ts\td\tmincost\tversion\tcputime\n");

    int n = 6, s = 0, d = 0;
    int testCases[][2] = { 0, 4, 2, 5, 2, 4 };
    for (int i = 0; i < 3; i++)
    {
        s = testCases[i][0];
        d = testCases[i][1];

        QueryPerformanceCounter(&start);
        minCost = airtelDC(n, s, d);
        QueryPerformanceCounter(&end);
        diff = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
        printf("\t%d\t%d\t%d\t%d\tDC\t%lf\n", n, s, d, minCost, diff);

        QueryPerformanceCounter(&start);
        minCost = airtelDP(n, s, d);
        QueryPerformanceCounter(&end);
        diff = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
        printf("\t%d\t%d\t%d\t%d\tDP\t%lf\n", n, s, d, minCost, diff);
    }
    n = MAX;
    s = 1;
    d = MAX - 2;

    QueryPerformanceCounter(&start);
    minCost = airtelDC(n, s, d);
    QueryPerformanceCounter(&end);
    diff = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    printf("\t%d\t%d\t%d\t%d\tDP\t%lf\n", n, s, d, minCost, diff);

    QueryPerformanceCounter(&start);
    minCost = airtelDP(n, s, d);
    QueryPerformanceCounter(&end);
    diff = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    printf("\t%d\t%d\t%d\t%d\tDP\t%lf\n", n, s, d, minCost, diff);
}


int rAirtel(const int n, const int s, const int d)
{
    // base case
    if (d == s)
    {
        return 0;
    }

    // recursive case

    //printf("recursion invoked - s: %d d: %d\n", s, d);

    int minCost = INT32_MAX;
    for (int k = s; k < d; k++)
    {
        // 정방향, k까지 가는 최소 비용 + k에서 d로 가는 비용 + k의 숙박비
        int cost = rAirtel(n, s, k) + A[d - k] + H[k];
        
        // 시작 도시인 경우 숙박비 제외
        /*if (s == k)
        {
            cost -= H[k];
        }*/

        // 최소 비용 갱신
        minCost = minCost < cost ? minCost : cost;
    }

    //printf("recursion return - s: %d d: %d, minCost: %d\n", s, d, minCost);

    return minCost; // s에서 d로 가는 최소 비용 (+ 시작 도시의 숙박비) 반환
}

int airtelDC(const int n, const int s, const int d)
{
    //return rAirtel(n, s, d);
    return rAirtel(n, s, d) - H[s]; // s에서 d까지 가는 최소 비용 반환(s 숙박비 제외)
}

int airtelDP(const int n, const int s, const int d)
{
    int m[MAX] = { 0, };

    for (int i = s + 1; i <= d; i++)
    {
        m[i] = INT32_MAX;
        for (int j = s; j < i; j++)
        {
            // j를 거쳐서 i로 가는 최소 비용 = j까지 가는 최소 비용 + j에서 i로 가는 비용 + i의 숙박비
            int cost = m[j] + A[i - j] + H[i];
            
            // 도착 도시인 경우 숙박비 제외하고 계산
            /*if (i == d)
            {
                cost -= H[i];
            }*/

            //printf("from %d to %d through %d, m[%d]=%d, A[%d]=%d, H[%d]=%d, cost=%d, old_m[%d]=%d, ", 
            //    s, i, j, j, m[j], i - j, A[i - j], i, H[i], cost, i, m[i]);

            m[i] = m[i] < cost ? m[i] : cost; // i까지 가는 최소 비용 갱신
            
            //printf("new_m[%d]=%d\n", i, m[i]);
        }
    }

    // return m[d];
    return m[d] - H[d]; // s에서 d까지 가는 최소 비용 반환(d 숙박비 제외)
}