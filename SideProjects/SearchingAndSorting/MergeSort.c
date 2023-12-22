#include <stdio.h>
#include <stdlib.h>

void Merge(int L[], int start, int end, int mid);
void MergeSort(int L[], int start, int end);
void printList(int L[], int size);

int main(void){
    int L[] = { 5, 3, 8, 1, 6, 10, 7, 2, 4, 9 };
    int L_size = sizeof(L) / sizeof(L[0]);

    printf("list has size %d\n",L_size);
    printf("Given list \n");
    printList(L, L_size);

    MergeSort(L, 0, L_size - 1);

    printf("The sorted list \n");
    printList(L, L_size);
    return 0;
}

void Merge(int L[], int start, int end, int mid){
    int n1=mid-start+1;
    int n2=end-mid;
    int L1[n1];
    int L2[n2];
    for(int i=0;i<n1;i++)
        L1[i]=L[start+i];
    for(int i=0;i<n2;i++)
        L2[i]=L[mid+1+i];

    int i=0;
    int j=0;

    while(i<n1 && j<n2)
    {
        if (L1[i] <= L2[j])
        {
            L[start+i+j]=L1[i];
            i++;
        }
        else {
            L[start+i+j]=L2[j];
            j++;
        }
    }
    if (i==n1)
    {
        for(int k=j; k<=end-mid-1;k++) {
            L[start + i + k] = L2[k];
        }
    }
    else
    {
        for (int k = i; k <= mid - start; k++) {
            L[start + j + k] = L1[k];
        }
    }
}

void MergeSort(int L[], int start, int end){
    if(start<end)
    {
        int mid=(start+end)/2;
        MergeSort(L,start,mid);
        MergeSort(L,mid+1,end);

        Merge(L,start,end,mid);
    }
}

void printList(int L[], int size){
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", L[i]);
    printf("\n");
}