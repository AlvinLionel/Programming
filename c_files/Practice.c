void deleteUser(char *username)
{
    FILE *file = fopen("../Others/Users.txt", "r+");
    if (file == NULL)
    {
        perror("File opening unsuccessfull");
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize);
    if (buffer == NULL)
    {
        perror("Memory allocation failed");
        fclose(file);
        exit(1);
    }

    long writePos = 0;
    while (fgets(buffer, fileSize, file) != NULL)
    {
        if (strstr(buffer, username) == NULL)
        {
            fseek(file, writePos, SEEK_SET);
            fputs(buffer, file);
            writePos = ftell(file);
        }
    }
    _chsize(fileno(file), writePos);

    userCount--;
    saveUsers();

    fclose(file);
    free(buffer);
}

void deleteTransactions(char *username)
{
    FILE *file = fopen("../Others/Transactions.txt", "r+");
    if (file == NULL)
    {
        perror("File opening unsuccessfull");
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize);
    if (buffer == NULL)
    {
        perror("Memory allocation failed");
        fclose(file);
        exit(1);
    }
    long writePos = 0;
    while (fgets(buffer, fileSize, file) != NULL)
    {
        if (strstr(buffer, username) == NULL)
        {
            fseek(file, writePos, SEEK_SET);
            fputs(buffer, file);
            writePos = ftell(file);
        }
    }
    _chsize(fileno(file), writePos);

    transactionCount--;
    saveTransactions();

    fclose(file);
    free(buffer);
}