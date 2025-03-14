#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <io.h>

#define MAX_USERS 100
#define MAX_TRANSACTIONS 100

typedef struct
{
    char name[50];
    char username[50];
    char password[50];
    double balance;
} users;
typedef struct
{
    char username[50];
    char type[50];
    double amount;
} transactions;

transactions transaction[MAX_TRANSACTIONS];
users user[MAX_USERS];

int userCount = 0, transactionCount = 0;

void saveUsers()
{
    FILE *file = fopen("../Others/Users.txt", "w");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }
    for (int i = 0; i < userCount; i++)
    {
        fprintf(file, "User %d={%s,%s,%s,%.2lf}\n", i + 1, user[i].name, user[i].username, user[i].password, user[i].balance);
    }
    fclose(file);
}

void loadUsers()
{
    FILE *file = fopen("../Others/Users.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }
    while (fscanf(file, "User %*d={%[^,],%[^,],%[^,],%lf}\n", user[userCount].name, user[userCount].username, user[userCount].password, &user[userCount].balance) != EOF)
    {
        userCount++;
    }
    fclose(file);
}

void saveTransactions()
{
    FILE *file = fopen("../Others/Transactions.txt", "w");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }
    for (int i = 0; i < transactionCount; i++)
    {
        fprintf(file, "Transaction %d={%s,%s,%.2lf}\n", i + 1, transaction[i].username, transaction[i].type, transaction[i].amount);
    }
    fclose(file);
}

void loadTransactions()
{
    FILE *file = fopen("../Others/Transactions.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }
    while (fscanf(file, "Transaction %*d={%[^,],%[^,],%lf}\n", transaction[transactionCount].username, transaction[transactionCount].type, &transaction[transactionCount].amount) != EOF)
    {
        transactionCount++;
    }
    fclose(file);
}

void createAccount()
{
    if (userCount >= MAX_USERS)
    {
        printf("Maximum number of users reached\n");
        return;
    }
    printf("Enter your full name: ");
    getchar();
    fgets(user[userCount].name, 50, stdin);

    user[userCount].name[strcspn(user[userCount].name, "\n")] = '\0';

    char username[50];
    bool usernameExists;

    do
    {
        printf("Enter your username: ");
        scanf("%s", username);
        getchar();

        usernameExists = false;
        for (int i = 0; i < userCount; i++)
        {
            if (strcmp(user[i].username, username) == 0)
            {
                printf("Username already exists,please try again.\n");
                usernameExists = true;
            }
        }
    } while (usernameExists);
    strcpy(user[userCount].username, username);

    printf("Enter your password: ");
    scanf("%s", user[userCount].password);
    getchar();

    userCount++;
    saveUsers();
    printf("Account created successfully\n");
}

void deposit(char *username)
{
    char password[50], choice[10];
    double amount;
    bool correctPassword = false;

    printf("Enter the amount you wish to deposit: ");
    scanf("%lf", &amount);
    printf("Enter your password: ");
    scanf("%s", &password);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(user[i].username, username) == 0)
        {
            if (strcmp(user[i].password, password) == 0)
            {
                correctPassword = true;
                printf("You are about to deposit $%.2lf,continue?(yes,no) \n", amount);
                scanf("%s", choice);
                if (strcmp(choice, "yes") == 0 || strcmp(choice, "Yes") == 0)
                {
                    user[i].balance += amount;
                    printf("\nDeposit successfull\n");
                    printf("Your new balance is: $%.2lf\n", user[i].balance);

                    strcpy(transaction[transactionCount].username, user[i].username);
                    strcpy(transaction[transactionCount].type, "Deposit");
                    transaction[transactionCount].amount = amount;
                    transactionCount++;
                    saveTransactions();
                    break;
                }
                else
                {
                    printf("Deposit cancelled\n");
                    break;
                }
            }
        }
    }
    if (!correctPassword)
    {
        printf("Invalid password.Please try again.\n");
    }
}

void withdraw(char *username)
{
    char password[50], choice[10];
    double amount;
    bool correctPassword = false;

    printf("Enter the amount you want to withdraw: ");
    scanf("%lf", &amount);
    printf("Enter your password: ");
    scanf("%s", &password);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(user[i].username, username) == 0)
        {
            if (strcmp(user[i].password, password) == 0)
            {
                if (user[i].balance < amount)
                {
                    printf("Insufficient balance\n");
                    break;
                }
                correctPassword = true;
                printf("You are about to withdraw $%.2lf,continue?(yes,no) \n", amount);
                scanf("%s", choice);
                if (strcmp(choice, "yes") == 0 || strcmp(choice, "Yes") == 0)
                {
                    user[i].balance -= amount;
                    printf("\nWithdraw successfull\n");
                    printf("Your new balance is: $%.2lf\n", user[i].balance);

                    strcpy(transaction[transactionCount].username, username);
                    strcpy(transaction[transactionCount].type, "Withdraw");
                    transaction[transactionCount].amount = amount;
                    transactionCount++;
                    saveTransactions();
                    break;
                }
                else
                {
                    printf("Withdrawal cancelled\n");
                    break;
                }
            }
        }
    }
    if (!correctPassword)
    {
        printf("Invalid password.Please try again.\n");
    }
}

