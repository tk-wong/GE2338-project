#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

int main(void) {
    char storedUsername[MAX_LEN];
    char storedPassword[MAX_LEN];
    char inputUsername[MAX_LEN];
    char inputPassword[MAX_LEN];

    FILE *file = fopen("credentials.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open credentials file.\n");
        return 1;
    }

    if (fscanf(file, "%99s %99s", storedUsername, storedPassword) != 2) {
        printf("Error: Invalid credentials file format.\n");
        fclose(file);
        return 1;
    }

    fclose(file);

    printf("Enter username: ");
    scanf("%99s", inputUsername);

    printf("Enter password: ");
    scanf("%99s", inputPassword);

    if (strcmp(inputUsername, storedUsername) == 0 &&
        strcmp(inputPassword, storedPassword) == 0) {
        printf("Authentication successful.\n");
    } else {
        printf("Authentication failed.\n");
    }

    return 0;
}#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

int main(void) {
    char storedUsername[MAX_LEN];
    char storedPassword[MAX_LEN];
    char inputUsername[MAX_LEN];
    char inputPassword[MAX_LEN];

    FILE *file = fopen("credentials.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open credentials file.\n");
        return 1;
    }

    if (fscanf(file, "%99s %99s", storedUsername, storedPassword) != 2) {
        printf("Error: Invalid credentials file format.\n");
        fclose(file);
        return 1;
    }

    fclose(file);

    printf("Enter username: ");
    scanf("%99s", inputUsername);

    printf("Enter password: ");
    scanf("%99s", inputPassword);

    if (strcmp(inputUsername, storedUsername) == 0 &&
        strcmp(inputPassword, storedPassword) == 0) {
        printf("Authentication successful.\n");
    } else {
        printf("Authentication failed.\n");
    }

    return 0;
}