#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS      100
#define MAX_USERNAME   64
#define MAX_PASSWORD   128
#define CREDENTIALS_FILE "credentials.txt"
#define MAX_ATTEMPTS   3

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

/*
 * Strips the trailing newline (or carriage return + newline) from a string.
 */
static void strip_newline(char *str)
{
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r'))
        str[--len] = '\0';
}

/*
 * Loads user credentials from the given file into the users array.
 * Returns the number of users loaded, or -1 on error.
 */
static int load_credentials(const char *filename, User *users, int max_users)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening credentials file");
        return -1;
    }

    char line[MAX_USERNAME + MAX_PASSWORD + 2]; /* +2 for ':' and '\0' */
    int count = 0;

    while (fgets(line, sizeof(line), fp) != NULL && count < max_users) {
        strip_newline(line);

        /* Skip empty lines and comments (lines starting with #) */
        if (line[0] == '\0' || line[0] == '#')
            continue;

        /* Find the colon delimiter */
        char *delimiter = strchr(line, ':');
        if (!delimiter) {
            fprintf(stderr, "Warning: malformed line skipped: \"%s\"\n", line);
            continue;
        }

        /* Split into username and password */
        *delimiter = '\0';
        const char *username = line;
        const char *password = delimiter + 1;

        if (strlen(username) == 0 || strlen(password) == 0) {
            fprintf(stderr, "Warning: empty username or password skipped.\n");
            continue;
        }

        strncpy(users[count].username, username, MAX_USERNAME - 1);
        users[count].username[MAX_USERNAME - 1] = '\0';

        strncpy(users[count].password, password, MAX_PASSWORD - 1);
        users[count].password[MAX_PASSWORD - 1] = '\0';

        count++;
    }

    fclose(fp);
    return count;
}

/*
 * Searches the users array for a matching username and password.
 * Returns 1 if authentication succeeds, 0 otherwise.
 */
static int authenticate(const User *users, int user_count,
                        const char *username, const char *password)
{
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

int main(void)
{
    User users[MAX_USERS];

    /* ---- Load credentials from file ---- */
    printf("Loading credentials from \"%s\"...\n", CREDENTIALS_FILE);
    int user_count = load_credentials(CREDENTIALS_FILE, users, MAX_USERS);

    if (user_count < 0) {
        fprintf(stderr, "Failed to load credentials. Exiting.\n");
        return EXIT_FAILURE;
    }

    if (user_count == 0) {
        fprintf(stderr, "No valid credentials found in file. Exiting.\n");
        return EXIT_FAILURE;
    }

    printf("Loaded %d user(s) successfully.\n\n", user_count);

    /* ---- Authentication loop ---- */
    char input_user[MAX_USERNAME];
    char input_pass[MAX_PASSWORD];
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS) {
        printf("=== Login (attempt %d/%d) ===\n", attempts + 1, MAX_ATTEMPTS);

        printf("Username: ");
        if (fgets(input_user, sizeof(input_user), stdin) == NULL) {
            printf("\nInput terminated. Exiting.\n");
            return EXIT_FAILURE;
        }
        strip_newline(input_user);

        printf("Password: ");
        if (fgets(input_pass, sizeof(input_pass), stdin) == NULL) {
            printf("\nInput terminated. Exiting.\n");
            return EXIT_FAILURE;
        }
        strip_newline(input_pass);

        if (authenticate(users, user_count, input_user, input_pass)) {
            printf("\n>> Authentication SUCCESSFUL. Welcome, %s!\n", input_user);
            return EXIT_SUCCESS;
        }

        attempts++;
        printf("\n>> Authentication FAILED. Invalid username or password.\n");

        if (attempts < MAX_ATTEMPTS)
            printf("   Please try again.\n\n");
    }

    printf("\n>> Maximum login attempts reached. Account locked.\n");
    return EXIT_FAILURE;
}