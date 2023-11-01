
/*
How to pass an array using call by value in C ? Assuming array is declared locally that is inside main() 
*/

#include<stdio.h>
/* here array is called by value
calling by value do not make changes in original values 
this function will perform a linear search in a given array*/ 
int linear_search(int arr[], int element, int size) 
{
    for( int i=0; i<size; i++)
    {
        if(arr[i]==element)
        return i;
    }
    return 0;
}

/* here array is called by Reference
calling by Reference make changes in the original values 
Below function will replace a given element with a new element*/ 
void Replace_array_element(int *arr, int element, int size, int new_ele)
{
    for( int i=0; i<size; i++)
    {
        if(arr[i]==element)
        arr[i]=new_ele;
    }
    
}

int main(){
    int arr[]={1,2,3,4,5,6,7,8,9,10,11,12};
    
    /* calculating size of array sizeof(arr) gives total size of array here it is 2*12 and sizeof(arr[0]) give size of 1 cell 
    here datatype is INT so 2*/
    int size = (sizeof(arr)/sizeof(arr[0])); 
    
    printf("element found at: %d \n\n\n",linear_search(arr,7,size)); // call by value
    
    Replace_array_element(arr, 10, size, 90); // call by reference
    printf("array:\n");
    for( int i=0; i<size;i++){  printf("%d \n",arr[i]);    } // print Array on console
    return 0;
}