void transfer(char *username)
{
    char password[50], receiver[50], choice[10];
    double amount;
    bool correctPassword = false, receiverFound = false;

    printf("Enter the username of the receiver: ");
    scanf("%s", &receiver);
    printf("Enter the amount you wish to transfer: ");
    scanf("%lf", &amount);
    printf("Enter your password: ");
    scanf("%s", &password);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(user[i].username, username) == 0)
        {
            if (strcmp(user[i].password, password) == 0)
            {
                correctPassword = true;
                for (int i = 0; i < userCount; i++)
                {
                    if (strcmp(user[i].username, receiver) == 0)
                    {
                        receiverFound = true;
                    }
                }
                if (!receiverFound)
                {
                    printf("Invalid receiver username.Please try again\n");
                    break;
                }
                if (user[i].balance < amount)
                {
                    printf("Insufficient balance\n");
                    break;
                }
                for (int j = 0; j < userCount; j++)
                {
                    if (strcmp(user[j].username, receiver) == 0)
                    {
                        printf("You are about to transfer $%.2lf to %s,continue?(yes,no) \n", amount, user[j].name);
                        scanf("%s", choice);
                        if (strcmp(choice, "yes") == 0 || strcmp(choice, "Yes") == 0)
                        {
                            user[i].balance -= amount;
                            user[j].balance += amount;
                            printf("Trasfer successfull\n");
                            printf("Your new balance is: $%.2lf\n", user[i].balance);

                            strcpy(transaction[transactionCount].username, username);
                            strcpy(transaction[transactionCount].type, "Trasfer");
                            transaction[transactionCount].amount = amount;
                            transactionCount++;
                            saveTransactions();
                            break;
                        }
                        else
                        {
                            printf("Transfer cancelled\n");
                            break;
                        }
                    }
                }
            }
        }
    }
    if (!correctPassword)
    {
        printf("Invalid password.Please try again.\n");
    }
}

void checkBalance(char *username)
{
    char password[50];
    printf("Enter your password: ");
    scanf("%s", &password);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(user[i].password, password) == 0)
        {
            printf("\nYour balance is: $%.2lf\n", user[i].balance);
            return;
        }
    }
    printf("Invalid password.Please try again\n");
}

void transactionHistory(char *username)
{
    char password[50];
    bool correctPassword = false;

    printf("Enter your password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(user[i].username, username) == 0)
        {
            if (strcmp(user[i].password, password) == 0)
            {
                correctPassword = true;
                bool transactionFound = false;

                for (int j = 0; j < transactionCount; j++)
                {
                    if (strcmp(transaction[j].username, username) == 0)
                    {
                        transactionFound = true;
                        printf("\nTransaction %d\n", j + 1);
                        printf("\tName: %s\n", transaction[j].username);
                        printf("\tType: %s\n", transaction[j].type);
                        printf("\tAmount: $%.2lf\n", transaction[j].amount);
                    }
                }
                if (!transactionFound)
                {
                    printf("\nNo transactions have been performed yet.\n");
                }
                break;
            }
        }
    }
    if (!correctPassword)
    {
        printf("Invalid password.Please try again\n");
    }
}

void userAuthentication()
{
    char username[50];
    char password[50];
    int passwordTrials = 0;
    bool authenticated = false;

    printf("Enter your username: ");
    scanf("%s", &username);

    while (passwordTrials < 3)
    {
        printf("Enter your password: ");
        scanf("%s", &password);

        for (int i = 0; i < userCount; i++)
        {
            if (strcmp(user[i].username, username) == 0 && strcmp(user[i].password, password) == 0) // check if an incorrect username will be treated the same as an incorrect password
            {
                printf("\nWelcome %s\n", user[i].name);
                authenticated = true;

                while (1)
                {
                    int choice;
                    printf("\n1. Deposit\n");
                    printf("2. Withdraw\n");
                    printf("3. Trasfer\n");
                    printf("4. Check balance\n");
                    printf("5. Transaction history\n");
                    printf("6. Log out\n");
                    printf("\nEnter your choice: ");
                    scanf("%d", &choice);

                    switch (choice)
                    {
                    case 1:
                        deposit(username);
                        break;
                    case 2:
                        withdraw(username);
                        break;
                    case 3:
                        transfer(username);
                        break;
                    case 4:
                        checkBalance(username);
                        break;
                    case 5:
                        transactionHistory(username);
                        break;
                    case 6:
                        printf("Logging out...\n");
                        return;
                    default:
                        printf("Invalid choice\n");
                        break;
                    }
                }
            }
        }
        if (!authenticated)
        {
            passwordTrials++;
            if (passwordTrials < 3)
            {
                printf("Invalid password.Trials left: %d\n", 3 - passwordTrials);
            }
        }
    }
    if (!authenticated && passwordTrials == 3)
    {
        printf("\nMaximum trials reached.Try again later\n");
        exit(0);
    }
}

