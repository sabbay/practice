
#include"merge.h"
#include <stdlib.h>
#include <stdio.h>



int min_val(int a, int b){
  if(a>b){
    return b;
  }else return a;
}


void bottom_up_merge(int *a, int size){
  int * tmp = calloc(size, sizeof(int));
  for( int s = 1; s < size; s+=s){
    for(int lo = 0; lo < size - s; lo+=s+s){
      __merge(a, tmp, lo, lo+s-1, min_val(lo+s+s-1, size-1));
    }
  }
}

void print_array(int *a, int size){
  for(int i = 0 ; i  < size ; i++){
    printf("%d ", a[i]);
  }
  printf("\n");
}

void merge_sort(int *a, int size){
  int * tmp = calloc(size, sizeof(int));
  __sort(a, tmp, 0, size -1);
}


void __sort(int *a, int *tmp, int lo , int hi){
  if(hi <= lo) return;
  int mid = lo + (hi - lo )/ 2;
  __sort(a, tmp, lo, mid);
  __sort(a, tmp, mid+1, hi);
  __merge(a, tmp, lo, mid, hi);
}




void __merge(int *a, int *tmp, int lo, int mid, int hi){
  for(int k = lo; k <= hi; k++){
    tmp[k] = a[k];
  }

  int i = lo, j = mid+1;
  for(int k = lo; k <= hi; k++){
    if( i > mid)             a[k] = tmp[j++];
    else if( j > hi )        a[k] = tmp[i++];
    else if( tmp[j] < tmp[i] )        a[k] = tmp[j++];
    else         a[k] = tmp[i++];
  }
}
