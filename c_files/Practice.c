#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *bird_code(const char *name)
{
    char *result = (char *)malloc(sizeof(char) * strlen(name) + 1);
    if (name == NULL)
    {
        perror("File opening unsuccessfull");
        exit(1);
    }
    int wordCount = 1, j = 0;
    for (int i = 0; i < strlen(name); i++)
    {
        if (name[i] == ' ')
        {
            wordCount++;
        }
    }
    if (wordCount == 1)
    {
        for (int i = 0; i < 4; i++)
        {
            result[j++] = name[i];
        }
    }
    else if (wordCount == 2)
    {
        result[j++] = name[0];
        for (int i = 0; i < strlen(name); i++)
        {
            result[j++] = name[strcspn(name, " ") + 1];
        }
    }
    else if (wordCount = 3)
    {
        result[j++] = name[0];
        for (int i = 0; i < strlen(name); i++)
        {
            int count = 0, position;
            if (name[i] == ' ')
            {
                count++;
            }
            if(count==1)
            {
                position=i+1;
            }
            result[j++]=name[position];
            if (count == 2)
            {
                position = i + 1;
            }
            result[j++] = name[position];
        }
    }
    else if (wordCount == 4)
    {
        result[j++] = name[0];
        for (int i = 0; i < strlen(name); i++)
        {
            int count = 0, position;
            if (name[i] == ' ')
            {
                count++;
            }
            if (count == 1)
            {
                position = i + 1;
            }
            result[j++] = name[position];
            if (count == 2)
            {
                position = i + 1;
            }
            result[j++] = name[position];
            if (count == 3)
            {
                position = i + 1;
            }
            result[j++] = name[position];
        }
    }
    result[j] = '\0';
    return result;
}

int main()
{
    char str[30],*code;

    printf("Enter a string: ");
    fgets(str, 30, stdin);

    code = bird_code(str);

    printf("%s\n", code);

    return 0;
}