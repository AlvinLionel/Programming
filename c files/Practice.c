#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_USERS 100
#define MAX_TRANSACTIONS 100

typedef struct{
    char name[50];
    char username[50];
    char password[50];
    double balance;
}users;
typedef struct{
    char username[50];
    char type[50];
    double amount;
}transactions;

transactions transaction[MAX_TRANSACTIONS];
users user[MAX_USERS];

int userCount=0,transactionCount=0;

void saveUsers()
{
    FILE *file=fopen("../Others/Users.txt","w");
    if(file==NULL)
    {
        //fprintf(stderr,"Error opening file\n");
        perror("Error opening file");
        exit(1);
    }
    for(int i=0;i<userCount;i++)
    {
        fprintf(file,"%s,%s,%s,%.2lf\n",user[i].name,user[i].username,user[i].password,user[i].balance);
    }
    fclose(file);
}
void loadUsers()
{
    FILE *file=fopen("../Others/Users.txt","r");
    if(file==NULL)
    {
        //fprintf(stderr,"Error opening file\n");
        perror("Error opening file");
        exit(1);
    }
    while(fscanf(file,"%s,%s,%s,%lf\n",user[userCount].name,user[userCount].username,user[userCount].password,&user[userCount].balance)!=EOF)
    {
        userCount++;
    }
    fclose(file);
}
void saveTransactions()
{
    FILE *file=fopen("../Others/Transactions.txt","w");
    if(file==NULL)
    {
        //fprintf(stderr,"Error opening file\n");
        perror("Error opening file");
        exit(1);
    }
    for(int i=0;i<transactionCount;i++)
    {
        fprintf(file,"%s,%s,%.2lf\n",transaction[i].username,transaction[i].type,transaction[i].amount);
    }
    fclose(file);
}
void loadTransactions()
{
    FILE *file=fopen("../Others/Transactions.txt","r");
    if(file==NULL)
    {
        //fprintf(stderr,"Error opening file\n");
        perror("Error opening file");
        exit(1);
    }
    while(fscanf(file,"%s,%s,%lf\n",transaction[transactionCount].username,transaction[transactionCount].type,&transaction[transactionCount].amount)!=EOF)
    {
        transactionCount++;
    }
    fclose(file);
}

