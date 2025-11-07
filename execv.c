#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void bubbleSort(int arr[], int n)
{
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
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

int main()
{
  int n;
  printf("Enter Size of Arr : ");
  scanf("%d", &n);

  int arr[n];
  printf("Enter Elements : ");
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &arr[i]);
  }

  bubbleSort(arr, n);

  pid_t pid = fork();

  if (pid < 0)
  {
    perror("Fork failed");
    return 1;
  }
  else if (pid == 0)
  {
    char *args[n + 2];
    args[0] = "./helper";
    args[n + 1] = NULL;

    for (int i = 0; i < n; i++)
    {
      args[i + 1] = malloc(10);
      sprintf(args[i + 1], "%d", arr[i]);
    }

    execv("./helper", args);
    perror("execv failed");
    exit(1);
  }
  else
  {
    wait(NULL);
    printf("Parent Process: PID = %d, Child PID = %d\n", getpid(), pid);
  }
  return 0;
}

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("No numbers provided.\n");
    fprintf(stderr, "Usage: %s <number1> <number2> ... <numberN>\n", argv[0]);
    return 1;
  }

  printf("Inside Helper File Name: %s\n", argv[0]);
  printf("Array Recieved: ");

  int n = argc - 1;
  int arr[n];

  for (int i = 0; i < n; i++)
  {
    arr[i] = atoi(argv[i + 1]);
    printf("%d ", arr[i]);
  }
  printf("\n");
  return 0;
}
