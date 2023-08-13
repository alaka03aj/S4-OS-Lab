#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

void printMatrix(const char *label, int matrix[MAX_PROCESSES][MAX_RESOURCES], int n, int m) {
    printf("%s:\n", label);
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n, m;  // Number of processes and resources
    int available[MAX_RESOURCES];
    int max_claim[MAX_PROCESSES][MAX_RESOURCES];
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};  // Initially, no process is finished

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

    // Resource request algorithm
    int process_id, request[MAX_RESOURCES];
    printf("Enter the process requesting resources (0-%d): ", n - 1);
    scanf("%d", &process_id);
    printf("Enter the resource request for each type: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &request[i]);
    }

    // Check if the request can be granted
    int is_request_granted = 1;
    for (int i = 0; i < m; i++) {
        if (request[i] > need[process_id][i] || request[i] > available[i]) {
            is_request_granted = 0;
            break;
        }
    }

    if (is_request_granted) {
        // Temporarily simulate allocation to check safety
        for (int i = 0; i < m; i++) {
            available[i] -= request[i];
            allocation[process_id][i] += request[i];
            need[process_id][i] -= request[i];
        }

        // Safety check after resource allocation
        int work_copy[MAX_RESOURCES];
        for (int i = 0; i < m; i++) {
            work_copy[i] = work[i];
        }
        int finish_copy[MAX_PROCESSES];
        for (int i = 0; i < n; i++) {
            finish_copy[i] = finish[i];
        }
        int count_copy = count;
        int safe_sequence_copy[MAX_PROCESSES];
        for (int i = 0; i < n; i++) {
            safe_sequence_copy[i] = safe_sequence[i];
        }

        int is_safe_after_allocation = 1;
        int found = 1;
        while (count_copy < n) {
            found = 0;
            for (int i = 0; i < n; i++) {
                if (!finish_copy[i]) {
                    int j;
                    for (j = 0; j < m; j++) {
                        if (need[i][j] > work_copy[j]) {
                            break;
                        }
                    }
                    if (j == m) {
                        // All resources for process i can be allocated
                        for (int k = 0; k < m; k++) {
                            work_copy[k] += allocation[i][k];
                        }
                        finish_copy[i] = 1;
                        safe_sequence_copy[count_copy++] = i;
                        found = 1;
                    }
                }
            }
            if (!found) {
                is_safe_after_allocation = 0;
                break;
            }
        }

        if (is_safe_after_allocation) {
            printf("Request is granted. New safe sequence: ");
            for (int i = 0; i < count_copy; i++) {
                printf("%d", safe_sequence_copy[i]);
                if (i < count_copy - 1) {
                    printf(" -> ");
                }
            }
            printf("\n");
        } else {
            printf("Request is denied. Unsafe state after resource allocation.\n");
        }

        // Restore original state
        for (int i = 0; i < m; i++) {
            available[i] += request[i];
            allocation[process_id][i] -= request[i];
            need[process_id][i] += request[i];
        }
    } else {
        printf("Request is denied. It exceeds process need or available resources.\n");
    }

    return 0;
}
