#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include <vector>
void print(int *arr,int n){
    std::cout << '\n';
    for( int i = 0; i < n; i++ ) {
        std::cout << arr[i] << ' ';
    }
    std::cout <<  '\n';
}
void shell(int *A, int N)
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
void simple_sort(int *arr, int n)
{
    unsigned i,j,k;
    int t;
    for( k = n / 2; k > 0; k /= 2 )
        for( i = k; i < n; i++ )
        {
            //print(arr,n);
            t = arr[i];
            for( j = i; j >= k; j -= k )
            {
                if( t < arr[j - k] )
                    arr[j] = arr[j - k];
                else
                    break;
            }
            arr[j] = t;
        }
}

void merge_sort(int* arr,int n){
    int i, key, j;
    for ( i = 1; i < n; i++ )
    {
        key = arr[i];
        j = i - 1;
        while ( j >= 0 && arr[j] > key )
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }

}

struct B {
    int *arr;
    int i;
    int n;
    int k;
    int l;
};
void *thread(void *args){

    B *b = (B*)args;

    for( int i = 0; i < b->l; i++ ) {
        arr[i] = &b->arr[b->arr2[i]];
    }
    for( int j = 0; j < n / k; j++ ) {
        arr2[j] = i + j * k;
        b->arr = arr;
        b->arr2 = arr2;
        b->n = n;
        b->l = l;
        //std::cout << arr2[j] << " ";
    }
    //i + j * k
    int i, key, j;
    for ( i = 1; i < n / k; i++ )
    {
        key = arr[i][0];
        j = i - 1;
        while ( j >= 0 && arr[j][0] > key )
        {
            arr[j + 1][0] = arr[j][0];
            j = j - 1;
        }
        arr[j + 1][0] = key;
    }
    
    delete b;

}

void func(int *arr,int n){

    //print(arr,n);
    for( int k = n / 2; k > 1; k /= 2 ) {

        pthread_t *th = new pthread_t[k];
        for( int i = 0; i < k; i++ ) {
            //arr2[j] = i + j * k;

            int l = n / k;
            int *arr2 = new int[l];
            B *b =  new B;
            b->arr = arr;
            b->k = k;
            b->i = i;
            b->n = n;
            for( int j = 0; j < n / k; j++ ) {

                //std::cout << arr2[j] << " ";
            }
            pthread_create(&th[i],NULL,thread,(void*)b);
            //std::cout << "" << '\n';
        }
        for( int i = 0; i < num; i++ ) {
            pthread_join(th[i],NULL);
        }
        delete[] th;
    }
    merge_sort(arr,n);
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

void generate(int *arr,int n){
    for( int i = 0; i < n; i++ ) {
        arr[i] = rand() % 10000 - 500;
    }
}
int main() {

    srand (time(NULL) );
    int n = 1000;
    clock_t t1, t2, t3, t4;
    int *arr = new int[n];
    int *arr2 = new int[n];
    generate(arr,n);
    generate(arr2,n);
    ShellsSort sh(arr,n);
    ShellsSort sh2(arr2,n);

    /*for( int i = 0; i < n; i++ ) {
        std::cout << arr[i] << ' ';
       }
       std::cout << '\n';
     */

    //print(arr,n);
    //print(arr2,n);
    t1 = clock();
    shell(arr,n);
    t2 = clock();
    std::cout << "\nTIME without multithreading : " << ( t2 - t1 ) / (double)CLOCKS_PER_SEC << "\n";
    t3 = clock();
    //sh2.sort(func);
    func(arr2,n);
    t4 = clock();
    //print(arr,n);
    //print(arr2,n);
    /*
       std::cout << '\n';
       for( int i = 0; i < n; i++ ) {
        std::cout << arr2[i] << ' ';
       }*/

    std::cout << "\nTIME with multithreading : " << ( t4 - t3 ) / (double)CLOCKS_PER_SEC << "\n";
    return 0;
}
