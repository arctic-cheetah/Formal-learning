#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>


#define MAGIC_NUMBER 42

//A function that returns the pathname of the parent
char *copyParent (char *pathName) {
    int len = strlen(pathName);
    char *parent = (char *)calloc(len, sizeof(char));
    int i = 0;
    while (pathName[i] != '/') {
        parent[i] = pathName[i];
        i +=1;
    }
    return parent;
}
//A function that puts the byte into the file
void putByte(uint64_t data, uint64_t *start, uint64_t end, FILE *newFile) {
    int i = 0;
    while (*start < end) {
        uint64_t temp = data >> (8 * i);
        fputc(temp, newFile);
        *start +=1;
        i +=1;
    }
}
//A function that puts the pathName into file
void putPathName (char *pathName, uint64_t *start, uint64_t end,
    FILE *newFile) {
    int i = 0;
    while (*start < end) {
        if (pathName[i] == '\0') {
            printf("test1!\n");
            break;
        }
        fputc(pathName[i], newFile);
        i +=1;
    }
}
//A function that puts content into a file
void putContent(FILE *newFile, FILE *src, uint64_t size) {
    int c = 0;
    while ((c = fgetc(src)) != EOF) {
        fputc(c, newFile);
    }
}

//A helper function to add a file
int addFile (char *pathName, FILE *newFile) {

    FILE *f = fopen(pathName, "r");
    //Fetch the size of the file
    fseek(f, 0, SEEK_END);
    uint64_t size = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint64_t byteCount = 0;


    struct stat info;
    stat(pathName, &info);

    //Place the magic number (1 byte)
    putByte(MAGIC_NUMBER, &byteCount, byteCount + 1, newFile);

    //Place the mode (2 bytes)
    putByte(info.st_mode, &byteCount, byteCount + 2, newFile);

    //Place the length of the file name (8 bytes)
    int name_len = strlen(pathName);
    putByte(name_len, &byteCount, byteCount + 8, newFile);

    //Place the file size (8 bytes)
    putByte(size, &byteCount, byteCount + 8, newFile);

    //Place the file name
    putPathName(pathName, &byteCount, byteCount + name_len, newFile);

    //Place the contents
    putContent(newFile, f, size);

    return 0;
}

//A helper function to add a directory
int addDir (char *pathName, FILE *newFile) {

    uint64_t byteCount = 0;
    struct stat info;
    stat(pathName, &info);

    //Place the magic number (1 byte)
    putByte(MAGIC_NUMBER, &byteCount, byteCount + 1, newFile);

    //Place the mode (2 bytes)
    putByte(info.st_mode, &byteCount, byteCount + 2, newFile);

    //Place the length of the file name (8 bytes)
    int name_len = strlen(pathName);
    putByte(name_len, &byteCount, byteCount + 8, newFile);

    //Place the file size (8 bytes)
    putByte(0, &byteCount, byteCount + 8, newFile);

    //Place the file name
    putPathName(pathName, &byteCount, byteCount + name_len, newFile);

    //Place the contents, 0 bytes for a file

    return 0;
}

//A helper function to add directories
int addDirRecur (char *pathName, FILE *newFile) {
    return 0;
}

int main (int argc, char **argv) {
    FILE *newFile = fopen(argv[1], "w+");
    if (argc == 1) {
        //restore directory tree

    }
    else if (argc == 2) {
        //Save directory tree


        //Could be a file
        //or a folder
        struct stat info;
        stat(argv[2], &info);

        if (info.st_mode & S_IFDIR) {
            //Add the parent directory first

            //Use recursion to add the children

        }
        else {
            //Only add the file and the direct parent directories
            
            addFile(argv[2], newFile);
        }

    }
    fclose(newFile);
}
