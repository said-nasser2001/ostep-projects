#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    char *pattern = argv[1];
    char buffer[1024];

    if (argc == 2)
    {
        while (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            if (strstr(buffer, pattern) != NULL)
            {
                printf("%s", buffer);
            }
        }
        return 0;
    }

    for (int i = 2; i < argc; i++)
    {

        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("wgrep: cannot open file\n");
            exit(1);
        }

        while (fgets(buffer, sizeof(buffer), fp) != NULL)
        {
            if (strstr(buffer, pattern) != NULL)
            {
                printf("%s", buffer);
            }
        }

        fclose(fp);
    }

    return 0;
}