#include <stdio.h>

struct process
{
    int at;
    int bt;
    int rt;
    int ct;
    int tat;
    int wt;
    int done;
};

int main()
{
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    printf("Enter Arrival Times:\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i + 1);
        scanf("%d", &p[i].at);
    }

    printf("Enter Burst Times:\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].done = 0;
    }

    printf("Enter Time quantum: ");
    scanf("%d", &tq);

    int time = 0, finished = 0;

    while (finished < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (p[i].done == 0 && p[i].at <= time)
            {
                if (p[i].rt > tq)
                {
                    time += tq;
                    p[i].rt -= tq;
                }
                else
                {
                    time += p[i].rt;
                    p[i].rt = 0;
                    p[i].ct = time;
                    p[i].done = 1;
                    finished++;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }

    printf("\nAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n",
               p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat);
    }

    float avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++)
    {
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }
    avg_wt = avg_wt / n;
    avg_tat = avg_tat / n;

    printf("\nAverage Waiting Time: %f", avg_wt);
    printf("\nAverage Turnaround Time: %f\n", avg_tat);

    return 0;
}
