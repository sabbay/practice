#include "bin_search.h"
#include <stdio.h>

int bin_search(int target, int data[], int size){
  int left_index = 0;
  int right_index = size;
  int middle_index = ( left_index + right_index ) / 2;

  while(data[middle_index] != target){

    if(left_index == right_index){
      return -1;
    }

    else if(data[middle_index] < target){
      left_index = middle_index + 1;
      middle_index = ( left_index + right_index ) / 2;
    }else{
      right_index = middle_index - 1;
      middle_index = ( left_index + right_index ) / 2;
    }
  }
  return middle_index;
}


int bin_search_recu(int target, int data[], int left_index, int right_index) {
  if(left_index > right_index){
    return -1;
  }

  int middle_index = ( left_index + right_index ) / 2;
  if(data[middle_index] > target){
    return bin_search_recu(target, data, left_index, middle_index -1);
  }else if(data[middle_index] < target){
    return bin_search_recu(target, data, middle_index +1, right_index);
  }else{
    return middle_index;
  }
}















