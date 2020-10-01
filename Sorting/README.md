# Sorting

## 특징
- 수를 Comparator에 따라서 정렬하는 알고리즘
- Sort의 종류
  * Bubble Sort: 붙어있는 element끼리 비교해서 swap, 왼쪽 끝부터 채우기
  ~~~java 
  public static void bubbleSort(int[] a) {
    boolean sorted = false;
    int temp;
    while(!sorted) {
        sorted = true;
        for (int i = 0; i < array.length - 1; i++) {
            if (a[i] > a[i+1]) {//맞는 order가 아닐 시 swap
                temp = a[i];
                a[i] = a[i+1];
                a[i+1] = temp;
                sorted = false;
            }
        }
    }
  }
  ~~~
  * Insertion Sort: index 0 부터 하나씩 배열에 insert하면서 맞는 위치 찾을 때까지 swap
  ~~~java
  public static void insertionSort(int[] array) {
    for (int i = 1; i < array.length; i++) {//한칸 씩 늘리기
        int current = array[i];
        int j = i - 1;
        while(j >= 0 && current < array[j]) {//맞는 위치 찾을때까지 swap
            array[j+1] = array[j];
            j--;
        }
        // at this point we've exited, so j is either -1
        // or it's at the first element where current >= a[j]
        array[j+1] = current;
    }
  }
  ~~~

  * Selection Sort: sort되지 않은 모든 숫자를 서칭하면서 정렬 규칙에 맞는 수를 끝으로 옮기기
  ~~~java 
  public static void selectionSort(int[] array) {
    for (int i = 0; i < array.length; i++) {//하나씩 오른쪽으로 옮겨가면서 sort 안된 것만 지정
        int min = array[i];
        int minId = i;
        for (int j = i+1; j < array.length; j++) {//제일 작은 것 찾기
            if (array[j] < min) {
                min = array[j];
                minId = j;
            }
        }
        // swap 진행
        int temp = array[i];
        array[i] = min;
        array[minId] = temp;
    }
  }
  ~~~
  * Merge Sort: Divide & Conquer 방식, 배열을 반으로 Divide하다가 이를 합치면서 sort 하는 방식
  ~~~java
  public static void mergeSort(int[] array, int left, int right) {
    if (right <= left) return;
    int mid = (left+right)/2;
    //Divide 과정
    mergeSort(array, left, mid);
    mergeSort(array, mid+1, right);
    //Conquer 과정
    merge(array, left, mid, right);
  }

  void merge(int[] array, int left, int mid, int right) {
    // 왼쪽, 오른쪽 길이 계산
    int lengthLeft = mid - left + 1;
    int lengthRight = right - mid;

    // 임시 subArray 생성
    int leftArray[] = new int [lengthLeft];
    int rightArray[] = new int [lengthRight];

    // 임시 복사
    for (int i = 0; i < lengthLeft; i++)
        leftArray[i] = array[left+i];
    for (int i = 0; i < lengthRight; i++)
        rightArray[i] = array[mid+i+1];

    int leftIndex = 0;
    int rightIndex = 0;

    // left와 right array로부터 Conquer 하는 과정
    for (int i = left; i < right + 1; i++) {
        // R, L에 둘다 아직 element가 있으면 비교해서 삽입
        if (leftIndex < lengthLeft && rightIndex < lengthRight) {
            if (leftArray[leftIndex] < rightArray[rightIndex]) {
                array[i] = leftArray[leftIndex];
                leftIndex++;
            }
            else {
                array[i] = rightArray[rightIndex];
                rightIndex++;
            }
        }
        // 오른쪽 모두 사용 시 왼쪽 것을 모두 삽입
        else if (leftIndex < lengthLeft) {
            array[i] = leftArray[leftIndex];
            leftIndex++;
        }
        // 왼쪽 모두 사용 시 오른쪽 것을 모두 삽입
        else if (rightIndex < lengthRight) {
            array[i] = rightArray[rightIndex];
            rightIndex++;
        }
    }
  }
  ~~~
  * Heapsort: Heap를 사용해 수를 꺼내면서 수를 정렬
    - Heap(https://github.com/Factoriall/Algorithm-Java/tree/master/Heap) 참조
  * Quicksort: 특정한 pivot를 지정, pivot 기준으로 정렬 규칙에 따라 왼쪽, 오른쪽으로 나눠서 Divide & Conquer 진행
  ~~~java
  static int partition(int[] array, int begin, int end) {
    int pivot = end;//pivot를 가장 끝으로 잡음

    //end를 기준으로 왼쪽, 오른쪽으로 나누기
    int counter = begin;
    for (int i = begin; i < end; i++) {
        if (array[i] < array[pivot]) {
            int temp = array[counter];
            array[counter] = array[i];
            array[i] = temp;
            counter++;
        }
    }

    //pivot과 counter의 위치 교환
    int temp = array[pivot];
    array[pivot] = array[counter];
    array[counter] = temp;

    return counter;//counter가 실제 pivot
  }

  public static void quickSort(int[] array, int begin, int end) {
    if (end <= begin) return;//종료 조건
    int pivot = partition(array, begin, end);//pivot 위치 찾기

    //pivot 위치 기준 Divide
    quickSort(array, begin, pivot-1);
    quickSort(array, pivot+1, end);
  }
  ~~~

  * Counting Sort: 실제 하나의 숫자가 몇 개가 있는지 세서 정렬하는 방법, 속도는 매우 빠르나 메모리를 상당히 잡아먹는 단점이 존재

  * Radix Sort: 자리수에 따라 소팅하는 방법, 작은 자릿수부터 시작하는 LSD 방법과 큰 자릿수부터 시작하는 MSD 방법 존재, counting sort처럼 빠르나 메모리를 크게 잡아 먹을 수 있음

- 출처: https://stackabuse.com/sorting-algorithms-in-java/

## 라이브러리 제외 코드
- 실제 sort 라이브러리 내에서는 Dual-Pivot Quicksort을 사용
~~~java
// pivot을 2개로 설정한 quicksort
class GFG{ 
    static void swap(int[] arr, int i, int j) { 
        int temp = arr[i]; 
        arr[i] = arr[j]; 
        arr[j] = temp; 
    } 
    
    static void dualPivotQuickSort(int[] arr,  int low, int high) { 
    if (low < high) { 
            // piv[] stores left pivot and right pivot. 
            // piv[0] means left pivot and 
            // piv[1] means right pivot 
            int[] piv; 
            piv = partition(arr, low, high); 
            
            //3개로 나눠서 divide & conquer
            dualPivotQuickSort(arr, low, piv[0] - 1); 
            dualPivotQuickSort(arr, piv[0] + 1, piv[1] - 1); 
            dualPivotQuickSort(arr, piv[1] + 1, high); 
        }
    } 
    
    static int[] partition(int[] arr, int low, int high) { 
        if (arr[low] > arr[high]) //arr[low]보다 arr[high]가 항상 크게
            swap(arr, low, high); 
            
        int j = low + 1; 
        int g = high - 1, k = low + 1, //pivot의 index
            p = arr[low], q = arr[high]; //p,q는 각각 pivot1, pivot2
            
        while (k <= g)  
        { 
            
            // If elements are less than the left pivot 
            if (arr[k] < p) //j 기준으로 왼쪽으로 모두 작은 수가 들어가게 조정
            { 
                swap(arr, k, j); 
                j++; 
            } 
            
            // If elements are greater than or equal 
            // to the right pivot 
            else if (arr[k] >= q)  //g 기준으로 오른쪽 모두 큰 수가 들어가게 조정
            { 
                while (arr[g] > q && k < g) 
                    g--; 
                    
                swap(arr, k, g); 
                g--; 
                
                if (arr[k] < p) 
                { 
                    swap(arr, k, j); 
                    j++; 
                } 
            } 
            k++; 
        } 
        j--; 
        g++; 
        
        // Bring pivots to their appropriate positions. 
        swap(arr, low, j); 
        swap(arr, high, g); 
    
        // Returning the indices of the pivots 
        // because we cannot return two elements 
        // from a function, we do that using an array. 
        //j,g의 실제 위치가 2개의 pivot
        return new int[] { j, g }; 
    } 
} 
~~~
- 정렬 방법의 시간 복잡도
![sorting_complexity.png](https://blog.kakaocdn.net/dn/wzHnE/btqzxCLyeuw/lBUZ7JI7cIasI7GLkpl9Yk/img.png)

- 출처: https://www.geeksforgeeks.org/dual-pivot-quicksort/

## 사용 사례
- 오름차순, 내림차순 정렬이 필요할 때 사용
- input dataset의 크기가 작거나, 이미 정렬된 것에서 추가가 될 경우 insertion sort가 가장 효율적
- sorting하는 숫자의 범위가 작을 시 Radix 또는 Counting Sort 사용
- 그 외의 대부분의 sort는 QuickSort 또는 Merge Sort. Merge Sort는 공간복잡도 부담이 될 수 있어 Quicksort가 대부분 우위를 보인다. 

## 정의 방법
- import java.util.Arrays 및 import java.util.Collections로 소팅 라이브러리 import
- primitive일 경우 Arrays.sort(E[])로 오름차순 소팅
- primitive가 아닐 시 Arrays.sort(E[], Collections.reverseOrder()); 로 내림차순 소팅 가능
- ArrayList일 경우 Collections.sort(arrayList)로 오름차순 소팅
- 내림차순, 오름차순 외 소팅을 하고 싶을 시 sort 내의 Comparator 재정의를 통해 정렬 규칙을 지정할 수 있다.
Ex)
~~~java
    Arrays.sort(nums, new Comparator<Integer>(){
        @Override
        public int compare(Integer n1, Integer n2){
            String s1 = Integer.toString(n1);
            String s2 = Integer.toString(n2);
                
            int sum1 = Integer.parseInt(s1 + s2);
            int sum2 = Integer.parseInt(s2 + s1);
                
            return sum2 - sum1;
        }
    });

~~~

## 문제 사이트 및 코드
- Sort 파트: https://programmers.co.kr/learn/challenges?selected_part_id=12198
