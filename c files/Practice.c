/* #include <stdio.h>

#define SIZE 3

char board[SIZE][SIZE];
char currentPlayer;

void initializeBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
    currentPlayer = 'X';
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("---|---|---\n");
    }
    printf("\n");
}

int checkWin() {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return 1;
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return 1;

    return 0;
}

int checkDraw() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ')
                return 0;
        }
    }
    return 1;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void makeMove() {
    int row, col;
    printf("Player %c, enter your move (row and column): ", currentPlayer);
    scanf("%d %d", &row, &col);

    if (row >= 1 && row <= 3 && col >= 1 && col <= 3 && board[row - 1][col - 1] == ' ') {
        board[row - 1][col - 1] = currentPlayer;
    } else {
        printf("Invalid move. Try again.\n");
        makeMove();
    }
}

int main() {
    initializeBoard();
    printBoard();

    while (1) {
        makeMove();
        printBoard();

        if (checkWin()) {
            printf("Player %c wins!\n", currentPlayer);
            break;
        }

        if (checkDraw()) {
            printf("The game is a draw!\n");
            break;
        }

        switchPlayer();
    }

    return 0;
}
 */

/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 100
#define MAX_TRANSACTIONS 100

typedef struct {
    char type[10];
    float amount;
} Transaction;

typedef struct {
    char username[50];
    char password[50];
    float balance;
    Transaction transactions[MAX_TRANSACTIONS];
    int transaction_count;
} User;

User users[MAX_USERS];
int user_count = 0;

void createAccount() {
    if (user_count >= MAX_USERS) {
        printf("User limit reached. Cannot create more accounts.\n");
        return;
    }

    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    users[user_count].balance = 0.0;
    strcpy(users[user_count].username, username);
    strcpy(users[user_count].password, password);
    users[user_count].transaction_count = 0;
    user_count++;

    printf("Account created successfully!\n");
}

int authenticate(char *username, char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i;
        }
    }
    return -1;
}

void deposit(int user_index, float amount) {
    users[user_index].balance += amount;
    strcpy(users[user_index].transactions[users[user_index].transaction_count].type, "Deposit");
    users[user_index].transactions[users[user_index].transaction_count].amount = amount;
    users[user_index].transaction_count++;
    printf("Deposited $%.2f. New balance: $%.2f\n", amount, users[user_index].balance);
}

void withdraw(int user_index, float amount) {
    if (users[user_index].balance < amount) {
        printf("Insufficient balance.\n");
        return;
    }

    users[user_index].balance -= amount;
    strcpy(users[user_index].transactions[users[user_index].transaction_count].type, "Withdrawal");
    users[user_index].transactions[users[user_index].transaction_count].amount = amount;
    users[user_index].transaction_count++;
    printf("Withdrew $%.2f. New balance: $%.2f\n", amount, users[user_index].balance);
}

void viewBalance(int user_index) {
    printf("Current balance: $%.2f\n", users[user_index].balance);
}

void viewTransactionHistory(int user_index) {
    printf("Transaction History for %s:\n", users[user_index].username);
    for (int i = 0; i < users[user_index].transaction_count; i++) {
        printf("%s: $%.2f\n", users[user_index].transactions[i].type, users[user_index].transactions[i].amount);
    }
}

