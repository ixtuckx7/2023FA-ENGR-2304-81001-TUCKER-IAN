/* 
   2023FA-ENGR-2304-81005-P02-TUCKER-IAN
   Author: Ian Tucker
   Date: October 2, 2023
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to convert a decimal number to an 8-bit signed magnitude binary number
char* decimalToBinary(int decimal) {
    char* binary = (char*)malloc(9); // 8 bits + '\0'
    if (decimal >= 0) {
        binary[0] = '0';
    } else {
        binary[0] = '1';
        decimal = -decimal;
    }
    int i;
    for (i = 7; i > 0; i--) {
        binary[i] = (decimal % 2) + '0';
        decimal /= 2;
    }
    binary[8] = '\0';
    return binary;
}

// Function to convert a binary number to decimal
int binaryToDecimal(char* binary) {
    int decimal = 0;
    int sign = 1;
    if (binary[0] == '1') {
        sign = -1;
        // Invert the binary bits for negative numbers
        for (int i = 1; i < 8; i++) {
            if (binary[i] == '0') {
                binary[i] = '1';
            } else {
                binary[i] = '0';
            }
        }
    }
    for (int i = 1; i < 8; i++) {
        decimal = decimal * 2 + (binary[i] - '0');
    }
    return decimal * sign;
}

// Function to convert a hexadecimal or binary string to binary
char* convertToBinary(char* input) {
    if (input[0] == '0' && (input[1] == 'x' || input[1] == 'X')) {
        // Hexadecimal to binary
        char* hex = input + 2; // Skip the "0x" prefix
        int len = strlen(hex);
        char* binary = (char*)malloc((4 * len + 1) * sizeof(char));
        char* binDigit;
        int binaryIndex = 0;
        for (int i = 0; i < len; i++) {
            switch (hex[i]) {
                case '0': binDigit = "0000"; break;
                case '1': binDigit = "0001"; break;
                case '2': binDigit = "0010"; break;
                case '3': binDigit = "0011"; break;
                case '4': binDigit = "0100"; break;
                case '5': binDigit = "0101"; break;
                case '6': binDigit = "0110"; break;
                case '7': binDigit = "0111"; break;
                case '8': binDigit = "1000"; break;
                case '9': binDigit = "1001"; break;
                case 'A': case 'a': binDigit = "1010"; break;
                case 'B': case 'b': binDigit = "1011"; break;
                case 'C': case 'c': binDigit = "1100"; break;
                case 'D': case 'd': binDigit = "1101"; break;
                case 'E': case 'e': binDigit = "1110"; break;
                case 'F': case 'f': binDigit = "1111"; break;
                default:
                    printf("Invalid hex digit: %c\n", hex[i]);
                    exit(1);
            }
            for (int j = 0; j < 4; j++) {
                binary[binaryIndex++] = binDigit[j];
            }
        }
        binary[binaryIndex] = '\0';
        return binary;
    } else {
        // Binary number
        int len = strlen(input);
        if (len != 8) {
            printf("Binary number must be 8 bits long.\n");
            exit(1);
        }
        char* binary = (char*)malloc((len + 1) * sizeof(char));
        strcpy(binary, input);
        return binary;
    }
}

int main() {
    int choice;
    do {
        printf("Menu Options:\n");
        printf("1. Decimal to binary or Binary to decimal (base 10)\n");
        printf("2. Hex to binary and Binary to hex\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int decimal;
            printf("Enter a decimal number (-127 to 127): ");
            scanf("%d", &decimal);

            if (decimal < -127 || decimal > 127) {
                printf("Invalid input. Number must be between -127 and 127.\n");
                continue;
            }

            char* binary = decimalToBinary(decimal);
            printf("Binary representation: %s\n", binary);
            free(binary);

            char binaryInput[9];
            printf("Enter an 8-bit binary number (-127 to 127): ");
            scanf("%s", binaryInput);

            int result = binaryToDecimal(binaryInput);
            printf("Decimal representation: %d\n", result);
        } else if (choice == 2) {
            char input[20];
            printf("Enter a positive number in binary or hexadecimal: ");
            scanf("%s", input);

            char* binary = convertToBinary(input);
            printf("64-bit binary representation: %s\n", binary);

            if (input[0] == '0' && (input[1] == 'x' || input[1] == 'X')) {
                // Hexadecimal input
                printf("16-bit hexadecimal representation: %s\n", input);
            } else {
                // Binary input
                char hex[20];
                int len = strlen(binary);
                int padding = 16 - len;
                if (padding < 0) {
                    printf("Binary number is too long to convert to hexadecimal.\n");
                    continue;
                }
                strcpy(hex, "0x");
                for (int i = 0; i < padding; i++) {
                    strcat(hex, "0");
                }
                strcat(hex, binary);
                printf("16-bit hexadecimal representation: %s\n", hex);
            }

            free(binary);
        } else if (choice != 3) {
            printf("Invalid choice. Please enter 1, 2, or 3.\n");
        }
    } while (choice != 3);

    return 0;
}
