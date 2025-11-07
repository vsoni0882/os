#include <stdio.h>
#include <stdlib.h>

void sstf(int req[], int n, int head) {
    int total = 0, visited[100] = {0};

    printf("\nSSTF Sequence: ");
    for (int i = 0; i < n; i++) {
        int min = 9999, pos = -1;

        // find nearest unvisited request
        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int diff = abs(req[j] - head);
                if (diff < min) {
                    min = diff;
                    pos = j;
                }
            }
        }

        visited[pos] = 1; // mark visited
        total += abs(req[pos] - head);
        head = req[pos];
        printf("%d ", head);
    }

    printf("\nTotal Seek Time: %d", total);
    printf("\nAverage Seek Time: %.2f\n", (float)total / n);
}

int main() {
    int n, head, req[100];
    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request queue: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    sstf(req, n, head);
    return 0;
}
