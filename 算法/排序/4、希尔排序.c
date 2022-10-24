https://www.bilibili.com/video/BV1XG4y167gF/?spm_id_from=trigger_reload&vd_source=7a946851230e2436678a65b33cc6be26
前言：
    数据序列1： 13-17-20-42-28 利用插入排序，13-17-20-28-42. Number of swap:1;
    数据序列2： 13-17-20-42-14 利用插入排序，13-14-17-20-42. Number of swap:3;
    如果数据序列基本有序，使用插入排序会更加高效。

基本思想：
    在要排序的一组数中，根据某一增量分为若干子序列，并对子序列分别进行插入排序。
    然后逐渐将增量减小,并重复上述过程。直至增量为1,此时数据序列基本有序,最后进行插入排序。

平均时间复杂度：O(n^1.3)

#include <stdio.h>
int main(int argc, char* argv[])
{
    int a[] = {25,96,2,52,36,54,58,69,11,225,445,645,154,41,25,14,26,33,14,14,112,2,4,12,54,125,2,1,0,5,45,5};
    int i, j, k;
    int tmp;
    int len = sizeof(a)/sizeof(int);

    int incre = len;

   while(1)
   {
       incre = incre/2;

       for(k = 0; k < incre; k++) //根据增量分为若干子序列
       {
           for(i = k + incre; i < len; i += incre)
           {
               for(j = i ;j  > k; j -= incre)
               {
                   if(a[j] < a[j - incre])
                   {
                       tmp = a[j - incre];
                       a[j - incre] = a[j];
                       a[j] = tmp;
                   }
                   else
                   {
                       break;
                   }
               }
           }
       }

       if(incre == 1){
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