void deleteUser(char *username)
{
    FILE *file = fopen("../Others/Users.txt", "r");
    if (file == NULL)
    {
        perror("File opening unsuccessful");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL)
    {
        perror("Memory allocation failed");
        fclose(file);
        exit(1);
    }

    fread(buffer, 1, fileSize, file);
    fclose(file);
    buffer[fileSize] = '\0';

    file = fopen("../Others/Users.txt", "w");
    if (file == NULL)
    {
        perror("File opening unsuccessful");
        free(buffer);
        exit(1);
    }

    char *line = strtok(buffer, "\n");
    while (line != NULL)
    {
        if (strstr(line, username) == NULL)
        {
            fprintf(file, "%s\n", line);
        }
        line = strtok(NULL, "\n");
    }

    free(buffer);
    fclose(file);

    userCount--;
    saveUsers();
}

void deleteTransactions(char *username)
{
    FILE *file = fopen("../Others/Transactions.txt", "r");
    if (file == NULL)
    {
        perror("File opening unsuccessful");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL)
    {
        perror("Memory allocation failed");
        fclose(file);
        exit(1);
    }

    fread(buffer, 1, fileSize, file);
    fclose(file);
    buffer[fileSize] = '\0';

    file = fopen("../Others/Transactions.txt", "w");
    if (file == NULL)
    {
        perror("File opening unsuccessful");
        free(buffer);
        exit(1);
    }

    char *line = strtok(buffer, "\n");
    while (line != NULL)
    {
        if (strstr(line, username) == NULL)
        {
            fprintf(file, "%s\n", line);
        }
        line = strtok(NULL, "\n");
    }

    free(buffer);
    fclose(file);

    transactionCount--;
    saveTransactions();
}

void deleteAccount()
{
    char username[50];
    printf("Enter the username of the account you want to delete: ");
    scanf("%s", username);

    bool userFound = false;
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(user[i].username, username) == 0)
        {
            userFound = true;
            deleteUser(username);
            deleteTransactions(username);
            printf("Account deleted successfully\n");
            break;
        }
    }
    if (!userFound)
    {
        printf("Invalid username.Please try again\n");
    }
}

void authorizedAccess()
{
    char systemPassword[20] = "Banking", inputPassword[20];
    bool authenticated = false;
    int passwordTrials = 0;

password_entry:
    printf("Enter the password: ");
    scanf("%s", inputPassword);

    while (passwordTrials < 2)
    {
        if (strcmp(inputPassword, systemPassword) == 0)
        {
            authenticated = true;
            int choice;
            printf("Access granted\n");

            while (1)
            {
                printf("\n1. Show users\n");
                printf("2. Show transactions\n");
                printf("3. Delete account\n");
                printf("4. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                    printf("\nThe number of users is %d\n", userCount);
                    printf("The users are:\n");
                    for (int i = 0; i < userCount; i++)
                    {
                        printf("User %d:\n", i + 1);
                        printf("\tName= %s\n", user[i].name);
                        printf("\tUsername= %s\n", user[i].username);
                        printf("\tPassword= %s\n", user[i].password);
                        printf("\tBalance= %.2lf\n", user[i].balance);
                    }
                    break;
                case 2:
                    printf("\nThe number of transactions performed is: %d\n", transactionCount);
                    printf("The transactions are: \n");
                    for (int i = 0; i < transactionCount; i++)
                    {
                        printf("Transaction %d:\n", i + 1);
                        printf("\tUsername= %s\n", transaction[i].username);
                        printf("\tType= %s\n", transaction[i].type);
                        // Check if there is a way i can add a print function to print the username of the receiver.
                        printf("\tAmount= %.2lf\n", transaction[i].amount);
                    }
                    break;
                case 3:
                    deleteAccount();
                    break;
                case 4:
                    printf("Exiting...\n");
                    return;
                    break;
                default:
                    printf("Invalid choice.Please try again.\n");
                    break;
                }
                break;
            }
        }
        if (!authenticated)
        {
            passwordTrials++;
            printf("Incorrect password.Trials remaining %d.\n", 3 - passwordTrials);
            goto password_entry;
        }
    }
    if (!authenticated && passwordTrials == 2)
    {
        printf("Maximum number of trials reached.Please try again later\n");
        return;
    }
}

int main()
{
    loadUsers();
    loadTransactions();

    while (1)
    {
        int choice;
        printf("\n1. Create account\a\n");
        printf("2. Login\n");
        printf("3. System info\n");
        printf("4. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createAccount();
            break;
        case 2:
            userAuthentication();
            break;
        case 3:
            authorizedAccess();
            break;
        case 4:
            printf("Exiting...\n");
            saveUsers();
            saveTransactions();
            exit(0);
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    }

    return 0;
}