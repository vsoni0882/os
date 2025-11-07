#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

void printArray(int arr[], int n, const char *msg)
{
    printf("%s: ", msg);
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &arr[i]);

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        sleep(3);
        printf("\n[Child] PID: %d, Parent PID: %d (before sort)\n", getpid(), getppid());

        insertionSort(arr, n);
        printArray(arr, n, "[Child] Sorted using Insertion Sort");

        printf("[Child] Finished.\n");
    }
    else
    {
        wait(NULL);

        printf("\n[Parent] PID: %d, Child PID: %d (before sort)\n", getpid(), pid);
        bubbleSort(arr, n);
        printArray(arr, n, "[Parent] Sorted using Bubble Sort");

        printf("[Parent] Finished.\n");
    }

    return 0;
}
