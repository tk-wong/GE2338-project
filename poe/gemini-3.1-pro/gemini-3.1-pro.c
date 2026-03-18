#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 50

int main() {
    FILE *file;
    char stored_username[MAX_LEN];
    char stored_password[MAX_LEN];
    char input_username[MAX_LEN];
    char input_password[MAX_LEN];

    // 1. Open and read the credentials file
    file = fopen("credentials.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open credentials.txt.\n");
        printf("Please make sure the file exists in the same directory.\n");
        return 1; // Exit the program with an error code
    }

    // Read the username and password from the file
    // We use %49s to prevent buffer overflow (leaving 1 byte for the null terminator)
    if (fscanf(file, "%49s %49s", stored_username, stored_password) != 2) {
        printf("Error: Invalid file format in credentials.txt.\n");
        fclose(file);
        return 1;
    }
    fclose(file); // Close the file as we no longer need it

    // 2. Prompt the user for input
    printf("=== User Authentication ===\n");
    
    printf("Enter username: ");
    scanf("%49s", input_username);
    
    printf("Enter password: ");
    scanf("%49s", input_password);

    // 3. Compare the input with the stored credentials
    // strcmp returns 0 if the two strings are exactly identical
    if (strcmp(stored_username, input_username) == 0 && 
        strcmp(stored_password, input_password) == 0) {
        
        printf("\n[SUCCESS] Authentication successful! Welcome, %s.\n", input_username);
    } else {
        printf("\n[FAILED] Invalid username or password. Access denied.\n");
    }

    return 0;
}