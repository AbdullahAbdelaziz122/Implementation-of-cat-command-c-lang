#include "mycat.h"

void print_help(const char* program_name)
{
    printf("\n");
    printf("  ╔═══════════════════════════════════════════════════╗\n");
    printf("  ║                    MYCAT                          ║\n");
    printf("  ║         A Custom 'cat' Implementation             ║\n");
    printf("  ╚═══════════════════════════════════════════════════╝\n\n");

    printf("Usage: %s [OPTIONS] [FILE...]\n", program_name);
    printf("Concatenate FILE(s) to standard output.\n\n");
    printf("Options:\n");
    printf("  -n              Number all output lines\n");
    printf("  -b              Number only non-empty lines\n");
    printf("  -s              Squeeze multiple blank lines into one\n");
    printf("  -E              Display '$' at the end of each line\n");
    printf("  --help          Display this help message and exit\n\n");
    printf("Examples:\n");
    printf("  %s file.txt              Display a single file\n", program_name);
    printf("  %s -n file.txt           Number all lines\n", program_name);
    printf("  %s -nE file1 file2       Number lines and show ends\n",
           program_name);
    printf("  %s --help                Show this help\n", program_name);
}
void parse_arguments(int argc, char** argv, arguments* args)
{
    args->files = malloc(argc * sizeof(char*));
    int index = 0;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
        {
            print_help(argv[0]);
            exit(0);
        }
        else if (argv[i][0] == '-')
        {
            for (int j = 1; argv[i][j] != '\0'; j++)
            {
                switch (argv[i][j])
                {
                case 'n':
                    args->number_lines = 1;
                    break;
                case 'b':
                    args->number_nonblank = 1;
                    break;
                case 's':
                    args->squeeze_blank = 1;
                    break;
                case 'E':
                    args->show_ends = 1;
                    break;
                default:
                    printf("Unknown flag: -%c\n", argv[i][j]);
                    exit(1);
                }
            }
        }
        else
        {
            args->files[index] = argv[i];
            index++;
        }
    }
    args->files_count = index;
}
