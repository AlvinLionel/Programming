#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

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
        fprintf(file, "Transaction %d={%s,%s,%.2lf}\n", transaction[i].username, transaction[i].type, transaction[i].amount);
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
} // I modified the fscanf to be like users.

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

void deposit()
{
    char password[50];
    double amount;
    bool userFound = false;

    printf("Enter your password: ");
    scanf("%s", &password);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(user[i].password, password) == 0)
        {
            printf("Enter the amount you want to deposit: ");
            scanf("%lf", &amount);
            userFound = true;
            user[i].balance += amount;
            printf("\nDeposit successfull\n");
            printf("Your new balance is: $%.2lf\n", user[i].balance);

            strcpy(transaction[transactionCount].username, user[i].username);
            strcpy(transaction[transactionCount].type, "Deposit");
            transaction[transactionCount].amount = amount;
            transactionCount++;
            saveTransactions();
            return;
        }
    }
    if (!userFound)
    {
        printf("Invalid password.Please try again.\n");
    }
}

void withdraw()
{
    char username[50];
    double amount;
    bool userFound = false;

    printf("Enter your username: ");
    scanf("%s", &username);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(user[i].username, username) == 0)
        {
            printf("Enter the amount you want to withdraw: ");
            scanf("%lf", &amount);
            userFound = true;
            if (user[i].balance < amount)
            {
                printf("Insufficient balance\n");
                return;
            }
            user[i].balance -= amount;
            printf("\nWithdraw successfull\n");
            printf("Your new balance is: $%.2lf\n", user[i].balance);

            strcpy(transaction[transactionCount].username, username);
            strcpy(transaction[transactionCount].type, "Withdraw");
            transaction[transactionCount].amount = amount;
            transactionCount++;
            saveTransactions();
        }
    }
    if (!userFound)
    {
        printf("Invalid username.Please try again.\n");
    }
}

void transfer()
{
    char username[50];
    char receiver[50];
    double amount;
    bool userFound = false, receiverFound = false;

    printf("Enter your username: ");
    scanf("%s", &username);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(user[i].username, username) == 0)
        {
            userFound = true;
            printf("Enter the username of the receiver: ");
            scanf("%s", &receiver);
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
                return;
            }

            printf("Enter the amount you want to transfer: ");
            scanf("%lf", &amount);
            if (user[i].balance < amount)
            {
                printf("Insufficient balance\n");
                return;
            }
            for (int j = 0; j < userCount; j++)
            {
                if (strcmp(user[j].username, receiver) == 0)
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
                    return;
                }
            }
        }
    }
    if (!userFound)
    {
        printf("Invalid username.Please try again.\n");
    }
}

void checkBalance()
{
    char username[50];
    printf("Enter your username: ");
    scanf("%s", &username);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(user[i].username, username) == 0)
        {
            printf("\nYour balance is: $%.2lf\n", user[i].balance);
            return;
        }
    }
    printf("Invalid username.Please try again\n");
}

void transactionHistory()
{
    char username[50];
    bool userFound = false;

    printf("Enter your username: ");
    scanf("%s", username);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(user[i].username, username) == 0)
        {
            userFound = true;
            bool transactionFound = false;

            for (int j = 0; j < transactionCount; j++)
            {
                if (strcmp(transaction[j].username, username) == 0)
                {
                    printf("\nTransaction %d\n", j + 1);
                    printf("Name: %s\n", transaction[j].username);
                    printf("Type: %s\n", transaction[j].type);
                    printf("Amount: $%.2lf\n", transaction[j].amount);
                    transactionFound = true;
                }
            }
            if (!transactionFound)
            {
                printf("\nNo transactions have been performed yet.\n");
            }
            return;
        }
    }
    if (!userFound)
    {
        printf("Invalid username.Please try again\n");
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
            if (strcmp(user[i].username, username) == 0 && strcmp(user[i].password, password) == 0)
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
                        deposit();
                        break;
                    case 2:
                        withdraw();
                        break;
                    case 3:
                        transfer();
                        break;
                    case 4:
                        checkBalance();
                        break;
                    case 5:
                        transactionHistory();
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

void authorizedAccess()
{
    char systemPassword[20] = "Banking", inputPassword[20];
    bool authenticated = false;
    int passwordTrials = 0;

    printf("Enter the password: ");
    scanf("%s", inputPassword);

    while (passwordTrials < 3)
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
                printf("3. Exit\n");
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
                        printf("    Name= %s\n", user[i].name);
                        printf("    Username= %s\n", user[i].username);
                        printf("    Balance= %.2lf\n", user[i].balance);
                    }
                    break;
                case 2:
                    printf("\nThe number of transactions performed is: %d\n", transactionCount);
                    printf("The transactions are: \n");
                    for (int i = 0; i < transactionCount; i++)
                    {
                        printf("    Username= %s\n", transaction[i].username);
                        printf("    Type= %s\n", transaction[i].type);
                        printf("    Amount= %.2lf\n", transaction[i].amount);
                    }
                    break;
                case 3:
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
        }
    }
    if (!authenticated && passwordTrials == 3)
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
        printf("\n1. Create account\n");
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