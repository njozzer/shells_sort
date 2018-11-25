#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

void simple_sort(int *A, int N)
{
    unsigned i,j,k;
    int t;
    for( k = N / 2; k > 0; k /= 2 )
        for( i = k; i < N; i++ )
        {
            t = A[i];
            for( j = i; j >= k; j -= k )
            {
                if( t < A[j - k] )
                    A[j] = A[j - k];
                else
                    break;
            }
            A[j] = t;
        }
}

struct swap_struct {
    int *arr;
    int n;
    int *i;
    int *j;
    int *k;
};
void *thread(void *args){
    swap_struct *arguments = (swap_struct*) args;
    int t;
    int *arr = arguments->arr;
    int *i = arguments->i;
    int *j = arguments->j;
    int *k = arguments->k;
    t = arr[i[0]];
    for( j[0] = i[0]; j[0] >= k[0]; j[0] -= k[0] )
    {
        if( t < arr[j[0] - k[0]] )
            arr[j[0]] = arr[j[0] - k[0]];
        else
            break;
    }
    arr[j[0]] = t;
    pthread_exit(0);
}
void func(int *arr,int n){

    int i,j,k;
    int t;
    for( k = n / 2; k > 0; k /= 2 ) {
        pthread_t *th = new pthread_t[n - k];
        for( i = k; i < n; i++ )
        {
            pthread_t th;
            swap_struct args;
            args.arr = arr;
            args.n = n;
            args.i = &i;
            args.j = &j;
            args.k = &k;
            pthread_create(&th,NULL,thread,(void*)&args);
        }

    }
}

class ShellsSort {
private:
    int *arr;
    int n;
public:

    void sort(void ( *sort_function )(int*,int) ){
        sort_function(arr,n);
    }

    ShellsSort(int *arr,int n){
        this->arr = new int[n];
        memcpy(this->arr,arr,n * sizeof( int ) );
        this->n = n;
    }
};


int main() {
    srand (time(NULL) );
    int n = 10000000;
    clock_t t1, t2, t3, t4;
    int *arr = new int[n];
    int *arr2 = new int[n];
    for( int i = 0; i < n; i++ ) {
        arr[i] = rand() % 100000 - 500;
    }
    memcpy(arr2,arr,sizeof( int ) * n);
    ShellsSort sh(arr,n);
    ShellsSort sh2(arr,n);
    /*for( int i = 0; i < n; i++ ) {
        std::cout << arr[i] << ' ';
       }
       std::cout << '\n';
     */

    t1 = clock();
    sh.sort(simple_sort);
    t2 = clock();
    std::cout << "\nTIME without multithreading : " << ( t2 - t1 ) / (double)CLOCKS_PER_SEC;
    sh2.sort(func);
    t3 = clock();
    /*
       std::cout << '\n';
       for( int i = 0; i < n; i++ ) {
        std::cout << arr2[i] << ' ';
       }*/

    std::cout << "\nTIME without multithreading : " << ( t3 - t2 ) / (double)CLOCKS_PER_SEC;
    return 0;
}
