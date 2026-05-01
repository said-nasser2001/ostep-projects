#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }
    int c;
    int count = 0;
    char prev;
    int first = 1;
    for (int i = 1; i < argc; i++)
    {

        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("wzip: cannot open file\n");
            exit(1);
        }

        while ((c = fgetc(fp)) != EOF)
        {
            if (first)
            {
                prev = (char)c;
                count = 1;
                first = 0;
            }
            else if (prev == (char)c)
            {
                count++;
            }
            else
            {
                fwrite(&count, sizeof(int), 1, stdout);
                fwrite(&prev, sizeof(char), 1, stdout);
                count = 1;
                prev = (char)c;
            }
        }
        fclose(fp);
    }
    fwrite(&count, sizeof(int), 1, stdout);
    fwrite(&prev, sizeof(char), 1, stdout);
    return 0;
}