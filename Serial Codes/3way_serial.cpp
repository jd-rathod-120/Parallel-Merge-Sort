 #include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <stdio.h>
#include <omp.h>

using namespace std;
#define ll long long
#define TASK_SIZE 100  //not required
ll flop;
//merge sort function 
void mergeSortAux(ll *arr, ll n, ll *dummy) {
   ll i = 0;
   ll j1 = n/3;
   ll j2 = 2*n/3;
   ll ti = 0;
   ll l=0,r=n-1;
   
   while (i<n/3 && j1<(2*n/3) && j2<n) {
      if (arr[i] <= arr[j1] && arr[i] <= arr[j2]) {
         dummy[ti] = arr[i];
         ti++; i++;
      } else if (arr[j1] <= arr[i] && arr[j1] <= arr[j2]) {
         dummy[ti] = arr[j1];
         ti++; j1++;
      } else {
         dummy[ti] = arr[j2];
         ti++; j2++;
      }
   }
   
   while (i<(n/3) && j1<(2*n/3)) {
      if (arr[i] <= arr[j1]) {
         dummy[ti] = arr[i];
         ti++; i++;
      }
      else {
         dummy[ti] = arr[j1];
         ti++; j1++;
      }         
   }
   
   while (i<(n/3) && j2<n) {
      if (arr[i] <= arr[j2]) {
         dummy[ti] = arr[i];
         ti++; i++;
      }
      else {
         dummy[ti] = arr[j2];
         ti++; j2++;
      }         
   }
   
   while (j1<(2*n/3) && j2<n) {
      if (arr[j1] <= arr[j2]) {
         dummy[ti] = arr[j1];
         ti++; j1++;
      }
      else {
         dummy[ti] = arr[j2];
         ti++; j2++;
      }         
   }
   
   while (i<n/3) { /* finish up lower half */
      dummy[ti] = arr[i];
      ti++; i++;
   }
   
   while (j1<(2*n/3)) { /* finish up upper half */
      dummy[ti] = arr[j1];
      ti++; j1++;
   }
   
   while (j2<n) { /* finish up upper half */
      dummy[ti] = arr[j2];
      ti++; j2++;
   }
   
   for(i=l;i<=r;i++)
    {
        a[i]/=mx;
        flop++;
    }
} 
  
void mergeSort(ll *arr, ll n, ll *dummy)
{
   if (n < 2) return;
   int end1 = n/3;
   int end2 = 2*n/3;
   flop+=2;
 //  #pragma omp task shared(arr) if(n>TASK_SIZE)
   mergeSort(arr, end1, dummy);

   //#pragma omp task shared(arr) if(n>TASK_SIZE)
   mergeSort(arr+end1, end2-end1, dummy+end1);
   
   //#pragma omp task shared(arr) if(n>TASK_SIZE)
   mergeSort(arr+end2, n-end2, dummy+end2);

 //  #pragma omp taskwait
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
   /*  for(ll p=2;p<32;p*=2)
     {
         cout<<"Thread: "<<p<<"\n\n";*/
       for(ll i=2;i<=536870914;i*=2)
      {
          flop=0;
          for(ll j=0;j<i;j++)
          {
              arr[j]=rand();
              //cout<<arr[j]<<" ";
              //cout<<a[j]<<endl;
          }
       //   omp_set_num_threads(p);
         double start=omp_get_wtime();
         // #pragma omp parallel
          //{
          /*if(omp_get_thread_num()==0)
          cout<<omp_get_num_threads()<<endl;*/
         //   #pragma omp single
              mergeSort(arr, i, dummy);
        //  }
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
    // } 
	free(arr);
    free(dummy);
	return 0;
}