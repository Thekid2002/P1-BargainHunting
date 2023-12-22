#include <stdio.h>
#include <math.h>
#include <time.h>

/* Change this to 500, 1000, 2000, 6000, or 9000 for the different lists*/
#define N 6000

int LinSearch(int array[], int x, int* k);
int BinSearch(int array[], int x, int* k);

int main(void){
    int x;
    char filename[20];
    FILE *myFile;
    int array[N];
    int k;
    /*change this for more or less runs of the algorithm*/
    int runs = pow(10,6);
    int i;

    int runTimes = 0;

    sprintf(filename, "List%d.txt", N);
    printf("What number are we searching for?\n"); /* Feel free to alter this*/
    scanf("%d", &x);

    myFile = fopen(filename, "r");

    /* iList is read into array */
    for (k = 0; k < N; k++){
        fscanf(myFile, "%d", &array[k]);
    }
    fclose(myFile);

    printf("The size of the list is %d\n", N);

    /* start time */
    double startTime = clock();
    

    for (i = 0; i < runs; i++){
        BinSearch(array, x, &runTimes);
    }

    /* stop time and print */
    double endTime = clock();
    double duration = (endTime - startTime) / CLOCKS_PER_SEC;
    printf("BinSearch needed: %.7fs and %d runs\n", duration, runTimes);



    /* start time */
    startTime = clock();

    for (i = 0; i < runs; i++){
        LinSearch(array, x, &runTimes);
    }

    /* stop time and print */
    endTime = clock();
    duration = (endTime - startTime) / CLOCKS_PER_SEC;
    printf("LinSearch needed: %.7fs and %d runs\n", duration, runTimes);

    /* Prints the result */
    int result=LinSearch(array, x, &runTimes);
    if (result == 0){
        printf("%d is not in the list \n",x);
    }
    else {
        printf("%d is in position %d\n",array[result],result+1);
    }

    result=BinSearch(array, x, &runTimes);
    if (result == 0){
        printf("%d is not in the list \n",x);
    }
    else {
        printf("%d is in position %d\n",array[result],result+1);
    }
    printf("Done!\n"); /* Feel free to be more creative here */
    return 0;
}

/*
 * Lin search, searches through an array linearly
 *
 * x is the number to search for
 * k is the number of runs
 * array is the array to search through
 */
int LinSearch(int array[], int x, int* k){
    *k = 0;
    int i = 0;
    while ( i <= N && x != array[i]){
        *k += 1;
        i += 1;
    }
    if( i <= N ){
        return i;
    }else{
        return 0;
    }
}

/*
 * Bin search, searches through an array with binary search
 *
 * x is the number to search for
 * k is the number of runs
 * array is the array to search through
 */
int BinSearch(int array[], int x, int* k){
    *k = 0;
    int i = 0;
    int j = N-1;

    while ( i < j ){
        *k += 1;
        int m = round((i+j)/2);
        if( x > array[m] ){
            i = m + 1;
        }else{
            j = m;
        }
    }
    if( x == array[i] ){
        return i;
    }else{
        return 0;
    }
}