void createAccount()
{
    if(userCount>=MAX_USERS)
    {
        printf("Maximum number of users reached\n");
        return;
    }
    printf("Enter your full name: ");
    getchar();
    fgets(user[userCount].name,50,stdin);

    user[userCount].name[strcspn(user[userCount].name, "\n")]='\0';

    printf("Enter your username: ");
    scanf("%s",user[userCount].username);
    getchar();
    printf("Enter your password: ");
    scanf("%s",user[userCount].password);
    getchar();

    userCount++;
    saveUsers();
    printf("Account created successfully\n");
}
void deposit()
{
    char username[50];
    double amount;
    printf("Enter your username: ");
    scanf("%s",&username);
    printf("Enter the amount you want to deposit: ");
    scanf("%lf",&amount);

    for(int i=0;i<userCount;i++)
    {
        if(strcmp(user[i].username,username)==0)
        {
            user[i].balance+=amount;
            printf("Deposit successfull\n");
            printf("Your new balance is: %.2lf\n",user[i].balance);
            return;
        }
        else{
            printf("Invalid username\n");
            return;
        }
    }
    transaction[transactionCount].amount=amount;
    strcpy(transaction[transactionCount].username,username);
    strcpy(transaction[transactionCount].type,"Deposit");
    transactionCount++;
    saveTransactions();
}
void withdraw()
{
    char username[50];
    double amount;
    printf("Enter your username: ");
    scanf("%s",&username);
    printf("Enter the amount you want to withdraw: ");
    scanf("%lf",&amount);

    for(int i=0;i<userCount;i++)
    {
        if(strcmp(user[i].username,username)==0)
        {
            if(user[i].balance<amount)
            {
                printf("Insufficient balance\n");
                return;
            }
            user[i].balance-=amount;
            printf("Withdraw successfull\n");
            printf("Your new balance is: %.2lf\n",user[i].balance);
        }
        else
        {
            printf("Invalid username\n");
            return;
        }
    }
    transaction[transactionCount].amount=amount;
    strcpy(transaction[transactionCount].username,username);
    strcpy(transaction[transactionCount].type,"Withdraw");
    transactionCount++;
    saveTransactions();
}
void transfer()
{
    char username[50];
    char receiver[50];
    double amount;
    printf("Enter your username: ");
    scanf("%s",&username);
    printf("Enter the username of the receiver: ");
    scanf("%s",&receiver);
    printf("Enter the amount you want to transfer: ");
    scanf("%lf",&amount);

    for(int i=0;i<userCount;i++)
    {
        if(strcmp(user[i].username,username)==0)
        {
            if(user[i].balance<amount)
            {
                printf("Insufficient balance\n");
                return;
            }
            for(int j=0;j<userCount;j++)
            {
                if(strcmp(user[i].username,receiver)==0)
                {
                    user[i].balance-=amount;
                    user[j].balance+=amount;
                    printf("Trasfer successfull\n");
                    printf("Your new balance is: %.2lf\n",user[i].balance);
                    return;
                }
                else
                {
                    printf("Invalid receiver username\n");
                    return;
                }
            }
        }
        else
        {
            printf("Invalid username\n");
            return;
        }
    }
    transaction[transactionCount].amount=amount;
    strcpy(transaction[transactionCount].username,username);
    strcpy(transaction[transactionCount].type,"Trasfer");
    transactionCount++;
    saveTransactions();
}
void checkBalance()
{
    char username[50];
    printf("Enter your username: ");
    scanf("%s",&username);

    for(int i=0;i<userCount;i++)
    {
        if(strcmp(user[i].username,username)==0)
        {
            printf("Your balance is: %.2lf\n",user[i].balance);
            return;
        }
        else
        {
            printf("Invalid username\n");
            return;
        }
    }
}
void transactionHistory()
{
    char username[50];
    printf("Enter your username: ");
    scanf("%s",&username);

    for(int i=0;i<userCount;i++)
    {
        if(strcmp(user[i].username,username)==0)
        {
            for(int j=0;j<transactionCount;j++)
            {
                if(transaction[j].amount==0)
                {
                    break;
                }
                else
                {
                    printf("Transaction %d\n",j+1);
                    printf("Name: %s\n",transaction[j].username);
                    printf("Type: %s\n",transaction[j].type);
                    printf("Amount: %.2lf\n",transaction[j].amount);
                }
            }
        }
        else
        {
            printf("Invalid username\n");
            return;
        }
    }
}
void userAuthentication()
{
    char username[50];
    char password[50];
    printf("Enter your username: ");
    scanf("%s",&username);
    printf("Enter your password: ");
    scanf("%s",&password);

    for(int i=0;i<userCount;i++)
    {
        if(strcmp(user[i].username,username)==0 && strcmp(user[i].password,password)==0)
        {
            printf("\nWelcome %s\n",user[i].name);
            
            while(1)
            {
                int choice;
                printf("1. Deposit\n");
                printf("2. Withdraw\n");
                printf("3. Trasfer\n");
                printf("4. Check balance\n");
                printf("5. Transaction history\n");
                printf("6. Logout\n");
                printf("\nEnter your choice: ");
                scanf("%d",&choice);

                switch(choice)
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
        else
        {
            printf("Invalid username or password\n");
        }
    }
}

int main()
{
    loadUsers();
    loadTransactions();
    while(1)
    {
        int choice;
        printf("\n1. Create account\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                createAccount();
                break;
            case 2:
                userAuthentication();
                break;
            case 3:
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