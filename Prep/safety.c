#include <stdio.h>
#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int n, m;  // Number of processes and resources
    int available[MAX_RESOURCES];
    int max_claim[MAX_PROCESSES][MAX_RESOURCES];
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resources: ");
    scanf("%d", &m);

    printf("Enter the available resources for each type: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum claim matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &max_claim[i][j]);
        }
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max_claim[i][j] - allocation[i][j];
        }
    }

    // Initialize the work vector with available resources
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    // Safety algorithm
    int safe_sequence[MAX_PROCESSES];
    int count = 0;
    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == m) {
                    // All resources for process i can be allocated
                    for (int k = 0; k < m; k++) {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = 1;
                    safe_sequence[count++] = i;
                    found = 1;
                }
            }
        }
        if (!found) {
            break; // No safe sequence found
        }
    }

    if (count == n) {
        printf("Safe sequence exists: ");
        for (int i = 0; i < n; i++) {
            printf("%d", safe_sequence[i]);
            if (i < n - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
    } else {
        printf("No safe sequence exists.\n");
    }

    return 0;
}
