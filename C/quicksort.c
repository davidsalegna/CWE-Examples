#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int n;

// Function to swap two elements
// CWE-374: Checks that the pointers are valid and within the array bounds.
void swap(int *a, int *b, int low, int high) {
    //CWE-129: Proper validation of recieved indexes
    if(100 < low || low < 0 || 100 < high || high < 0){
        //handle error
        return;
    }
    // CWE-476: Checks for null pointers to ensure that it does not attempt to dereference a null pointer.
    if (a == NULL || b == NULL || *a < low || *a > high || *b < low || *b > high) {
        // Handle the error (e.g. return an error code, terminate the program, etc.)
        return;
    }
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to partition the array
int partition(int arr[], int low, int high) {
    //CWE-129: Proper validation of recieved indexes
    if(100 < low || low < 0 || 100 < high || high < 0){
        //handle error
        return 0;
    }
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
            swap(&arr[i], &arr[j], low, high);
        }
    }
    swap(&arr[i + 1], &arr[high], low, high);
    return (i + 1);
}

// Function to implement quick sort
void quicksort(int arr[], int low, int high) {
    //CWE-129: Proper validation of recieved indexes
    if(100 < low || low < 0 || 100 < high || high < 0){
        //handle error
        return;
    }
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
    if (size == 0) {
        return;
    }
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    char c;
    int len;
    char num_buffer[4];
    // CWE-242: No use of inherently dangerous function
    do
    {
        // CWE-170: Set the memory to automatically be null-terminated
        memset(num_buffer, 0, sizeof(num_buffer));
        

        printf("Enter the size of the array: ");
        // CWE-469, CWE-805: As integer 'n' is used to keep track of the size of the array,
        // calculations are not needed to accurately determine or verify the size of the array.
        // CWE-170: This function ensures null-termination
        // CWE-242: Does not use unsafe gets or potentially dangerous scanf
        fgets(num_buffer, 4, stdin);

        // Flush stdin
        if ((len = strlen(num_buffer)) == 4 && num_buffer[3] != '\n' && num_buffer[3] != EOF) {
            while ((c = getchar()) != '\n' && c != EOF);
        }
        // CWE-1287: Although this method of input validation is involved, this final scanf 
        // makes sure that we are provided an integer
        // Convert to integer
        sscanf(num_buffer, "%d", &n);

        // CWE-839: The minimum value is checked to protect against any problems that might arise from
        // an invalid array size.
        // CWE-1284: The quantity of input is validated to keep the program reasonable to use, to ensure
        // there is enough space, and so that it is safe from exploitation
        if (n > 100 || n < 1)
            printf("Size must be a value from 1-100, try again.\n\n");
    } while (n > 100 || n < 1);
    
    // CWE-789: Thanks to the previous block of code, the integer array is ensured to be a reasonable size.
    // CWE-467: sizeof() is not called on a pointer type, but rather a standard value (int)
    // CWE-482: Proper use of comparing vs assigning
    // CWE-131: Proper calculation of buffer size
    // CWE-244: Malloc() is used to allocate memory, instead of realloc() on a previous buffer
    // which could compromise data stored in it.
    int *arr = (int *)malloc(n * sizeof(int)); // Dynamically allocate memory for the array

    printf("Enter the elements of the array:\n");
    int num = 0;
    // CWE-128: Because the bounds are restricted, wraparound error cannot occur
    for (int i = 0; i < n; i++) {
        printf("[%d]: ", i);
        
        scanf("%d", &num);
        // CWE-122: Proper check for heap-based overflow
        if(INT_MIN <= num && num <= INT_MAX) {
            arr[i] = num;
        // Will simply add filler number 1 if not valid integer for input
        } else {
            arr[i] = 1;
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
