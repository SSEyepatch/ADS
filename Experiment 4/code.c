#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int get_max(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx) mx = arr[i];
    return mx;
}

void count_sort(int arr[], int n, int exp) {
    int *out = (int*)malloc(n * sizeof(int));
    int count[10] = {0};

    for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        out[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++) arr[i] = out[i];
    free(out);
}

void radix_sort(int arr[], int n) {
    int m = get_max(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        count_sort(arr, n, exp);
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n, choice;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n], arr_copy[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        arr_copy[i] = arr[i];
    }

    printf("\n1. Insertion Sort\n2. Radix Sort\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        insertion_sort(arr, n);
        printf("Sorted array (Insertion Sort): ");
        print_array(arr, n);
    } else if (choice == 2) {
        radix_sort(arr_copy, n);
        printf("Sorted array (Radix Sort): ");
        print_array(arr_copy, n);
    } else {
        printf("Invalid choice\n");
    }
    return 0;
}
