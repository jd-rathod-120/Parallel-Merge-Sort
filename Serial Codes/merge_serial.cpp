#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <stdio.h>
#include <omp.h>

using namespace std;
#define ll long long
#define TASK_SIZE 100
ll flop;
//merge sort function 
void mergeSortAux(ll *arr, ll n, ll *dummy) {
   ll i = 0;
   ll j = n/2;
   ll ti = 0;

   while (i<n/2 && j<n) {
      if (arr[i] < arr[j]) {
         dummy[ti] = arr[i];
         ti++; i++;
      } else {
         dummy[ti] = arr[j];
         ti++; j++;
      }
   }
   while (i<n/2) { /* finish up lower half */
      dummy[ti] = arr[i];
      ti++; i++;
   }
   while (j<n) { /* finish up upper half */
      dummy[ti] = arr[j];
      ti++; j++;
   }
   //memcpy(arr, dummy, n*sizeof(ll));
   for(ll q=0;q<n;q++)
   arr[q]=dummy[q];
} 
  
void mergeSort(ll *arr, ll n, ll *dummy)
{
   if (n < 2) return;
   int end = n/2;
   flop++;
   //#pragma omp task shared(arr) if(n>TASK_SIZE)
   mergeSort(arr, end, dummy);

   //#pragma omp task shared(arr) if(n>TASK_SIZE)
   mergeSort(arr+end, n-end, dummy + end);

   //#pragma omp taskwait
   mergeSortAux(arr, n, dummy);
}

int main()
{
   /* #ifndef ONLINE_JUDGE
    //freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif*/
	//clock_t start,end;
    double walltime;
    ll *arr;
     arr = (long long*) malloc((536870914)*sizeof(long long));
     long long* dummy = (long long*) malloc((536870914)*sizeof(long long));
     if(!dummy || !arr)
     {
         if(dummy)
         free(dummy);
         if(arr)
         free(arr);
     }
    //vector<ll> dummy(200000000);
    //vector<ll> arr(200000000);
    
   // omp_set_nested(1);
    // for(ll p=2;p<32;p*=2)
     //{
       //  cout<<"Thread: "<<p<<"\n\n";
       for(ll i=2;i<=536870912;i*=2)
      {
          flop=0;
          for(ll j=0;j<i;j++)
          {
              arr[j]=rand();
              //cout<<arr[j]<<" ";
              //cout<<a[j]<<endl;
          }
          //omp_set_num_threads(p);
         double start=omp_get_wtime();
        // #pragma omp parallel
          //{
          /*if(omp_get_thread_num()==0)
          cout<<omp_get_num_threads()<<endl;*/
            //#pragma omp single
              mergeSort(arr, i, dummy);
          //}
          double end=omp_get_wtime();
         walltime = (end - start);

          double throughput = (8.0 * flop)/walltime;
          double memory= (8.0 * i)/walltime;
          printf("%ld, %f, %f, %f\n",i,walltime,throughput,memory);
        //cout<<i<<endl;
          for(ll qq=0;qq<i-1;qq++)
          {
            if(arr[qq]<=arr[qq+1])
            {
              //cout<<arr[qq]<<" ";
              //break;
            }
            else 
            {
                cout<<"no\n";
                break;
            }
          }
          //cout<<"\n\n\n";
         // delete[] arr;
      }
     //} 
	free(arr);
    free(dummy);
	return 0;
}

