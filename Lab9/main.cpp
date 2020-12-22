#include <iostream>
#include <time.h>

using namespace std;

const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds

const int NUMBERS_SIZE = 50000;

int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}

void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

int Partition(int numbers[], int i, int k){
  int l = 0;
  int h = 0;
  int midpoint = 0;
  int pivot = 0;
  int temp = 0;
  bool done = false;
   // Pick middle element as pivot
   midpoint = (i + k) / 2;
   pivot = numbers[midpoint];
   l = i;
   h = k;
   while(!done){
      // Increment l while numbers[l] < pivot
      while (numbers[l] < pivot) {
         ++l;
      }
      // Decrement h while pivot < numbers[h]
      while (pivot < numbers[h]) {
         --h;
      }
      // If there are zero or one elements remaining,
      // all numbers are partitioned. Return h
      if (l >= h){
         done = true;
      }
      else{
        // Swap numbers[l] and numbers[h],
        // update l and h
        temp = numbers[l];
        numbers[l] = numbers[h];
        numbers[h] = temp;
        ++l;
        --h;
      }
   }
   return h;
}

void Quicksort_midpoint(int numbers[], int i, int k){
  int j = 0;
   // Base case: If there are 1 or zero elements to sort,
   // partition is already sorted
   if(i >= k){
      return;
   }
   // Partition the data within the array. Value j returned
   // from partitioning is location of last element in low partition.
   j = Partition(numbers, i, k);
   // Recursively sort low partition (i to j) and
   // high partition (j + 1 to k)
   Quicksort_midpoint(numbers, i, j);
   Quicksort_midpoint(numbers, j + 1, k);
}

void InsertionSort(int numbers[], int numbersSize){
  int j = 0;
  int temp = 0;  // Temporary variable for swap
  for (int i = 1; i < numbersSize; ++i) {
    j = i;
    // Insert numbers[i] into sorted part
    // stopping once numbers[i] in correct position
    while (j > 0 && numbers[j] < numbers[j - 1]){
         // Swap numbers[j] and numbers[j - 1]
         temp = numbers[j];
         numbers[j] = numbers[j - 1];
         numbers[j - 1] = temp;
         --j;
    }
  }
}

int findMedian(int numbers[], int i, int k){
  int arr[3] = {numbers[i], numbers[(i+k)/2], numbers[k]};
  InsertionSort(arr, 3);
  if(arr[1] == numbers[i]){
    return i;
  }
  else if(arr[1] == numbers[(i+k)/2]){
    return (i+k)/2;
  }
  else{
    return k;
  }
}

int medianPartition(int numbers[], int i, int k){
  int l = 0;
  int h = 0;
  int midpoint = 0;
  int pivot = 0;
  int temp = 0;
  bool done = false;
   midpoint = findMedian(numbers, i, k);
   pivot = numbers[midpoint];
   l = i;
   h = k;
   while(!done){
      // Increment l while numbers[l] < pivot
      while (numbers[l] < pivot) {
         ++l;
      }
      // Decrement h while pivot < numbers[h]
      while (pivot < numbers[h]) {
         --h;
      }
      // If there are zero or one elements remaining,
      // all numbers are partitioned. Return h
      if (l >= h){
         done = true;
      }
      else{
        // Swap numbers[l] and numbers[h],
        // update l and h
        temp = numbers[l];
        numbers[l] = numbers[h];
        numbers[h] = temp;
        ++l;
        --h;
      }
   }
   return h;
}

void Quicksort_medianOfThree(int numbers[], int i, int k){
  int j = 0;
   if(i >= k){
      return;
   }
   j = medianPartition(numbers, i, k);
   Quicksort_medianOfThree(numbers, i, j);
   Quicksort_medianOfThree(numbers, j + 1, k);
}

int main() {
/*int arr1[NUMBERS_SIZE];
int arr2[NUMBERS_SIZE];
int arr3[NUMBERS_SIZE];
fillArrays(arr1, arr2, arr3);

clock_t Start = clock();
//call sort function here
InsertionSort(arr1, NUMBERS_SIZE);
clock_t End = clock();
int elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
cout << "InsertionSort time of arr1: " << elapsedTime << endl;*/
int arr[3] = {10, 7, 1};
int midIndex = findMedian(arr, 0, 2);
cout << midIndex;

}
