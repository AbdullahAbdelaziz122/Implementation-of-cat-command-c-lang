#include "mycat.h"

int main(int argc, char** argv)
{
    arguments args = {0};
    parse_arguments(argc, argv, &args);

    for (int i = 0; i < args.files_count; i++)
    {
        print_file(args.files[i], &args);
    }

    free(args.files);
    return 0;
}
