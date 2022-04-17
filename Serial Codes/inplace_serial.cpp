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
void mergeSortAux(ll *a, ll n) {
    ll i=0,j=n/2,k=0,mid=n/2-1;
    
    ll mx=max(a[n/2-1],a[n-1])+1;
    flop++;
    
    ll r=n-1,l=0;
    while(i<=mid && j<=r && k<=r)
    {
        ll element1=a[i]%mx;
        ll element2=a[j]%mx;
        flop+=2;
        if(element1<=element2)
        {
            a[k]+=element1*mx;
            i++;
        }
        else
        {
            a[k]+=element2*mx;
            j++;
        }
        k++;
        flop+=2;
    }

    while(i<=mid)
    {
        ll element=a[i]%mx;
        a[k]+=element*mx;
        i++;
        k++;
        flop+=3;
    }

    while(j<=r)
    {
        ll element=a[j]%mx;
        a[k]+=element*mx;
        j++;
        k++;
        flop+=3;
    }
    
    for(i=l;i<=r;i++)
    {
        a[i]/=mx;
        flop++;
    }
} 
  
void mergeSort(ll *arr, ll n)
{
   if (n < 2) return;
   ll end = n/2;
   flop++;
  // #pragma omp task shared(arr) 
   mergeSort(arr, end);

  // #pragma omp task shared(arr) 
   mergeSort(arr+end, n-end);

  // #pragma omp taskwait
   mergeSortAux(arr, n);
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
    
     if(!arr)
     {
         if(arr)
         free(arr);
     }
    //vector<ll> dummy(200000000);
    //vector<ll> arr(200000000);
    
   // omp_set_nested(1);
    /* for(ll p=2;p<32;p*=2)
     {
         cout<<"Thread: "<<p<<"\n\n";*/
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
          //#pragma omp parallel
          //{
          /*if(omp_get_thread_num()==0)
          cout<<omp_get_num_threads()<<endl;*/
        //    #pragma omp single
              mergeSort(arr, i);
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
    // } 
	free(arr);
	return 0;
}

