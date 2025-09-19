#include <stdio.h>

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

// i. Bubble Sort Ascending
int bubble_sort(int arr[], int n) {
    int comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
            }
        }
    }
    return comparisons;
}

// ii. Selection Sort Descending
void selection_sort_desc(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] > arr[max_idx]) max_idx = j;
        }
        if (max_idx != i) {
            int t = arr[i]; arr[i] = arr[max_idx]; arr[max_idx] = t;
        }
    }
}

// iv. Selection Sort Ascending with step diagram
void selection_sort_asc_steps(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) min_idx = j;
        }
        if (min_idx != i) {
            int t = arr[i]; arr[i] = arr[min_idx]; arr[min_idx] = t;
        }
        printf("Iteration %d: ", i + 1);
        print_array(arr, n);
    }
}

int main() {
    int choice;
    printf("1. Bubble Sort Ascending\n");
    printf("2. Selection Sort Descending\n");
    printf("3. Bubble Sort Comparisons (100,200,300,400,500)\n");
    printf("4. Selection Sort Ascending (step diagram)\n");
    printf("Choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int arr[] = {64, 34, 25, 12, 22, 11, 90};
        int n = sizeof(arr) / sizeof(arr[0]);
        printf("Original: "); print_array(arr, n);
        bubble_sort(arr, n);
        printf("Sorted (Bubble Ascending): ");
        print_array(arr, n);
    }
    else if (choice == 2) {
        int arr[] = {64, 34, 25, 12, 22, 11, 90};
        int n = sizeof(arr) / sizeof(arr[0]);
        printf("Original: "); print_array(arr, n);
        selection_sort_desc(arr, n);
        printf("Sorted (Selection Descending): ");
        print_array(arr, n);
    }
    else if (choice == 3) {
        int arr[] = {100, 200, 300, 400, 500};
        int n = 5;
        int comps = bubble_sort(arr, n);
        printf("Bubble Sort comparisons required: %d\n", comps);
    }
    else if (choice == 4) {
        int arr[] = {500, -20, 30, 14, 50};
        int n = 5;
        printf("Original: "); print_array(arr, n);
        selection_sort_asc_steps(arr, n);
        printf("Final Sorted (Selection Ascending): ");
        print_array(arr, n);
    }
    else {
        printf("Invalid choice.\n");
    }
    return 0;
}
