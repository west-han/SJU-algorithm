#include <stdio.h>

int BinarySearch(int start, int end, int numYN){
    int left = start;
    int right = end;

    for(int i = 0; (i < numYN) && (left != right); i++){
        int mid = (left + right) / 2;
        char c = getchar();

        if(c == 'Y'){
            left = mid + 1;
        }
        else if(c == 'N'){
            right = mid;
        }
    }

    return left;
}

int main()
{
    int a, b, numYN;
    int answer = 0;
    scanf("%d %d %d", &a, &b, &numYN);
    getchar();
    answer = BinarySearch(a, b, numYN);
    printf("%d", answer);
}