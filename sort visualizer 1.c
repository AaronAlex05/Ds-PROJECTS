#include <stdio.h>
#include <unistd.h> // For sleep and usleep functions

#define MAX_SIZE 100 // Define a maximum size for the array

// ANSI color codes for highlighting
#define RESET_COLOR "\033[0m" // Reset to default color
#define BUBBLE_HIGHLIGHT "\033[1;33m" // Bright yellow for bubble sort
#define SELECT_HIGHLIGHT "\033[1;34m" // Bright blue for current element in selection sort
#define MIN_COLOR "\033[1;31m" // Bright red for the current minimum in selection sort
#define INSERT_HIGHLIGHT "\033[1;32m" // Bright green for insertion sort
#define PIVOT_COLOR "\033[1;35m" // Magenta for the pivot in quick sort
#define MERGE_HIGHLIGHT "\033[1;36m" // Cyan for merging in merge sort
#define HEAP_HIGHLIGHT "\033[38;5;214m" // Bright orange for heap sort

// Function to print the array with optional highlighting
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

// Function to print the array of merge sort with optional highlighting
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

// Bubble Sort Visualization
void bubbleSort(int arr[], int size) {
    printf("Visualizing Bubble Sort:\n");
    for (int i = 0; i < size - 1; i++) {
        printf("Pass %d:\n", i + 1);
        for (int j = 0; j < size - i - 1; j++) {
            printArray(arr, size, j, j + 1, BUBBLE_HIGHLIGHT, BUBBLE_HIGHLIGHT);
            usleep(1000000); // Pause to simulate slow comparison

            if (arr[j] > arr[j + 1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                // Show array state after swap
                printArray(arr, size, j, j + 1, BUBBLE_HIGHLIGHT, BUBBLE_HIGHLIGHT);
                usleep(1000000); // Pause to simulate slow swap
            }
        }
        printf("\n");
    }
}

// Selection Sort Visualization
void selectionSort(int arr[], int size) {
    printf("Visualizing Selection Sort:\n");
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        printf("Pass %d:\n", i + 1);

        // Initial array with the current minimum highlighted
        printArray(arr, size, -1, minIndex, MIN_COLOR, SELECT_HIGHLIGHT);
        usleep(1000000); // Pause to show initial state

        for (int j = i + 1; j < size; j++) {
            printArray(arr, size, j, minIndex, SELECT_HIGHLIGHT, MIN_COLOR);
            usleep(1000000); // Pause to simulate slow comparison

            if (arr[j] < arr[minIndex]) {
                minIndex = j;
                // Highlight the new minimum
                printArray(arr, size, j, minIndex, MIN_COLOR, SELECT_HIGHLIGHT);
                usleep(1000000); // Pause to show new minimum
            }
        }

        // Swap the found minimum element with the first element
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
            // Show array state after swap
            printArray(arr, size, -1, minIndex, MIN_COLOR, SELECT_HIGHLIGHT);
            usleep(1000000); // Pause to simulate slow swap
        }

        // Print the state of the array after each pass
        printf("Array after Pass %d:\n", i + 1);
        printArray(arr, size, -1, -1, "", "");
        usleep(1000000); // Pause to show the state after the pass
        printf("\n");
    }
}

// Insertion Sort Visualization
void insertionSort(int arr[], int size) {
    printf("Visualizing Insertion Sort:\n");
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        printf("Pass %d:\n", i);

        // Highlight the key to be inserted
        printArray(arr, size, i, -1, INSERT_HIGHLIGHT, "");
        usleep(1000000); // Pause to show the key being inserted

        // Move elements of arr[0..i-1] that are greater than key
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            printArray(arr, size, j, j + 1, INSERT_HIGHLIGHT, INSERT_HIGHLIGHT);
            usleep(1000000); // Pause to simulate element shifting
            j--;
        }
        arr[j + 1] = key;
        // Show array state after insertion
        printArray(arr, size, j + 1, -1, INSERT_HIGHLIGHT, "");
        usleep(1000000); // Pause to simulate slow insertion
        printf("\n");
    }
}

