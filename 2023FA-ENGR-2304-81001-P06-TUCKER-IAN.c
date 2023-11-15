/*
	2023FA-ENGR-2304-81001-P06-TUCKER-IAN
	AUTHOR: IAN TUCKER
	DATE: NOVEMBER 15, 2023
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 1200
#define MAX_LINE_SIZE 100

// Function prototypes
void readData(char* fileName, double data[], int* dataSize);
void printMenu();
void calculateStatistics(double data[], int dataSize, double* mean, double* stdDev);
void createReport(double data[], int dataSize, double mean, double stdDev);
int findValue(double data[], int dataSize, double value);
void clearInputBuffer();

int main() {
    char fileName[] = "P06_ASSIGNMENT.csv"; // Specify the file name
    double data[MAX_SIZE];
    int dataSize = 0;
    double mean, stdDev;
    int choice;
    double searchValue;
    int index;

    readData(fileName, data, &dataSize);

    do {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer(); // Clear input buffer to handle potential issues

        switch (choice) {
            case 1:
                calculateStatistics(data, dataSize, &mean, &stdDev);
                createReport(data, dataSize, mean, stdDev);
                break;

            case 2:
                printf("Enter a value to search: ");
                scanf("%lf", &searchValue);
                clearInputBuffer(); // Clear input buffer after reading search value
                index = findValue(data, dataSize, searchValue);
                if (index != -1) {
                    printf("Value %.2lf found at index %d\n", searchValue, index);
                } else {
                    printf("Value %.2lf not found in the data\n", searchValue);
                }
                break;

            case 3:
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 3);

    return 0;
}

// Function to read data from a file
void readData(char* fileName, double data[], int* dataSize) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_SIZE];
    while (fgets(line, sizeof(line), file) != NULL && *dataSize < MAX_SIZE) {
        char* token = strtok(line, "\t");
        while (token != NULL) {
            data[(*dataSize)++] = atof(token);
            token = strtok(NULL, "\t");
        }
    }

    fclose(file);
}

// Function to print the menu
void printMenu() {
    printf("\nMenu:\n");
    printf("1. Calculate Statistics and Create Report\n");
    printf("2. Search for a Value\n");
    printf("3. Exit\n");
}

// Function to calculate mean and standard deviation
void calculateStatistics(double data[], int dataSize, double* mean, double* stdDev) {
    double sum = 0.0, sumSquaredDiff = 0.0;

    for (int i = 0; i < dataSize; i++) {
        sum += data[i];
    }

    *mean = sum / dataSize;

    for (int i = 0; i < dataSize; i++) {
        sumSquaredDiff += pow(data[i] - *mean, 2);
    }

    *stdDev = sqrt(sumSquaredDiff / dataSize);
}

// Function to create a report
void createReport(double data[], int dataSize, double mean, double stdDev) {
    printf("\nReport:\n");
    printf("Number of data points: %d\n", dataSize);
    printf("Mean: %.2lf\n", mean);
    printf("Standard Deviation: %.2lf\n", stdDev);
}

// Function to search for a value in the data
int findValue(double data[], int dataSize, double value) {
    for (int i = 0; i < dataSize; i++) {
        if (data[i] == value) {
            return i;
        }
    }
    return -1;  // Value not found
}

// Function to clear the input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


