基本思想：
    在长度为N的无序数组中，第一次遍历n-1个数，找到最小的数值与第一个元素交换；
    第二次遍历n-2个数，找到最小的数值与第二个元素交换；
    。。。
    第n-1次遍历，找到最小的数值与第n-1个元素交换，排序完成。
平均时间复杂度：O(n^2)

#include <stdio.h>
int main(int argc, char* argv[])
{
    int a[] = {25,96,2,52,36,54,58,69,11,225,445,645,154,41,25,14,26,33,14,14,112,2,4,12,54,125,2,1,0,5,45,5};
    int i, j;
    int min, tmp;
    int len = sizeof(a)/sizeof(int);

    printf("the len of array is %d\n",len);

    for(i = 0;i < len;i++)
    {
        min = i;
        for(j = i;j < len; j++)
        {
            if(a[j] < a[min])
                min = j;
        }
        if(min != i)
        {
            tmp = a[min];
            a[min] = a[i];
            a[i] = tmp;
        }
    }

    for(i = 0;i < len;i++)
    {
        printf("%d, ",a[i]);
    }
    printf("\n");

    return 0;
}