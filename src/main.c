#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 128



typedef struct arguments{

unsigned int files_count;
char **files;

}arguments;

void parse_arguments(int argc, char **argv, arguments *args){
    args->files = malloc(argc * sizeof(char *));
    int index = 0;


    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "--help") == 0){
            printf("./main <files> [--help]\n");
            exit(0);
        } else {
            args-> files[index] = argv[i];
            index += 1;
        }
    }

    args->files_count = index;
}


int read_file(char *path, char **buffer){

    int tmp_capacity = MAX_LEN;
    int tmp_size = 0;
    char *tmp = malloc(tmp_capacity * sizeof(char));

    if(tmp == NULL){
        perror("malloc failed");
        exit(1);
    }



    FILE *f = fopen(path, "r");
    if (f == NULL){

        perror("fopen failed");
        exit(1);
    }


    int size = 0;
    do{
        if(tmp_size + MAX_LEN + 1 >= tmp_capacity){
            tmp_capacity *=2;
            tmp = realloc(tmp, tmp_capacity * sizeof(char));
            if(tmp == NULL){
                perror("realloc failed");
                exit(1);
            }
        }

        size = fread(tmp + tmp_size, sizeof(char) , MAX_LEN, f);
        tmp_size += size;
    }while(size > 0);


    fclose(f);

    tmp[tmp_size] = '\0';

    *buffer = tmp;
    return tmp_size;
}

int main(int argc, char **argv){

    int size_of_file =0;
    arguments args = {0};
    parse_arguments(argc, argv, &args);


    for (int i = 0; i < args.files_count; i++){

        char *buffer = NULL;
        size_of_file = read_file(args.files[i], &buffer);

        printf("%s\n", buffer);
        printf("file size: %d\n", size_of_file);

        free(buffer);

    }
    free(args.files);

    return 0;
}
