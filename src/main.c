#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 128



typedef struct arguments{

    unsigned int files_count;
    char **files;


    // flags
    int number_lines;        // -n : number all lines
    int number_nonblank;     // -b : number only non-empty lines
    int squeeze_blank;       // -s : squeeze multiple blank lines into one
    int show_ends;           // -E : show '$' at end of each line

}arguments;

void parse_arguments(int argc, char **argv, arguments *args){
    args->files = malloc(argc * sizeof(char *));
    int index = 0;


    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "--help") == 0){
            printf("./main <files> [--help]\n");
            exit(0);
        } else if (argv[i][0] == '-') {

            for(int j = 1; argv[i][j] != '\0'; j++){

                switch (argv[i][j]) {
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
                        // unsupported argument
                        printf("Unknowm flag: -%c\n", argv[i][j]);
                        exit(1);
                }
            }

        }else {
            args-> files[index] = argv[i];
            index += 1;
        }
    }

    args->files_count = index;
}


// deprecated func
int read_file(const char *path, char **buffer){

//     int tmp_capacity = MAX_LEN;
//     int tmp_size = 0;
//     char *tmp = malloc(tmp_capacity * sizeof(char));

//     if(tmp == NULL){
//         perror("malloc failed");
//         exit(1);
//     }



//     FILE *f = fopen(path, "r");
//     if (f == NULL){

//         perror("fopen failed");
//         exit(1);
//     }


//     int size = 0;
//     do{
//         if(tmp_size + MAX_LEN + 1 >= tmp_capacity){
//             tmp_capacity *=2;
//             tmp = realloc(tmp, tmp_capacity * sizeof(char));
//             if(tmp == NULL){
//                 perror("realloc failed");
//                 exit(1);
//             }
//         }

//         size = fread(tmp + tmp_size, sizeof(char) , MAX_LEN, f);
//         tmp_size += size;
//     }while(size > 0);


//     fclose(f);

//     tmp[tmp_size] = '\0';

//     *buffer = tmp;
//     return tmp_size;
    exit(1);
    return 0;
}

void print_file(char *path, arguments *args){

    FILE *f = fopen(path, "r");
    if (f == NULL){
        perror("fopen failed");
        exit(1);
    }

    char line[4096];
    int line_number = 0;
    int pervious_blank = 0; // for -s (sequeeze) flag

    while(fgets(line, sizeof(line), f) != NULL){


        int is_blank = (line[0] == '\n');

        if(args->squeeze_blank && is_blank && pervious_blank){
            continue;
        }

        if (args->number_nonblank && !is_blank){
            line_number ++;
        }else if (args->number_lines) {
            line_number++;
        }

        if(args->number_lines || (args->number_nonblank && !is_blank)){
            printf("%6d\t", line_number);
        }

        if(args->show_ends){
            int len = strlen(line);

            if(len > 0 && line[len - 1] == '\n'){
                line[len - 1] = '$';
                line[len] = '\n';
                line[len + 1] = '\0';
            }
        }


        printf("%s", line);

        pervious_blank = is_blank;

    }

    fclose(f);
}

int main(int argc, char **argv){

    arguments args = {0};
    parse_arguments(argc, argv, &args);


    for (int i = 0; i < args.files_count; i++){

        print_file(args.files[i], &args);

    }

    free(args.files);

    return 0;
}