// Quick Sort Helper: Partition Function
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choosing the last element as pivot
    int i = low - 1;

    printf("Pivot: ");
    printArray(arr, high - low + 1, high, -1, PIVOT_COLOR, 0);
    usleep(1000000); // Pause to show the pivot

    for (int j = low; j < high; j++) {
        printArray(arr, high - low + 1, j, high, 0, PIVOT_COLOR);
        usleep(1000000); // Pause to simulate comparison

        if (arr[j] < pivot) {
            i++;
            // Swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            // Show array state after swap
            printArray(arr, high - low + 1, i, j, PIVOT_COLOR, 0);
            usleep(1000000); // Pause to show swap
        }
    }
    // Swap arr[i + 1] and arr[high] (the pivot)
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    // Show array state after placing the pivot in the correct position
    printArray(arr, high - low + 1, i + 1, high, PIVOT_COLOR, 0);
    usleep(1000000); // Pause to show pivot placement
    return i + 1;
}

// Quick Sort Visualization (Recursive)
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        printf("Array after partitioning:\n");
        printArray(arr, high - low + 1, -1, -1, 0, 0);
        usleep(1000000); // Pause to show array after partition

        // Recursively sort elements before partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge Sort Helper: Merge Function
void merge(int arr[], int left, int mid, int right) {
    // Calculate sizes of two subarrays to be merged
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Print initial merge information
    printf("\nMerging:\n");
    printf("Left subarray: ");
    for (int i = 0; i < n1; i++){
        printf("%d ", L[i]);
        usleep(1000000); // Pause to simulate slow comparison
    }
    printf("\nRight subarray: ");
    for (int j = 0; j < n2; j++){
        printf("%d ", R[j]);
        usleep(1000000); // Pause to simulate slow comparison    
    }
    printf("\n");

    // Initial indexes of first and second subarrays
    int i = 0, j = 0, k = left;

    // Merge the temporary arrays back into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            printmergeArray(arr, right - left + 1, left, right,k);
            usleep(1000000); // Pause to simulate slow comparison
            i++;
        } else {
            arr[k] = R[j];
            printmergeArray(arr, right - left + 1, left, right, k);
            usleep(1000000); // Pause to simulate slow comparison
            j++;
        }
        k++;
    }

    // Copy remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        printmergeArray(arr, right - left + 1, left, right, k);
        usleep(1000000); // Pause to simulate slow comparison
        i++;
        k++;
    }

    // Copy remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        printmergeArray(arr, right - left + 1, left, right, k);
        usleep(1000000); // Pause to simulate slow comparison
        j++;
        k++;
    }
}

// Merge Sort Visualization
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2;

        printf("\n--- Dividing array ---\n");
        printf("Left half: ");
        for (int i = left; i <= mid; i++){
            printf("%d ", arr[i]);
            usleep(1000000); // Pause to simulate slow comparison
        }
        printf("\nRight half: ");
        for (int i = mid + 1; i <= right; i++){
            printf("%d ", arr[i]);
            usleep(1000000); // Pause to simulate slow comparison
        }
        printf("\n");

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Heap Sort Helper: Heapify Function
void heapify(int arr[], int size, int root) {
    int largest = root; // Initialize largest as root
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    // Check if left child exists and is greater than root
    if (left < size && arr[left] > arr[largest])
        largest = left;

    // Check if right child exists and is greater than largest
    if (right < size && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != root) {
        // Swap root and largest
        int temp = arr[root];
        arr[root] = arr[largest];
        arr[largest] = temp;

        // Show array state after swap
        printArray(arr, size, root, largest, HEAP_HIGHLIGHT, HEAP_HIGHLIGHT);
        usleep(1000000); // Pause to show heapifying

        // Recursively heapify the affected sub-tree
        heapify(arr, size, largest);
    }
}

// Heap Sort Visualization
void heapSort(int arr[], int size) {
    printf("Visualizing Heap Sort:\n");

    // Build heap (rearrange array)
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(arr, size, i);
    }

    // One by one extract elements from heap
    for (int i = size - 1; i > 0; i--) {
        // Move current root to end
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Show array state after swap
        printArray(arr, size, 0, i, HEAP_HIGHLIGHT, HEAP_HIGHLIGHT);
        usleep(1000000); // Pause to show swap

        // Call heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// Main Function
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
        
        // Ask the user if they want to sort the array again
        printf("Do you want to sort the array again? (y/n): ");
        scanf(" %c", &continueChoice);
        if(continueChoice == 'n' || continueChoice == 'N'){
            printf("Sorting complete!\n");
            printf("Sorting visualizer is closing.\n");
            printf("Thank You for using!!\n");

        }
    } while (continueChoice == 'y' || continueChoice == 'Y');
}