//*
// preemptive SJF
#include <stdio.h>

struct process
{
    int at;   // Arrival Time
    int bt;   // Burst Time
    int rt;   // Remaining Time
    int ct;   // Completion Time
    int tat;  // Turnaround Time
    int wt;   // Waiting Time
    int done; // Completion flag
};

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    // Input arrival times
    printf("Enter Arrival Times:\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i + 1);
        scanf("%d", &p[i].at);
    }

    // Input burst times
    printf("Enter Burst Times:\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].done = 0;
    }

    int time = 0, finished = 0;
    int min_rt, m;

    // Main scheduling loop
    while (finished < n)
    {
        m = -1;
        min_rt = 99999;

        // Find process with shortest remaining time among those that have arrived
        for (int i = 0; i < n; i++)
        {
            if (p[i].done == 0 && p[i].at <= time && p[i].rt < min_rt)
            {
                min_rt = p[i].rt;
                m = i;
            }
        }

        if (m == -1)
        {
            // No process available, advance time
            time++;
        }
        else
        {
            // Execute the selected process for 1 unit
            p[m].rt--;
            time++;

            if (p[m].rt == 0)
            {
                p[m].ct = time;
                p[m].done = 1;
                finished++;
            }
        }
    }

    // Calculate Turnaround and Waiting Times
    for (int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }

    // Display results
    printf("\nAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n",
               p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat);
    }

    // Calculate averages
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
