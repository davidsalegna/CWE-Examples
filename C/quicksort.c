#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to partition the array
int partition(int arr[], int low, int high) {
    // CWE-482: Proper use of comparing vs assigning
    int pivot = arr[high]; 
    // CWE-783: Operator precedence is correctly followed here and throughout the rest of the program,
    // using parentheses to guarantee operations are done in the desired order.
    // CWE-482: Proper use of comparing vs assigning
    int i = (low - 1);   
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            // CWE-787: Modifying an array is done such that there is no real possibility of attempting to
            // write values out of its bounds.
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Function to implement quick sort
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        // CWE-482: Proper use of comparing vs assigning
        int pivot_index = partition(arr, low, high);
        quicksort(arr, low, pivot_index - 1);
        quicksort(arr, pivot_index + 1, high);
    }
}

// Function to print the array
// CWE-231: Accepts extra parameters to be ignored
// CWE-685: Allows for function calling with incorrect parameter amount
void printArray(int arr[], int size, ...) {
    // CWE-232: Ensure that the size value is not undefined
    // CWE-482: Proper use of comparing vs assigning
    if (size == NULL) {
        return;
    }
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    do
    {
        char c;
        int len;
        char num_buffer[4];
        
        scanf("%d", &n);


        // printf("Enter the size of the array: ");
        // fgets(num_buffer, 4, stdin);

        // // Flush stdin
        // if ((len = strlen(num_buffer)) == 3 && num_buffer[3] != '\n' && num_buffer[3] != EOF) {
        //     printf("We flushin");
        //     while ((c = getchar()) != '\n' && c != EOF);
        // }
        // sscanf(num_buffer, "%d", &n);
        // printf("STRING %s", num_buffer);
        // printf("NUM %d", n);

        // CWE-839: The minimum value is checked to protect against any problems that might arise from
        // an invalid array size.
        if (n > 100 || n < 1)
            printf("Size must be a value from 1-100, try again.\n\n");
    } while (n > 100 || n < 1);
    
    // CWE-789: Thanks to the previous block of code, the integer array is ensured to be a reasonable size.
    // CWE-467: sizeof() is not called on a pointer type, but rather a standard value (int)
    // CWE-482: Proper use of comparing vs assigning
    // CWE-131: Proper calculation of buffer size
    int *arr = (int *)malloc(n * sizeof(int)); // Dynamically allocate memory for the array

    printf("Enter the elements of the array: ");
    int num = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", num);
        // CWE-122: Proper check for heap-based overflow
        if(-INT_MAX < num < INT_MAX){
            arr[i] = num;
        //Will simply add filler number 1 if not valid integer for input
        }else{
            arr[i]
        }
    }

    printf("Original array: ");
    // CWE-686: Function is called using correct argument types (int[], int)
    // CWE-683: Function is called with correct order of arguments
    // CWE-688: Function is called with correct references as arguments
    printArray(arr, n);

    quicksort(arr, 0, n - 1);

    printf("Sorted array: ");
    printArray(arr, n);

    // CWE-415: Free is only called once to avoid double free memory leaks
    // CWE-416: Free is called at the end of the program so there's no possibility of it being used afterwards
    // CWE-401: Free memory after effective lifetime
    free(arr); // Free the dynamically allocated memory
    return 0;
}
