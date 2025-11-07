
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, head, total = 0, disk_size;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    int req[n];
    printf("Enter the request queue: ");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter total disk size: ");
    scanf("%d", &disk_size);


    for (i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (req[i] > req[j]) {
                int temp = req[i];
                req[i] = req[j];
                req[j] = temp;
            }
        }
    }

    int index;
    for (i = 0; i < n; i++)
        if (head < req[i]) {
            index = i;
            break;
        }

    printf("\nSequence of movement: ");
 
    for (i = index; i < n; i++) {
        printf("%d ", req[i]);
        total += abs(head - req[i]);
        head = req[i];
    }


    total += abs(disk_size - 1 - head);
    head = disk_size - 1;

    
    for (i = index - 1; i >= 0; i--) {
        printf("%d ", req[i]);
        total += abs(head - req[i]);
        head = req[i];
    }

    printf("\nTotal Seek Time: %d\n", total);
    printf("Average Seek Time: %.2f\n", (float)total / n);

    return 0;
}
