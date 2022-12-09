#include<stdio.h>
#include<math.h>
void bubbleSort(int arr[],int);
void printArray(int arr[],int);
int main(){
    int arr[]={23,4,5,12,7};
    int n=sizeof(arr)/sizeof(arr[0]);
    bubbleSort(arr,n);
    printArray(arr,n);
    return 0;
}
void bubbleSort(int arr[],int n){
    int i,j,temp;
    for(i=0;i<n;++i){
        for(j=i+1;j<n;++j){
            if(arr[j]<arr[i]){
                temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
}
void printArray(int arr[],int n){
    int i;
    for(i=0;i<n;++i){
        printf("%d ",arr[i]);
    }
    printf("\n");
}