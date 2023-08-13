#include <stdio.h>
#include <string.h>

struct process
{
    char name[20];
    int at, bt, pr, ct, wt, tat;
    int isScheduled;
} p[20], temp;

void displayGanttChart(struct process d[], int num)
{
    printf("\nGANTT CHART\n");
    printf("-------------------------------------------------------------\n");
    printf("|");
    for (int i = 0; i < num; i++)
    {
        printf(" %-10s |", d[i].name);
    }
    printf("\n-------------------------------------------------------------\n");
    printf("0");
    for (int i = 0; i < num; i++)
    {
        printf("          %2d", d[i].ct);
    }
    printf("\n-------------------------------------------------------------\n");
}

int main()
{
    int n, i, j;
    printf("ENTER THE NUMBER OF PROCESSES: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("\nENTER DETAILS OF PROCESS %d\n", i + 1);
        printf("PROCESS NAME: ");
        scanf("%s", p[i].name);
        printf("ARRIVAL TIME: ");
        scanf("%d", &p[i].at);
        printf("BURST TIME: ");
        scanf("%d", &p[i].bt);
        printf("PRIORITY: ");
        scanf("%d", &p[i].pr);
        p[i].isScheduled = 0;
    }

    // Sort processes by arrival time (if arrival times are not in order)
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (p[i].at > p[j].at)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int currentTime = 0, numScheduled = 0, remProcess = n;
    struct process scheduled[20];

    if (p[0].at > 0)
    {
        currentTime = p[0].at;
        strcpy(scheduled[numScheduled].name, "Idle");
        scheduled[numScheduled].ct = currentTime;
        numScheduled++;
    }

    while (remProcess > 0)
    {
        int highestPriority = -1;
        int index = -1;

        for (i = 0; i < n; i++)
        {
            if (p[i].at <= currentTime && !p[i].isScheduled)
            {
                if (highestPriority == -1 || p[i].pr < highestPriority)
                {
                    highestPriority = p[i].pr;
                    index = i;
                }
            }
        }

        if (index != -1)
        {
            p[index].ct = currentTime + p[index].bt;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;
            currentTime = p[index].ct;
            p[index].isScheduled = 1;
            scheduled[numScheduled++] = p[index];
            remProcess--;
        }
        else
        {
            currentTime++;
        }
    }

    printf("\nPROCESS NAME\tCOMPLETION TIME\tWAITING TIME\tTURNAROUND TIME\n\n");
    float totalWT = 0, totalTAT = 0;
    for (i = 0; i < n; i++)
    {
        printf("%-15s\t%6d\t\t%6d\t\t%6d\n", p[i].name, p[i].ct, p[i].wt, p[i].tat);
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    printf("\nAVERAGE WAITING TIME: %.2f", totalWT / n);
    printf("\nAVERAGE TURNAROUND TIME: %.2f\n", totalTAT / n);

    displayGanttChart(scheduled, numScheduled);

    return 0;
}
