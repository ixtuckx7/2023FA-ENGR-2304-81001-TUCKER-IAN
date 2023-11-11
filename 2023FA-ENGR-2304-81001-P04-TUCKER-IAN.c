#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Function to calculate the mean and standard deviation
void calculateStatistics(double data[], int n, double *mean, double *stdDev) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    *mean = sum / n;

    double sumSquaredDiff = 0;
    for (int i = 0; i < n; i++) {
        sumSquaredDiff += (data[i] - *mean) * (data[i] - *mean);
    }
    *stdDev = sqrt(sumSquaredDiff / n);
}

int main() {
    char filename[100];
    printf("Enter the filename: ");
    scanf("%s", filename);

    // Open the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found or could not be opened.\n");
        return 1;
    }

    double data[1000];
    int n = 0;
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, ", "); // Assume either comma or space delimiter
        while (token != NULL) {
            data[n++] = atof(token);
            token = strtok(NULL, ", ");
        }
    }

    double mean, stdDev;
    calculateStatistics(data, n, &mean, &stdDev);

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Show data\n");
        printf("2. Calculate mean and standard deviation\n");
        printf("3. Search for a value\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Data: ");
                for (int i = 0; i < n; i++) {
                    printf("%.2lf ", data[i]);
                }
                printf("\n");
                break;

            case 2:
                printf("Mean: %.2lf\n", mean);
                printf("Standard Deviation: %.2lf\n", stdDev);
                break;

            case 3:
                double searchValue;
                printf("Enter the value to search: ");
                scanf("%lf", &searchValue);
                int found = 0;
                for (int i = 0; i < n; i++) {
                    if (data[i] == searchValue) {
                        printf("Value %.2lf found at index %d\n", searchValue, i);
                        found = 1;
                    }
                }
                if (!found) {
                    printf("Value not found in the data.\n");
                }
                break;

            case 4:
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 4);

    fclose(file);
    return 0;
}