int main() {
    int choice;
    while (1) {
        printf("1. Create Account\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            createAccount();
        } else if (choice == 2) {
            char username[50], password[50];
            printf("Enter username: ");
            scanf("%s", username);
            printf("Enter password: ");
            scanf("%s", password);

            int user_index = authenticate(username, password);
            if (user_index == -1) {
                printf("Invalid username or password.\n");
                continue;
            }

            int user_choice;
            while (1) {
                printf("1. Deposit\n");
                printf("2. Withdraw\n");
                printf("3. View Balance\n");
                printf("4. View Transaction History\n");
                printf("5. Logout\n");
                printf("Enter your choice: ");
                scanf("%d", &user_choice);

                if (user_choice == 1) {
                    float amount;
                    printf("Enter amount to deposit: ");
                    scanf("%f", &amount);
                    deposit(user_index, amount);
                } else if (user_choice == 2) {
                    float amount;
                    printf("Enter amount to withdraw: ");
                    scanf("%f", &amount);
                    withdraw(user_index, amount);
                } else if (user_choice == 3) {
                    viewBalance(user_index);
                } else if (user_choice == 4) {
                    viewTransactionHistory(user_index);
                } else if (user_choice == 5) {
                    break;
                } else {
                    printf("Invalid choice.\n");
                }
            }
        } else if (choice == 3) {
            printf("Exiting program. Goodbye!\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}*/

/* #include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_TRIES 6
#define WORD_LENGTH 100

void print_hangman(int tries) {
    // Simple ASCII representation of Hangman
    switch (tries) {
        case 0: printf("\n\n\n\n\n\n"); break;
        case 1: printf("\n\n\n\n\n_______"); break;
        case 2: printf(" |\n |\n |\n |\n_|______"); break;
        case 3: printf(" _____\n |   |\n |\n |\n |\n_|______"); break;
        case 4: printf(" _____\n |   |\n |   O\n |\n |\n_|______"); break;
        case 5: printf(" _____\n |   |\n |   O\n |   |\n |\n_|______"); break;
        case 6: printf(" _____\n |   |\n |   O\n |  /|\\\n |   |\n_|______"); break;
        default: printf("Invalid number of tries.\n"); break;
    }
}

void display_word(char *word, int word_length, int *guessed) {
    for (int i = 0; i < word_length; i++) {
        if (guessed[i]) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int check_win(int *guessed, int word_length) {
    for (int i = 0; i < word_length; i++) {
        if (!guessed[i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char word[WORD_LENGTH] = "HELLO";
    int word_length = strlen(word);
    int guessed[word_length];
    memset(guessed, 0, sizeof(guessed));

    int tries = 0;
    char guess;

    printf("Welcome to Hangman!\n");

    while (tries < MAX_TRIES) {
        print_hangman(tries);
        display_word(word, word_length, guessed);

        printf("Enter a letter: ");
        scanf(" %c", &guess);
        guess = toupper(guess);

        int correct_guess = 0;
        for (int i = 0; i < word_length; i++) {
            if (word[i] == guess) {
                guessed[i] = 1;
                correct_guess = 1;
            }
        }

        if (!correct_guess) {
            tries++;
        }

        if (check_win(guessed, word_length)) {
            printf("Congratulations! You've guessed the word '%s'!\n", word);
            break;
        }
    }

    if (tries == MAX_TRIES) {
        print_hangman(tries);
        printf("Sorry, you lost! The word was '%s'.\n", word);
    }

    return 0;
} */

/* #include <stdio.h>
#include <math.h>
#include <stdlib.h>

int decimalToBinary(int decimal,char* binary)
{
    int digits, lastDigit, j = 0;
    digits = (int)log10(decimal) + 1;
    lastDigit = decimal % 10;
    while (decimal > 0)
    {
        binary[j++] = lastDigit % 2;
        lastDigit = decimal % 10;
    }
    binary[j] = '\0';
    size_t length = strlen(binary);

    for (int i = (length - 1); i >= 0; i--)
    {
        printf("%d", binary[i]);
    }
    return binary;
}
int main()
{
    int decimal;

    printf("Enter the decimal number: ");
    scanf("%d", &decimal);

    char binary[100] = decimalToBinary(decimal);
    size_t length = strlen(binary);

    for (int i = 0; i < length; i++)
    {
        printf("%d", binary[i]);
    }

    return 0;
} */

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>

enum weekday{
    Sunday=1,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
};
int main()
{
    int num;

    printf("Enter the number: ");
    scanf("%d",&num);

    printf("%s",weekday);

    return 0;
} 