#include "mycat.h"

void print_file(char* path, arguments* args)
{
    FILE* f = fopen(path, "r");
    if (f == NULL)
    {
        perror("fopen failed");
        exit(1);
    }

    char line[4096];
    int line_number = 0;
    int previous_blank = 0;

    while (fgets(line, sizeof(line), f) != NULL)
    {
        int is_blank = (line[0] == '\n');

        if (args->squeeze_blank && is_blank && previous_blank)
        {
            continue;
        }

        if (args->number_nonblank && !is_blank)
        {
            line_number++;
        }
        else if (args->number_lines)
        {
            line_number++;
        }

        if (args->number_lines || (args->number_nonblank && !is_blank))
        {
            printf("%6d\t", line_number);
        }

        if (args->show_ends)
        {
            int len = strlen(line);
            if (len > 0 && line[len - 1] == '\n')
            {
                line[len - 1] = '$';
                line[len] = '\n';
                line[len + 1] = '\0';
            }
        }

        printf("%s", line);
        previous_blank = is_blank;
    }

    fclose(f);
}
