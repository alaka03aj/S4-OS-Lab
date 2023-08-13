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
    int n, i, j, quantum;
    printf("ENTER THE NUMBER OF PROCESSES: ");
    scanf("%d", &n);
    printf("ENTER TIME QUANTUM: ");
    scanf("%d", &quantum);

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
    struct process scheduled[100]; // Increased the size to accommodate potential scheduling

    while (remProcess > 0) {
        for (i = 0; i < n; i++) {
            if (p[i].at <= currentTime && !p[i].isScheduled) {
                int executionTime = p[i].bt < quantum ? p[i].bt : quantum;
                p[i].bt -= executionTime;
                currentTime += executionTime;
                p[i].ct = currentTime;
                p[i].tat = p[i].ct - p[i].at;
                p[i].wt = p[i].tat - p[i].ct;
                p[i].isScheduled = p[i].bt == 0 ? 1 : 0;

                strcpy(scheduled[numScheduled].name, p[i].name);
                scheduled[numScheduled].ct = currentTime;
                numScheduled++;

                if (p[i].bt == 0) {
                    remProcess--;
                }
            }
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
