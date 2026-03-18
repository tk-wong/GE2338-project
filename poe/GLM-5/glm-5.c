#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 50
#define FILENAME "users.txt"

// Structure to hold user credentials
typedef struct {
    char username[MAX_LEN];
    char password[MAX_LEN];
} User;

// Helper function to remove the newline character from fgets input
void trimNewline(char *str) {
    str[strcspn(str, "\n")] = 0;
}

int main() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Error opening file");
        printf("Please ensure '%s' exists.\n", FILENAME);
        return 1;
    }

    // 1. Count the number of users in the file to allocate memory
    char buffer[150];
    int count = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
    }
    rewind(file); // Reset file pointer to the beginning

    if (count == 0) {
        printf("No users found in the file.\n");
        fclose(file);
        return 0;
    }

    // 2. Allocate memory for users
    User *users = malloc(count * sizeof(User));
    if (users == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return 1;
    }

    // 3. Read user data from file
    int idx = 0;
    while (idx < count && fscanf(file, "%49s %49s", users[idx].username, users[idx].password) == 2) {
        idx++;
    }
    fclose(file);

    // 4. Get user input
    char inputUser[MAX_LEN];
    char inputPass[MAX_LEN];

    printf("=== Login System ===\n");
    
    printf("Enter username: ");
    if (fgets(inputUser, sizeof(inputUser), stdin) == NULL) {
        printf("Error reading username.\n");
        free(users);
        return 1;
    }
    trimNewline(inputUser);

    printf("Enter password: ");
    if (fgets(inputPass, sizeof(inputPass), stdin) == NULL) {
        printf("Error reading password.\n");
        free(users);
        return 1;
    }
    trimNewline(inputPass);

    // 5. Check credentials
    int isAuthenticated = 0;
    for (int i = 0; i < idx; i++) {
        if (strcmp(users[i].username, inputUser) == 0 && strcmp(users[i].password, inputPass) == 0) {
            isAuthenticated = 1;
            break;
        }
    }

    // 6. Print result
    if (isAuthenticated) {
        printf("\nAccess Granted. Welcome, %s!\n", inputUser);
    } else {
        printf("\nAccess Denied. Invalid username or password.\n");
    }

    // Clean up memory
    free(users);

    return 0;
}