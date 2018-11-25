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
void print(int *arr,int n){
    std::cout << '\n';
    for( int i = 0; i < n; i++ ) {
        std::cout << arr[i] << ' ';
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
    /*swap_struct *arguments = (swap_struct*) args;
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
     */
    int *e = (int*)args;
    std::cout << e[0] << '\n';
    pthread_exit(0);
}
void func(int *arr,int n){

    int i,j,k;
    int t;
    for( k = n / 2; k > 0; k /= 2 ) {
        int num = n - k + 1;
        pthread_t *th = new pthread_t[n - k + 1];
        int l = 0;
        for( i = k; i < n; i++ ) {
            pthread_create(&( th[l] ),NULL,thread,(void*)&l);
            l++;
        }
        for ( int p = 0; p < l; p++ ) {
            pthread_join(th[p],NULL);
        }
        std::cout << "/* message */" << '\n';
        /*pthread_t *th = new pthread_t[n - k + 1];
           for( i = k; i < n; i++ )
           {
            swap_struct *args = new swap_struct;
            args->arr = arr;
            args->n = n;
            args->i = &i;
            args->j = &j;
            args->k = &k;
            int e = pthread_create(&( th[i - k] ),NULL,thread,(void*)args);
            std::cout << i << '\n';
           }
           for( int l = 0; l < n - k; l++ ) {
            std::cout << pthread_join(th[i],NULL) << '\n';
           }
           delete th;*/
    }
}

void *some_func(void* args){
    int *arr = (int*)args;
    for( int i = 0; i < 10000; i++ ) {
        std::cout << arr[i] << '\n';
    }
}
void foo(){
    int n = 10000;
    int *arr = new int[n];
    for( int i = 0; i < n; i++ ) {
        arr[i] = rand() % 100000 - 500;
    }
    pthread_t *pt = new pthread_t;
    pthread_create(pt,NULL,some_func,(void*)arr);
    pthread_join(pt[0],NULL);
    std::cout << "/* message */" << '\n';
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
    int n = 1000;
    clock_t t1, t2, t3, t4;
    int *arr = new int[n];
    int *arr2 = new int[n];
    for( int i = 0; i < n; i++ ) {
        arr[i] = rand() % 100000 - 500;
    }
    memcpy(arr2,arr,sizeof( int ) * n);
    ShellsSort sh(arr,n);
    ShellsSort sh2(arr2,n);

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

    /*std::cout << "\nTIME without multithreading : " << ( t3 - t2 ) / (double)CLOCKS_PER_SEC;*/
    return 0;
}
