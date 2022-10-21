基本思想：两个数比较大小，较大的数下沉，较小的数冒起来。
平均时间复杂度：O(n^2)

#include <stdio.h>
int main(int argc, char* argv[])
{
    int a[] = {25,96,2,52,36,54,58,69,11,225,445,645,154,41,25,14,26,33,14,14,112,2,4,12,54,125,2,1,0,5,45,5};
    int i, j;
    int tmp;
    int len = sizeof(a)/sizeof(int);

    printf("the len of array is %d\n",len);

    for(i = 0;i < len;i++)
    {
        for(j = 0;j < len - i - 1; j++)
        {
            if(a[j] > a[j + 1])
            {
                tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }

    for(i = 0;i < len;i++)
    {
        printf("%d, ",a[i]);
    }
    printf("\n");

    return 0;
}