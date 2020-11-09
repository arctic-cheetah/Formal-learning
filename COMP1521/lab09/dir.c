
/*
$ dcc list_directory.c
$ ./a.out .
list_directory.c
a.out
.
..
$
*/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX_LEN 65536


void listFileDir(char *basePath) {
    char pathName[MAX_LEN];

    DIR *dirp = opendir(basePath);
    //base case
    if (dirp == NULL) {
        return;
    }
    struct dirent *de;

    while ((de = readdir(dirp)) != NULL) {
        if (strcmp(de->d_name, ".") && strcmp(de->d_name, "..")) {
            strcpy(pathName, basePath);
            //check if pathname length is too big
            if (strlen(pathName) == (MAX_LEN - 1) ) {
                return;
            }
            strcat(pathName, "/");
            if (strlen(pathName) == (MAX_LEN - 1) ) {
                return;
            }
            strcat(pathName, de->d_name);
            if (strlen(pathName) == (MAX_LEN - 1) ) {
                return;
            }
            printf("Adding: %s\n", pathName);
            listFileDir(pathName);
        }
    }

    closedir(dirp);

}

// list the contents of directories specified as command-line arguments
int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        listFileDir(argv[arg]);
    }
    return 0;
}
