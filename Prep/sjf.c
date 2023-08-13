#include <stdio.h>
#include <string.h>

struct process {
    char name[20];
    int at, bt, ct, wt, tat;
    int isScheduled;
} p[20], temp;

void displayGanttChart(struct process d[], int num) {
    printf("\nGANTT CHART\n");
    printf("-------------------------------------------------------------\n");
    printf("|");
    for (int i = 0; i < num; i++) {
        printf(" %-10s |", d[i].name);
    }
    printf("\n-------------------------------------------------------------\n");
    printf("0");
    for (int i = 0; i < num; i++) {
        printf("          %2d", d[i].ct);
    }
    printf("\n-------------------------------------------------------------\n");
}

int main() {
    int n, i, j;
    printf("ENTER THE NUMBER OF PROCESSES: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nENTER DETAILS OF PROCESS %d\n", i + 1);
        printf("PROCESS NAME: ");
        scanf("%s", p[i].name);
        printf("ARRIVAL TIME: ");
        scanf("%d", &p[i].at);
        printf("BURST TIME: ");
        scanf("%d", &p[i].bt);
        p[i].isScheduled = 0;
    }

    int currentTime = 0, numScheduled = 0, remProcess = n;
    struct process scheduled[20];

    while (remProcess > 0) {
        int shortestJobIndex = -1;
        int shortestJobTime = 9999;

        for (i = 0; i < n; i++) {
            if (p[i].at <= currentTime && !p[i].isScheduled && p[i].bt < shortestJobTime) {
                shortestJobTime = p[i].bt;
                shortestJobIndex = i;
            }
        }

        if (shortestJobIndex != -1) {
            p[shortestJobIndex].ct = currentTime + p[shortestJobIndex].bt;
            p[shortestJobIndex].tat = p[shortestJobIndex].ct - p[shortestJobIndex].at;
            p[shortestJobIndex].wt = p[shortestJobIndex].tat - p[shortestJobIndex].bt;
            currentTime = p[shortestJobIndex].ct;
            p[shortestJobIndex].isScheduled = 1;
            strcpy(scheduled[numScheduled].name, p[shortestJobIndex].name);
            scheduled[numScheduled].ct = currentTime;
            numScheduled++;
            remProcess--;
        } else {
            currentTime++;
        }
    }

    printf("\nPROCESS NAME\tCOMPLETION TIME\tWAITING TIME\tTURNAROUND TIME\n\n");
    float totalWT = 0, totalTAT = 0;
    for (i = 0; i < n; i++) {
        printf("%-15s\t%6d\t\t%6d\t\t%6d\n", p[i].name, p[i].ct, p[i].wt, p[i].tat);
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    printf("\nAVERAGE WAITING TIME: %.2f", totalWT / n);
    printf("\nAVERAGE TURNAROUND TIME: %.2f\n", totalTAT / n);

    displayGanttChart(scheduled, numScheduled);

    return 0;
}
