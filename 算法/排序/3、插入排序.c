基本思想：
    在要排序的一组数中，假定前n-1个数已经排好序，现在将第n个数插到前面的有序数列中，使得这n个数也是排好顺序的。如此反复循环，直到全部排好顺序。
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
        for(j = i + 1;j > 0; j--)
        {
            if(a[j -1 ] > a[j])
            {
                tmp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = tmp;
            }
            else
                break;
        }
    }

    for(i = 0;i < len;i++)
    {
        printf("%d, ",a[i]);
    }
    printf("\n");

    return 0;
}