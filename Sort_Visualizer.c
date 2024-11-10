#include <stdio.h>
#include <unistd.h>

#define MAX_SIZE 100

#define RESET_COLOR "\033[0m"
#define BUBBLE_HIGHLIGHT "\033[1;33m"
#define SELECT_HIGHLIGHT "\033[1;34m"
#define MIN_COLOR "\033[1;31m"
#define INSERT_HIGHLIGHT "\033[1;32m"
#define PIVOT_COLOR "\033[1;35m"
#define MERGE_HIGHLIGHT "\033[1;36m"
#define HEAP_HIGHLIGHT "\033[38;5;214m"

void printArray(int arr[], int size, int highlight1, int highlight2, char* color1, char* color2) {
    for (int i = 0; i < size; i++) {
        if (i == highlight1) {
            printf("%s%d%s ", color1, arr[i], RESET_COLOR);
        } else if (i == highlight2) {
            printf("%s%d%s ", color2, arr[i], RESET_COLOR);
        } else {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

void printmergeArray(int arr[], int size, int left, int right, int highlightIndex) {
    for (int i = left; i <= right; i++) {
        if (i == highlightIndex) {
            printf(MERGE_HIGHLIGHT "%d" RESET_COLOR " ", arr[i]);
        } else {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

void bubbleSort(int arr[], int size) {
    printf("Visualizing Bubble Sort:\n");
    for (int i = 0; i < size - 1; i++) {
        printf("Pass %d:\n", i + 1);
        for (int j = 0; j < size - i - 1; j++) {
            printArray(arr, size, j, j + 1, BUBBLE_HIGHLIGHT, BUBBLE_HIGHLIGHT);
            usleep(1000000);

            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                printArray(arr, size, j, j + 1, BUBBLE_HIGHLIGHT, BUBBLE_HIGHLIGHT);
                usleep(1000000);
            }
        }
        printf("\n");
    }
}

void selectionSort(int arr[], int size) {
    printf("Visualizing Selection Sort:\n");
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        printf("Pass %d:\n", i + 1);

        printArray(arr, size, -1, minIndex, MIN_COLOR, SELECT_HIGHLIGHT);
        usleep(1000000);

        for (int j = i + 1; j < size; j++) {
            printArray(arr, size, j, minIndex, SELECT_HIGHLIGHT, MIN_COLOR);
            usleep(1000000);

            if (arr[j] < arr[minIndex]) {
                minIndex = j;
                printArray(arr, size, j, minIndex, MIN_COLOR, SELECT_HIGHLIGHT);
                usleep(1000000);
            }
        }

        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
            printArray(arr, size, -1, minIndex, MIN_COLOR, SELECT_HIGHLIGHT);
            usleep(1000000);
        }

        printf("Array after Pass %d:\n", i + 1);
        printArray(arr, size, -1, -1, "", "");
        usleep(1000000);
        printf("\n");
    }
}

void insertionSort(int arr[], int size) {
    printf("Visualizing Insertion Sort:\n");
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        printf("Pass %d:\n", i);

        printArray(arr, size, i, -1, INSERT_HIGHLIGHT, "");
        usleep(1000000);

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            printArray(arr, size, j, j + 1, INSERT_HIGHLIGHT, INSERT_HIGHLIGHT);
            usleep(1000000);
            j--;
        }
        arr[j + 1] = key;
        printArray(arr, size, j + 1, -1, INSERT_HIGHLIGHT, "");
        usleep(1000000);
        printf("\n");
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    printf("Pivot: ");
    printArray(arr, high - low + 1, high, -1, PIVOT_COLOR, 0);
    usleep(1000000);

    for (int j = low; j < high; j++) {
        printArray(arr, high - low + 1, j, high, 0, PIVOT_COLOR);
        usleep(1000000);

        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            printArray(arr, high - low + 1, i, j, PIVOT_COLOR, 0);
            usleep(1000000);
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    printArray(arr, high - low + 1, i + 1, high, PIVOT_COLOR, 0);
    usleep(1000000);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        printf("Array after partitioning:\n");
        printArray(arr, high - low + 1, -1, -1, 0, 0);
        usleep(1000000);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    printf("\nMerging:\n");
    printf("Left subarray: ");
    for (int i = 0; i < n1; i++){
        printf("%d ", L[i]);
        usleep(1000000);
    }
    printf("\nRight subarray: ");
    for (int j = 0; j < n2; j++){
        printf("%d ", R[j]);
        usleep(1000000);   
    }
    printf("\n");
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            printmergeArray(arr, right - left + 1, left, right,k);
            usleep(1000000);
            i++;
        } else {
            arr[k] = R[j];
            printmergeArray(arr, right - left + 1, left, right, k);
            usleep(1000000);
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        printmergeArray(arr, right - left + 1, left, right, k);
        usleep(1000000);
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        printmergeArray(arr, right - left + 1, left, right, k);
        usleep(1000000);
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        printf("\n--- Dividing array ---\n");
        printf("Left half: ");
        for (int i = left; i <= mid; i++){
            printf("%d ", arr[i]);
            usleep(1000000);
        }
        printf("\nRight half: ");
        for (int i = mid + 1; i <= right; i++){
            printf("%d ", arr[i]);
            usleep(1000000);
        }
        printf("\n");
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void heapify(int arr[], int size, int root) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < size && arr[left] > arr[largest])
        largest = left;

    if (right < size && arr[right] > arr[largest])
        largest = right;

    if (largest != root) {
        int temp = arr[root];
        arr[root] = arr[largest];
        arr[largest] = temp;

        printArray(arr, size, root, largest, HEAP_HIGHLIGHT, HEAP_HIGHLIGHT);
        usleep(1000000);
        heapify(arr, size, largest);
    }
}

void heapSort(int arr[], int size) {
    printf("Visualizing Heap Sort:\n");

    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(arr, size, i);
    }

    for (int i = size - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        printArray(arr, size, 0, i, HEAP_HIGHLIGHT, HEAP_HIGHLIGHT);
        usleep(1000000);
        heapify(arr, i, 0);
    }
}

void main() {
    int size;
    printf("Enter the number of elements: ");
    scanf("%d", &size);

    int arr[size];
    int choice;
    char continueChoice;

    do {
        printf("Enter %d elements:\n", size);
        for (int i = 0; i < size; i++) {
            scanf("%d", &arr[i]);
        }
        printf("Choose a sorting algorithm to visualize:\n");
        printf("1. Bubble Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Insertion Sort\n");
        printf("4. Quick Sort\n");
        printf("5. Merge Sort\n");
        printf("6. Heap Sort\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        printf("Original array:\n");
        printArray(arr, size, -1, -1, "", "");
        printf("\n");

        switch (choice) {
            case 1:
                bubbleSort(arr, size);
                break;
            case 2:
                selectionSort(arr, size);
                break;
            case 3:
                insertionSort(arr, size);
                break;
            case 4:
                quickSort(arr, 0, size - 1);
                break;
            case 5:
                mergeSort(arr, 0, size - 1);
                break;
            case 6:
                heapSort(arr, size);
                break;
            default:
                printf("Invalid choice!\n");
        }

        printf("Sorted array:\n");
        printArray(arr, size, -1, -1, "", "");
        printf("Do you want to sort the array again? (y/n): ");
        scanf(" %c", &continueChoice);
        if(continueChoice == 'n' || continueChoice == 'N'){
            printf("Sorting complete!\n");
            printf("Sorting visualizer is closing.\n");
            printf("Thank You for using!!\n");

        }
    } while (continueChoice == 'y' || continueChoice == 'Y');
}
