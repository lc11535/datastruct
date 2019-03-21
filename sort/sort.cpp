/*
 *  插入排序
 *  - 直接插入排序
 *  - 折半插入排序
 *  - 2-路插入排序
 *  - 表插入排序
 * 
 *  选择排序
 *  - 简单选择排序
 *  - 堆排序
 * 
 *  交换排序
 *  - 冒泡排序
 *  - 快速排序
 *  
 *  归并排序
 *  - 二路归并
 *  - 多路归并
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 100

void RandomArray(int Array[], int size)
{
    srand(time(NULL));

    for(int i=0;i<size;i++){
        Array[i] = (rand() % 100) + 1;
    } 

    return;
}

void PrintArray(int Array[], int size) 
{
    printf("Array: ");
    for(int i=0;i<size;i++){
        printf("%-4d", Array[i]);
    }
    printf("\n");
}

// 直插 （从小到大）
void InsertSort(int Array[], int size)
{
    // 从第二个元素开始，即 Array[1] 开始，往前插入
    for(int i = 1; i < size; i++){

        int elem = Array[i];

        // 凡是比 > elem，都往右移
        int j = i-1;    
        while(Array[j] > elem && j >= 0){
            Array[j+1] = Array[j];
            j--;
        }

        // j+1 就会 elem的位置
        Array[j+1] = elem;
    }
}


// 折半插入 （从小到大）
void BinarySort(int Array[], int size)
{
    // 从第二个元素开始，即 Array[1] 开始，往前折半插入
    for (int i = 2; i < size; i++){
        int elem = Array[i];
        int low = 0;
        int high = i -1;

        while(low <= high) {
            int mid = (low + high) / 2;
            if( Array[mid] > elem ) high = mid - 1;
            else low = mid + 1;
        }

        // high+1 就是应该插入的位置
        for(int j=i-1; j>= high+1; j--){
            Array[j+1] = Array[j];
        }

        Array[high + 1] = elem;
    }
}

// 二路插入 （从小到大）
void TwoWaySort(int Array[], int size)
{
    int tmp[N] = {0};  // head -> tail 依次增大
    int head = 0;
    int tail = 0;
    tmp[0] = Array[0];

    for(int i = 1; i < size; i++){

        // 比 tmp中最大的元素都大，直接放到tail+1位置
        if(Array[i] >= tmp[tail]){
            //printf("\n>=, insert %d, head=%d tail=%d \n", Array[i], head, tail); 
            //PrintArray(tmp,size);

            tail = (tail + 1 + size) % size;
            tmp[tail] = Array[i];

            //PrintArray(tmp,size);
        }

        // 比 tmp中最小的元素都小，直接放到tail+1位置
        else if(Array[i] < tmp[head]){
            //printf("\n<, insert %d, head=%d tail=%d \n", Array[i], head, tail); 
            //PrintArray(tmp,size);

            head = (head - 1 + size) % size;
            tmp[head] = Array[i];

            //PrintArray(tmp,size);
        }

        // 中间位置
        else{
            // 从 tail 开始，往前直插即可
            int j = (tail + 1 + size) % size; // tail + 1 是空的，依次往后移

            while(tmp[ ((j-1) + size) % size ] > Array[i]){
                // j <- j-1
                tmp[j] = tmp[ (j-1 + size) % size ];
                j = (j - 1 + size) % size;
            }

            //printf("\n<>, insert %d, head=%d tail=%d, j=%d\n", Array[i], head, tail, j); 
            //PrintArray(tmp,size);

            // j 就是插入位置
            tmp[j] = Array[i];

            //PrintArray(tmp,size);

            tail = (tail + 1 + size) % size;
        }
    }

    // 将tmp复制到Array
    for(int i = 0; i < size; i++){
        Array[i] = tmp[head];
        head = (head + 1 + size) % size;
    }
}

// 简单选择 （从小到大）
void SelectSort(int Array[], int size)
{
    for(int i = 0; i < size; i++){
        // 选择一个最小值，和 i 交换

        int min = i;
        for(int j = i + 1; j < size; j ++){
            if (Array[j] < Array[min]){
                min = j;
            }
        }

        if(min != i){
            int tmp = Array[i];
            Array[i] = Array[min];
            Array[min] = tmp;
        }
    }
}

// 调整：大顶堆，对顶点v进行调整
void Adjust(int Array[], int size, int v)
{
    if(v < 0) return;

    int indexLeft = 2 * v + 1;  // 左孩子
    int indexRight = 2 * v + 2;  // 右孩子


    // 没有孩子
    if( indexLeft > size-1 ) return;

    // 只有左孩子
    if( indexRight > size-1 ){

        // 比左孩子大，无需调整
        if(Array[v] >= Array[indexLeft] ){
            return;
        }

        // 比左孩子小，交换，继续调整
        int tmp = Array[v];
        Array[v] = Array[indexLeft];
        Array[indexLeft] = tmp;
        Adjust(Array, size, indexLeft);
        return;
    }

    // 有两个孩子

    // 选出两个孩子中较大的
    int child = indexLeft;
    if (Array[indexLeft] < Array[indexRight]){
        child = indexRight;
    }

    // 比左右孩子都大，无需调整
    if( Array[v] > Array[child]){
        return;
    }

    int tmp = Array[v];
    Array[v] = Array[child];
    Array[child] = tmp;
    Adjust(Array, size, child);
    return;
}

// 建堆
void BuildHeap(int Array[], int size)
{
    for(int i = (size / 2) - 1  ; i>=0; i--){
        Adjust(Array, size, i);
    }
}

// 堆排序
void HeapSort(int Array[], int size)
{
    for(int i=size-1; i >= 1; i-- ){
        //printf("i=%3d Array[0]=%d Array[i]=%d \n", i, Array[0], Array[i]);
        //PrintArray(Array,size);

        int tmp = Array[i];
        Array[i] = Array[0];
        Array[0] = tmp;
        //PrintArray(Array,size);

        Adjust(Array, i, 0);
        //PrintArray(Array,size);
    }
}

//冒泡排序
void BubbleSort(int Array[], int size)
{
    // 冒泡 size 趟
    for(int i=1;i < size; i++) {

        for(int j=0; j < size-i; j++) {
            if( Array[j] > Array[j+1] ){
                //swap
                int tmp = Array[j];
                Array[j] = Array[j+1];
                Array[j+1] = tmp;
            }
        }
    }
}

int Partition(int Array[], int low, int high)
{
    int pivot = Array[low];

    while(low < high){

        // 从high 开始找一个比pivot小的，放到 low
        while(Array[high] >= pivot && low < high) high --;
        Array[low] = Array[high];

        // 从low开始，找一个比pivot大的，放到high
        while(Array[low] <= pivot && low < high) low ++;
        Array[high] = Array[low];
    }

    Array[low] = pivot;

    return low;
}

// 快速排序
void QuickSort(int Array[], int low, int high)
{
    if(low < high){
        int pivotLoc = Partition(Array, low, high);
        QuickSort(Array, low, pivotLoc-1);
        QuickSort(Array, pivotLoc+1, high);
    }
}

int main()
{
    int Array[N] = {0};
    int size = 10;
/*
    RandomArray(Array,size);
    PrintArray(Array,size);
    InsertSort(Array,size);
    PrintArray(Array,size);

    printf("-----\n");
    RandomArray(Array,size);
    PrintArray(Array,size);
    BinarySort(Array,size);
    PrintArray(Array,size);

    printf("-----\n");
    RandomArray(Array,size);
    PrintArray(Array,size);
    TwoWaySort(Array,size);
    PrintArray(Array,size);

    printf("-----\n");
    RandomArray(Array,size);
    PrintArray(Array,size);
    SelectSort(Array,size);
    PrintArray(Array,size);

    printf("-----\n");
    RandomArray(Array,size);
    PrintArray(Array,size);
    BuildHeap(Array,size);
    PrintArray(Array,size);
    HeapSort(Array,size);
    PrintArray(Array,size);

    printf("-----\n");
    RandomArray(Array,size);
    PrintArray(Array,size);
    QuickSort(Array,0,size-1);
    PrintArray(Array,size);    
*/
    printf("-----\n");
    RandomArray(Array,size);
    PrintArray(Array,size);
    BubbleSort(Array,size);
    PrintArray(Array,size); 



    return 0;
}
