#ifndef MERGE_H
#define MERGE_H

int min_val(int a, int b);
void __merge(int *a, int *tmp, int lo, int mid, int hi);
void merge_sort(int *a, int size);
void __sort(int *a, int *tmp, int lo , int hi);
void bottom_up_merge(int *a, int size);
void print_array(int *a, int size);

#endif /* MERGE_H */
