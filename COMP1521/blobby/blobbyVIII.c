// blobby.c
// blob file archiver
// COMP1521 20T3 Assignment 2
// Written by <YOUR NAME HERE>
//MKVII: Utilised xz correctly-- But have not implemented -c -z


//TODO
//Perform error checking for all file functions
//Consider edge cases for length name of files!
//Remove debugging output

//BUG!
//max file size is 6 bytes, need to change byte count to uint64_t
//Check for file permissions when using fopen
//We cannot have a forward slash '/' at the end of our directory!


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <spawn.h>
#include <sys/wait.h>

// the first byte of every blobette has this value
#define BLOBETTE_MAGIC_NUMBER          0x42

// number of bytes in fixed-length blobette fields
#define BLOBETTE_MAGIC_NUMBER_BYTES    1
#define BLOBETTE_MODE_LENGTH_BYTES     3
#define BLOBETTE_PATHNAME_LENGTH_BYTES 2
#define BLOBETTE_CONTENT_LENGTH_BYTES  6
#define BLOBETTE_HASH_BYTES            1

// maximum number of bytes in variable-length blobette fields
#define BLOBETTE_MAX_PATHNAME_LENGTH   65535
#define BLOBETTE_MAX_CONTENT_LENGTH    281474976710655


// ADD YOUR #defines HERE
#define BYTE 8
#define EXTRACT 0xFF
#define MAX_PATHNAME_LEN 65536
#define CHECK_DIR 0x4000
#define MAX_FILE_SIZE 0xFFFFFF

typedef enum action {
    a_invalid,
    a_list,
    a_extract,
    a_create
} action_t;


void usage(char *myname);
action_t process_arguments(int argc, char *argv[], char **blob_pathname,
                           char ***pathnames, int *compress_blob);

void list_blob(char *blob_pathname);
void extract_blob(char *blob_pathname);
void create_blob(char *blob_pathname, char *pathnames[], 
                int compress_blob);

uint8_t blobby_hash(uint8_t hash, uint8_t byte);


// ADD YOUR FUNCTION PROTOTYPES HERE
//Subset 0 functions
uint64_t fetchByte (uint64_t begin, uint64_t end, FILE *f);
void checkMagicNum (FILE *f);
char *fetchFileName (uint64_t begin, uint64_t end, FILE *f, char *s);
void checkBlobHash (FILE *f, uint64_t begin, uint64_t end, uint8_t h);

//Subset 1/2 functions
int putContent (FILE *f, FILE *newBlob, int size, uint64_t *byteCount);
int putFields (FILE *newBlob, int size, int64_t data, uint64_t *byteCount);
int putPathName (FILE *newBlob, char *s, uint64_t *byteCount);
uint8_t fetchHash (FILE *newBlob, uint64_t begin ,uint64_t byteCount);
int isInDir(char *pathName);

//Functions for subset 03
char *getDir (int begin, int end, char *name);
int addDirToBlob (char *dir, uint64_t *byteCount,
         uint64_t *beginBobblet, FILE *newBlob);
int addFileToBlob (char *dir, uint64_t *byteCount,
         uint64_t *beginBobblet, FILE *newBlob);
void addRecurToBlob (char *basePath, uint64_t *byteCount,
         uint64_t *beginBobblet, FILE * newBlob);
int addParent (int numBackSlash, char *pathName, FILE *newBlob,
         uint64_t *byteCount, uint64_t *beginBobblet);
void cleanPathName (char *name);

//Subset 04 helper functions
int isXZ(char *file);
char *decompressFile(char *text, uint64_t *blobSize);
void list_blob_not_compressed(char *blob_pathname);
void list_blob_compressed(char *blob_pathname);
uint64_t print_file(char *file, uint64_t size);
uint64_t fetchByteArray (uint64_t *begin, uint64_t end, char *f);
void checkMagicNumArray (char *f, uint64_t *index);
char *fetchFileNameArray(uint64_t *begin, uint64_t end, char *f, char *s);
void extract_blob_not_compressed(char *blob_pathname);
void extract_blob_compressed(char *blob_pathname);
void checkBlobHashArray (char *f, uint64_t begin, 
                    uint64_t end, uint8_t h);
uint64_t copyContentArray (uint64_t *begin, uint64_t end, 
                           uint64_t offset, char *f);
void compressFile(char *text, FILE *newBlob, char * blob_pathname);

// YOU SHOULD NOT NEED TO CHANGE main, usage or process_arguments

int main(int argc, char *argv[]) {
    char *blob_pathname = NULL;
    char **pathnames = NULL;
    int compress_blob = 0;
    action_t action = process_arguments(argc, argv, &blob_pathname, &pathnames,
                                        &compress_blob);

    switch (action) {
    case a_list:
        list_blob(blob_pathname);
        break;

    case a_extract:
        extract_blob(blob_pathname);
        break;

    case a_create:
        create_blob(blob_pathname, pathnames, compress_blob);
        break;

    default:
        usage(argv[0]);
    }

    return 0;
}

// print a usage message and exit

void usage(char *myname) {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "\t%s -l <blob-file>\n", myname);
    fprintf(stderr, "\t%s -x <blob-file>\n", myname);
    fprintf(stderr, "\t%s [-z] -c <blob-file> pathnames [...]\n", myname);
    exit(1);
}

// process command-line arguments
// check we have a valid set of arguments
// and return appropriate action
// *blob_pathname set to pathname for blobfile
// *pathname and *compress_blob set for create action

action_t process_arguments(int argc, char *argv[], char **blob_pathname,
                           char ***pathnames, int *compress_blob) {
    extern char *optarg;
    extern int optind, optopt;
    int create_blob_flag = 0;
    int extract_blob_flag = 0;
    int list_blob_flag = 0;
    int opt;
    while ((opt = getopt(argc, argv, ":l:c:x:z")) != -1) {
        switch (opt) {
        case 'c':
            create_blob_flag++;
            *blob_pathname = optarg;
            break;

        case 'x':
            extract_blob_flag++;
            *blob_pathname = optarg;
            break;

        case 'l':
            list_blob_flag++;
            *blob_pathname = optarg;
            break;

        case 'z':
            (*compress_blob)++;
            break;

        default:
            return a_invalid;
        }
    }

    if (create_blob_flag + extract_blob_flag + list_blob_flag != 1) {
        return a_invalid;
    }

    if (list_blob_flag && argv[optind] == NULL) {
        return a_list;
    } else if (extract_blob_flag && argv[optind] == NULL) {
        return a_extract;
    } else if (create_blob_flag && argv[optind] != NULL) {
        *pathnames = &argv[optind];
        return a_create;
    }

    return a_invalid;
}


// list the contents of blob_pathname
// REPLACE WITH YOUR CODE FOR -l

void list_blob(char *blob_pathname) {

    //Check if the file is XZ
    if (isXZ(blob_pathname)) {
        //printf("XZ FILE!\n");
        list_blob_compressed(blob_pathname);
    }
    //Dealing with an ordinary file
    else {
        list_blob_not_compressed(blob_pathname);
    }

}


// extract the contents of blob_pathname
void extract_blob(char *blob_pathname) {
    //Check if the file is xz
    if (isXZ(blob_pathname)) {
        //printf("XZ FILE!\n");
        extract_blob_compressed(blob_pathname);
    }
    //If dealing with an ordinary file
    //then extract normally
    else {
        extract_blob_not_compressed(blob_pathname);
    }
}

// create blob_pathname from NULL-terminated array pathnames
// compress with xz if compress_blob non-zero (subset 4)

void create_blob(char *blob_pathname, char *pathnames[], int compress_blob) {

	//Create a new blob
	FILE *newBlob = fopen(blob_pathname, "w+");
    if (newBlob == NULL) {
        fprintf(stderr, "File was NULL\n");
        exit(1);
    }

	uint64_t byteCount = 0;
    uint64_t beginBobblet = 0;
    for (int p = 0; pathnames[p]; p +=1) {

        beginBobblet = byteCount;

        cleanPathName(pathnames[p]);

    	struct stat pathName;
    	//Extract the permissions of the file
    	if (stat(pathnames[p], &pathName) ) {
    		fprintf(stderr, "There was an issue with the filename\n");
    		exit(1);
    	}
        //If the file is under a directory
        //Only add the parent directories/directory to the blob
        int numBackSlash = isInDir(pathnames[p]);
        if (numBackSlash) {
            addParent(numBackSlash, pathnames[p], newBlob,
                &byteCount, &beginBobblet);
        }

        //We are dealing with a directory
        //use recursion
        if (S_ISDIR(pathName.st_mode)) {
            addDirToBlob(pathnames[p], &byteCount, &beginBobblet, newBlob);
            addRecurToBlob(pathnames[p], &byteCount, &beginBobblet, newBlob);
        }
        //Dealing with a file
        else {
            addFileToBlob(pathnames[p], &byteCount, &beginBobblet, newBlob);
        }
    }

    //Check if compression is desired
    if (compress_blob) {
        //Create a buffer
        uint64_t size = ftell(newBlob);
        char *buffer = (char *)calloc(size + 1, sizeof(char));
        fseek(newBlob, 0, SEEK_SET);
        //Put the contents into stdin
        int c = 0;
        int j = 0;
        while ((c = fgetc(newBlob)) != EOF) {
            buffer[j] = c;
            j +=1;
        }
        //buffer[j] = EOF;
        fseek(newBlob, 0, SEEK_SET);
        

        compressFile(buffer, newBlob, blob_pathname);
    }
    fclose(newBlob);
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//My functions:

//A recursive function which adds a file or directory to a blob
//With code adapted from the COMP1521 week08 slides
//on mkdir

//WARNING
//There's a bug, readdir can only read a max of 256 characters.
//It will break if the name of the file/directory exceeds 256 chars

//CONSOLATION;
//ANDREW reassured that stat will work
void addRecurToBlob (char *basePath, uint64_t *byteCount,
                uint64_t *beginBobblet, FILE * newBlob) {

    char pathName[MAX_PATHNAME_LEN];
    DIR *dirp = opendir(basePath);
    struct stat pN;
    //printf("%s\n", basePath);

    if (stat(basePath, &pN) ) {
        fprintf(stderr, "There was an issue with the filename\n");
        exit(1);
    }

    //base case
    if (!dirp) {
        return;
    }
    struct dirent *de;
    //Recursive case
    while ((de = readdir(dirp)) != NULL) {
        
        //Exclude the parent or current directory
        if (strcmp(de->d_name, ".") && strcmp(de->d_name, "..")) {
            //check if pathname length is too big
            //printf("Looking at: %s\n", de->d_name);
            //int check = strlen(pathName) + strlen(basePath);
            /*
            if (check == (MAX_PATHNAME_LEN - 1) ) {
                return;
            }
            */
            strcpy(pathName, basePath);
            /*
            check = strlen(pathName) + 1;
            if (check == (MAX_PATHNAME_LEN - 1) ) {
                return;
            }
            */
            strcat(pathName, "/");
            /*
            check = strlen(pathName) + strlen(de->d_name);
            if (strlen(pathName) == (MAX_PATHNAME_LEN - 1) ) {
                return;
            }
            */
            strcat(pathName, de->d_name);

            //Check if the object is a directory
            if (de->d_type == DT_DIR) {
                addDirToBlob(pathName, byteCount, beginBobblet, newBlob);
            }
            else {
                addFileToBlob(pathName, byteCount, beginBobblet, newBlob);
            }
            addRecurToBlob(pathName, byteCount, beginBobblet, newBlob);
        }
    }
}

//A function that obtains each byte given a range from a file
uint64_t fetchByte (uint64_t begin, uint64_t end, FILE *f) {
	uint64_t data = 0;
	uint64_t c = 0;
	int j = end - begin;
	for (int i = begin; i <= end; i +=1) {
    	c = fgetc(f);
        //printf("%lx ", c);
    	c = c << (j * BYTE);
    	data = data | c;
    	j -=1;
    }
    return data;
}


//A function which checks whether a byte is a magic number
void checkMagicNum (FILE *f) {
	uint32_t c = fgetc(f);
    //Check for magic number
    if (c != BLOBETTE_MAGIC_NUMBER) {
    	fprintf(stderr, "ERROR: Magic byte of blobette incorrect\n");
    	exit(1);
    }
}

//A function that obtains each char given a range from a file
//and returns a string
char *fetchFileName (uint64_t begin, uint64_t end, FILE *f, char *s) {
	uint64_t c = 0;
	int j = 0;
	for (int i = begin; i <= end; i +=1) {
    	c = fgetc(f);
    	s[j] = c;
    	j +=1;
    }
    //Null terminate the string for printf
    s[j - 1] = '\0';
    return s;
}

//A function which the hash value of a blobette
void checkBlobHash (FILE *f, uint64_t begin, uint64_t end, uint8_t h) {
	//Set the file pointer to the beginning
	fseek(f, begin, SEEK_SET);
	uint8_t hash = 0;
    //Check for the magic number

    for (uint64_t i = begin; i < end; i +=1) {
    	hash = blobby_hash(hash, fgetc(f));
    }
    //printf("Evaluated: %d, From file: %d\n", hash, h);

    if (hash != h) {
    	fprintf(stderr, "ERROR: blob hash incorrect\n");
    	exit(1);
    }
    //Restore the original position of the pointer
}


//A function that places the fields into a blob using big endian format
int putFields (FILE *newBlob, int size, int64_t data, uint64_t *byteCount) {
    int *info = malloc(size * sizeof(int));
    int i = size - 1;
    //Decompose the bytes
    //to get the bytes from the file
	for (int j = 0; j < size; j +=1) {
        uint64_t c = data;
        c = c >> (j * BYTE);
        c = c & 0xFF;
        info[i] = c;
        //printf("%x ", info[i]);
        i -=1;
	}
    //printf("Data: %lo, %lx\n", data, data);

    //Put the byte into the blob
    for (int j = 0; j < size; j +=1) {
        fputc(info[j], newBlob);
        *byteCount +=1;
	}
    //printf("The byte count is: %d\n", *byteCount);
    free(info);
    return 1;
}

//A function that puts the contents into a blob using big endian format
int putContent (FILE *f, FILE *newBlob, int size, uint64_t *byteCount) {
    int *info = malloc(size * sizeof(int));

	for (int j = 0; j < size; j +=1) {
        //get the bytes from the file
        info[j] = fgetc(f);
	}

    //Place the bytes into the blob
    for (int j = 0; j < size; j +=1) {
        fputc(info[j], newBlob);
        *byteCount +=1;
	}
    free(info);
    return 1;
}
//A function that places the pathname in the blob with big endian format
int putPathName (FILE *newBlob, char *s, uint64_t *byteCount) {
    int i = 0;
    while (s[i] != '\0') {
        fputc(s[i], newBlob);
        *byteCount +=1;
        i +=1;
    }
    return 1;
}

//A function which calculates a hash key
uint8_t fetchHash (FILE *newBlob, uint64_t begin ,uint64_t byteCount) {
    uint8_t hash = 0;
    for (int i = begin; i < byteCount; i +=1) {
        hash = blobby_hash(hash, (uint8_t)fgetc(newBlob));
    }
    //printf("hash: %d\n", hash);
    return hash;
}

//This function assumes it is looking at a file!
//It checks if a file is under a directory
//by checking for "/"
//By the definition from the C standard, a string must be terminated
//with a '\0'
//Returns the number of "/"
int isInDir (char *pathName) {
    int i = 0;
    int backSlashCount = 0;
    while (pathName[i] != '\0') {
        if (pathName[i] == '/') {
            backSlashCount +=1;
        }
        i +=1;
    }
    return backSlashCount;
}

//A function that returns string of the parent directory
// given that the file has a parent directory
char *getDir (int begin, int end, char *name) {
    int i = 0;
    int sLen = strlen(name) + 1;
    //Move the counter up to the nth backslash
    while (begin < end && i < sLen) {
        if (name[i] == '/') {
            begin +=1;
        }
        i +=1;
    }
    //Copy the string up to the nth backslash and null terminate it
    char *dir = malloc(sizeof(char) * (i));
    int j = 0;
    for (; j < i; j +=1) {
        dir[j] = name[j];
    }
    dir[j - 1] = '\0';
    //printf("%s\n", dir);
    return dir;
}
//A function that only adds directories to the blob
int addDirToBlob (char *dir, uint64_t *byteCount,
    uint64_t *beginBobblet, FILE *newBlob) {


    struct stat pathName;
    if (stat(dir, &pathName) ) {
        fprintf(stderr, "There was an issue with the filename\n");
        exit(1);
    }
    //Add the magic number
    fputc(BLOBETTE_MAGIC_NUMBER, newBlob);
    *byteCount +=1;

    putFields (newBlob, BLOBETTE_MODE_LENGTH_BYTES,
             pathName.st_mode, byteCount);
    //Fetch the length of the directory name
    uint64_t pathname_length = strlen(dir);
    //Deconstruct the dir name into bytes using big endian format
    putFields (newBlob, BLOBETTE_PATHNAME_LENGTH_BYTES,
             pathname_length, byteCount);

    //The size of the contents of a directory is 0
    putFields (newBlob, BLOBETTE_CONTENT_LENGTH_BYTES,
             0, byteCount);
    //Deconstruct the content size into bytes using big endian format

    //Place the name of the dir in the blob
    putPathName(newBlob, dir, byteCount);
//////////////////////////////////////////////////////////////////////
///

    //Set the blob file pointer to the beginning of the bobblet
    fseek(newBlob, *beginBobblet, SEEK_SET);
    //printf("beginBobblet: %lu\n", beginBobblet);

    //Calculate the hash key and add it to the end of the file
    uint8_t hash = fetchHash(newBlob, *beginBobblet, *byteCount);
    fseek(newBlob, *byteCount, SEEK_SET);
    putFields(newBlob, BLOBETTE_HASH_BYTES, hash, byteCount);

    *beginBobblet = *byteCount;
    printf("Adding: %s\n", dir);
    return 1;
}

//A function that only adds files to the blob
int addFileToBlob (char *fileName, uint64_t *byteCount,
    uint64_t *beginBobblet, FILE *newBlob) {


    struct stat pathName;
    if (stat(fileName, &pathName) ) {
        fprintf(stderr, "There was an issue with the filename\n");
        exit(1);
    }

    FILE *f = fopen(fileName, "r");
    if (f == NULL) {
        perror("Error:");
        exit(1);
    }
    //Set a new magic number
    fputc(BLOBETTE_MAGIC_NUMBER, newBlob);
    *byteCount +=1;

    //Deconstruct the permissions into bytes
    putFields (newBlob, BLOBETTE_MODE_LENGTH_BYTES,
             pathName.st_mode, byteCount);
    //Fetch the length of the file name
    uint64_t pathname_length = strlen(fileName);
    //Deconstruct the file name into bytes using big endian format
    putFields (newBlob, BLOBETTE_PATHNAME_LENGTH_BYTES,
             pathname_length, byteCount);

    //Fetch the size of the content
    uint64_t content_length = pathName.st_size;
    putFields (newBlob, BLOBETTE_CONTENT_LENGTH_BYTES,
             content_length, byteCount);
    //Deconstruct the content size into bytes using big endian format

    //Place the name of the file in the blob
    putPathName(newBlob, fileName, byteCount);
//////////////////////////////////////////////////////////////////////
///

    //Transfer the contents of the file into the blob
    putContent(f, newBlob, content_length, byteCount);

    //Set the blob file pointer to the beginning of the bobblet
    fseek(newBlob, *beginBobblet, SEEK_SET);
    //printf("beginBobblet: %lu\n", beginBobblet);

    //Calculate the hash key and add it to the end of the file
    uint8_t hash = fetchHash(newBlob, *beginBobblet, *byteCount);
    fseek(newBlob, *byteCount, SEEK_SET);
    putFields(newBlob, BLOBETTE_HASH_BYTES, hash, byteCount);

    //printf("ByteCount: %d\n", byteCount);
    printf("Adding: %s\n", fileName);
    *beginBobblet = *byteCount;
    fclose(f);
    return 1;
}

//A function that adds the parent directories to the blob
int addParent (int numBackSlash, char *pathName, FILE *newBlob,
    uint64_t *byteCount, uint64_t *beginBobblet) {
    int i = 0;
    while (i < numBackSlash) {
        char *dir = getDir(0, i + 1, pathName);
        addDirToBlob(dir, byteCount, beginBobblet, newBlob);
        free(dir);
        i +=1;
    }
    return 1;
}

//A function which removes any backslash at the end of a pathname
void cleanPathName (char *name) {
    int length = strlen(name);
    //Check if the 2nd last character is a forward slash '/'
    if (name[length - 1] == '/') {
        name[length - 1] = '\0';
    }
}

//A function that checks if the compressed file is a xz
//Returns 1 if the file is xz
int isXZ(char *file) {
    FILE *f = fopen(file, "r");
    const uint8_t XZ_FILE_ID[6]
                    = { 0xFD, '7', 'z', 'X', 'Z', 0x00 };
    
    uint8_t file_id[6] = {0};

    //get the magic number from the file
    for (int i = 0; i < 6; i +=1) {
        file_id[i] = fgetc(f);
    }
    fclose(f);
    //Check if the file number is a xz
    for (int i = 0; i < 6; i +=1) {
        //Return 0 if false
        if (file_id[i] != XZ_FILE_ID[i]) {
            return 0;
        }
    }
    //return 1 if true
    return 1;
}

char *decompressFile(char *text, uint64_t *blobSize) {
    // create a pipe
    int pipe_file_descriptors[2];
    if (pipe(pipe_file_descriptors) == -1) {
        perror("pipe");
        exit(1);
    }

    // create a list of file actions to be carried out on spawned process
    posix_spawn_file_actions_t actions;
    if (posix_spawn_file_actions_init(&actions) != 0) {
        perror("posix_spawn_file_actions_init");
        exit(1);
    }

    // tell spawned process to close unused read end of pipe
    // without this - spawned process would not receive EOF
    // when read end of the pipe is closed below,
    if (posix_spawn_file_actions_addclose(&actions, pipe_file_descriptors[0]) != 0) {
        perror("posix_spawn_file_actions_init");
        exit(1);
    }

    // tell spawned process to replace file descriptor 1 (stdout)
    // with write end of the pipe
    if (posix_spawn_file_actions_adddup2(&actions, pipe_file_descriptors[1], 1) != 0) {
        perror("posix_spawn_file_actions_adddup2");
        exit(1);
    }

    pid_t pid;
    extern char **environ;
    char *xz[] = {"xz", "-dc", text, NULL};
    if (posix_spawn(&pid, "/usr/bin/xz", &actions, NULL, xz, environ) != 0) {
        perror("spawn");
        exit(1);
    }

    // close unused write end of pipe
    // in some case processes will deadlock without this
    // not in this case, but still good practice
    close(pipe_file_descriptors[1]);

    // create a stdio stream from read end of pipe
    FILE *f = fdopen(pipe_file_descriptors[0], "r");
    if (f == NULL) {
        perror("fdopen");
        exit(1);
    }

    // read a line from read-end of pipe
    char *line = malloc(MAX_FILE_SIZE * sizeof(char));
    int c = 0;
    int i = 0;
    while ((c = fgetc(f)) != EOF) {
        //printf("%c", c);
        line[i] = c;
        i +=1;
        *blobSize +=1;
    }
    line[i + 1] = EOF;

    // close read-end of the pipe
    // spawned process will now receive EOF if attempts to read input
    fclose(f);

    int exit_status;
    if (waitpid(pid, &exit_status, 0) == -1) {
        perror("waitpid");
        exit(1);
    }

    // free the list of file actions
    posix_spawn_file_actions_destroy(&actions);

    return line;
}

//A helper function to list the bytes of the file
void list_blob_not_compressed(char *blob_pathname) {

    FILE *f1 = fopen(blob_pathname, "r");
    if (f1 == NULL) {
    	perror("");
    	exit(1);
    }

    FILE *size = fopen(blob_pathname, "r");
    if (size == NULL) {
    	perror("");
        exit(1);
    }

    fseek(size, 0, SEEK_END);
    long blobSize = ftell(size);
    //printf("The blob size is: %ld\n", blobSize);
    uint64_t i = 1;
    uint64_t offset0 = 0;
    while (i < blobSize - 1) {
		//Fetch the bytes for each blob field
		//and calculate each offset
		checkMagicNum(f1);

		uint64_t mode = fetchByte(i, i + 2, f1);
		uint64_t offset1 = (i + 2) + 1;
		//printf("offset1: %lu\n", offset1);
		uint64_t pathname_length = fetchByte(offset1, offset1 + 1, f1);
		if (pathname_length < 1 ||
				pathname_length > BLOBETTE_MAX_PATHNAME_LENGTH) {
			fprintf(stderr, "The length of the pathname was too long\n");
			exit(1);
		}
		uint64_t offset2 = (offset1 + 1);
		//printf("offset2: %lu\n", offset2);
		uint64_t content_length = fetchByte(offset2, offset2 + 5, f1);
		if (content_length < 0 ||
				pathname_length > BLOBETTE_MAX_CONTENT_LENGTH) {
			fprintf(stderr, "The size of the content was too large\n");
			exit(1);
		}
		uint64_t offset3 = (offset2 + 6) + 1;
		//printf("offset3: %lu\n", offset3);

		//Allocate memory for the length of the string
		char *pathName = malloc((pathname_length + 1) * sizeof(char));
		fetchFileName(offset3, offset3 + pathname_length, f1, pathName);
		printf("%06lo %5lu %s\n", mode, content_length, pathName);
		free(pathName);

		//calculate the offset for the file
		//and set the file pointer in the correct position
		i = offset3 + offset0 + pathname_length + content_length;
		if ( fseek(f1, i, SEEK_SET) == -1 ) {
			fprintf(stderr, "Error with getting file pointer\n");
			exit(1);
		}

		//printf("count is: %lu & %lu\n", i, ftell(f1));

		//Check if EOF is reached
		//to avoid offset issues
		if (fgetc(f1) != EOF) {
			i += 1;
			offset0 = 1;
			fseek(f1, 0, SEEK_SET);
			fseek(f1, i, SEEK_CUR);
			//printf("count is: %lu & %lu\n", i, ftell(f1));
		}
		else {
			offset0 = 0;
		}
    }

    fclose(size);
    fclose(f1);
} 

void list_blob_compressed(char *blob_pathname) {
    //Uncompress the file & get the size of the file
    uint64_t blobSize = 0;
    char *f1 = decompressFile(blob_pathname, &blobSize);
    //printf("\n\n");
    
    //printf("The blob size is: %ld\n", blobSize);
    uint64_t i = 0;
    while (i < blobSize - 1) {
        //Fetch the bytes for each blob field
        //and calculate each offset
        checkMagicNumArray(f1, &i);

        uint64_t mode = fetchByteArray(&i, i + 2, f1);
        //printf("offset1: %lu 0x%lx\n", i, mode);
        uint64_t pathname_length = fetchByteArray(&i, i + 1, f1);
        if (pathname_length < 1 ||
                pathname_length > BLOBETTE_MAX_PATHNAME_LENGTH) {
            fprintf(stderr, "The length of the pathname was too long\n");
            exit(1);
        }
        //printf("offset2: %lu\n", offset2);
        uint64_t content_length = fetchByteArray(&i, i + 5, f1);
        if (content_length < 0 ||
                pathname_length > BLOBETTE_MAX_CONTENT_LENGTH) {
            fprintf(stderr, "The size of the content was too large\n");
            exit(1);
        }
        //printf("offset3: %lu\n", i);

        //Allocate memory for the length of the string
        char *pathName = malloc((pathname_length + 1) * sizeof(char));
        fetchFileNameArray(&i, i + pathname_length, f1, pathName);
        printf("%06lo %5lu %s\n", mode, content_length, pathName);
        free(pathName);

        //calculate the offset for the array
        i = i + content_length;
        //printf("count is: %lu\n", i);
    }
}

uint64_t print_file(char *file, uint64_t size) {
    uint64_t i = 0;
    while (i < size) {
        printf("%c", file[i]);
        i +=1;
    }
    return i;
}

//A function that obtains each byte given a range from an array
uint64_t fetchByteArray (uint64_t *begin, uint64_t end, char *f) {
    uint64_t data = 0;
	uint64_t c = 0;
	int j = end - *begin;
	for (int i = *begin; i <= end; i +=1) {
    	c = (EXTRACT & f[i]);
    	c = c << (j * BYTE);
    	data = data | c;
    	j -=1;
        *begin +=1;
    }
    return data;
}

//A function that checks the magic number of the file in the array
void checkMagicNumArray (char *f, uint64_t *index) {
    if (f[*index] != BLOBETTE_MAGIC_NUMBER) {
        fprintf(stderr, "ERROR: Magic byte of blobette incorrect\n");
    	exit(1);
    }
    *index +=1;
}
//A function that obtains each char given a range from an array
//and returns a string
char *fetchFileNameArray(uint64_t *begin, uint64_t end, char *f, char *s){
    uint64_t c = 0;
	int j = 0;
	for (int i = *begin; i <= end; i +=1) {
    	c = f[i];
    	s[j] = c;
    	j +=1;
    }
    *begin +=(j);
    //Null terminate the string for printf
    s[j - 1] = '\0';

    return s;
}
//A function that extracts a blob that is not compressed
void extract_blob_not_compressed(char *blob_pathname) {
    FILE *f1 = fopen(blob_pathname, "r");
    if (f1 == NULL) {
    	fprintf(stderr, "The file was NULL!\n");
    	exit(1);
    }

    FILE *size = fopen(blob_pathname, "r");
    if (size == NULL) {
    	fprintf(stderr, "The file was NULL!\n");
    	exit(1);
    }

    fseek(size, 0, SEEK_END);
    long blobSize = ftell(size);
    //printf("The blob size is: %ld\n", blobSize);
    uint64_t i = 1;
    uint64_t offset0 = 0;
    uint64_t hashBegin = 0;
    
    while (i < blobSize - 1) {
		//Fetch the bytes for each blob field
		//and calculate each offset
		checkMagicNum(f1);
		uint64_t mode = fetchByte(i, i + 2, f1);
		uint64_t offset1 = (i + 2) + 1;
		//printf("offset1: %lu\n", offset1);
        
        //Fetch the pathname length
		uint64_t pathname_length = fetchByte(offset1, offset1 + 1, f1);
		if (pathname_length < 1 ||
				pathname_length > BLOBETTE_MAX_PATHNAME_LENGTH) {
			fprintf(stderr, "The length of the pathname was too long\n");
			exit(1);
		}

        //Fetch the length of the content
		uint64_t offset2 = (offset1 + 1);
		//printf("offset2: %lu\n", offset2);
		uint64_t content_length = fetchByte(offset2, offset2 + 5, f1);
		if (content_length < 0 ||
				pathname_length > BLOBETTE_MAX_CONTENT_LENGTH) {
			fprintf(stderr, "The size of the content was too large\n");
			exit(1);
		}

		uint64_t offset3 = (offset2 + 6) + 1;
		//printf("offset3: %lu\n", offset3);
		//Allocate memory for the length of the string
		char *pathName = malloc((pathname_length + 1) * sizeof(char));
		fetchFileName(offset3, offset3 + pathname_length, f1, pathName);
		uint64_t offset4 = offset3 + pathname_length;
		//printf("%lu %lu \n", offset4, i);

        //Offset to the correct position for the new obj
		if (hashBegin) {
			offset4 +=1;
		}
        //Check if the obj is a file or directory
        //By using the mode
        
        //Directory
        if (mode & S_IFDIR) {
            if (!mkdir(pathName, mode)) {
                printf("Creating directory: %s\n", pathName);
            }
            if( chmod(pathName, mode) ) {
                perror("Error2");
                exit(1);
            }
            //Return the position for the file pointer
            i = offset4;
            if ( fseek(f1, offset4, SEEK_SET) == -1 ) {
                fprintf(stderr, "Error with getting file pointer\n");
                exit(1);
            }
        }
        //File
        else {
            printf("Extracting: %s\n", pathName);
            //Create a new file
            FILE *newFile = fopen(pathName, "w+");
            if (!newFile) {
                perror("Error");
                exit(1);
            }

            //Check if the file is in a directory

            //Place the pointer at the correct offset
            if ( fseek(f1, offset4, SEEK_SET) == -1 ) {
                fprintf(stderr, "Error with getting file pointer\n");
                exit(1);
            }


            for (int j = 0; j < content_length; j +=1) {
                //Copy all the contents
                int c = fetchByte(j, j, f1);
                fputc(c, newFile);
                //printf("J is %d: c is %c\n", j, c);
            }

            //Set correct file permissions
            //Perform error checking
            if ( chmod(pathName, mode) == -1 ) {
                fprintf(stderr, "Error with changing permissions\n");
                exit(1);
            }

            fclose(newFile);
            free(pathName);

            //set the file pointer in the correct position
            i = offset3 + offset0 + pathname_length + content_length;
            if ( fseek(f1, i, SEEK_SET) == -1 ) {
                fprintf(stderr, "Error with getting file pointer\n");
                exit(1);
            }
        }
        
        //printf("%s\n", pathName);
        //printf("%lu %lu \n", offset4, i);
        
		//Fetch the hash value
		uint8_t hash = fetchByte(i, i, f1);
        //printf("Hash: %d\n", hash);
		//printf("Hashing begins: %lu and ends at: %lu\n", hashBegin, i);

		//Check the hash value;
		checkBlobHash(f1, hashBegin, i, hash);
		//printf("count is: %lu & %lu\n", i, ftell(f1));

		//Check if EOF is reached
		if (fgetc(f1) != EOF) {
			i += 1;
			offset0 = 1;
			fseek(f1, 0, SEEK_SET);
			fseek(f1, i, SEEK_CUR);
			//printf("count is: %lu & %lu\n", i, ftell(f1));
		}
		else {
			offset0 = 0;
		}
		//Shift the calculation of the hash blobette to the new
		//beginning position
		hashBegin = i;

    }

    fclose(size);
    fclose(f1);
}
//A function that extracts a blob that is compressed
void extract_blob_compressed(char *blob_pathname) {

    uint64_t blobSize = 0;
    char *f1 = decompressFile(blob_pathname, &blobSize);
    //printf("\n\n");
    
    //printf("The blob size is: %ld\n", blobSize);
    uint64_t i = 0;
    uint64_t hashBegin = 0;

    
    while (i < blobSize - 1) {
		//Fetch the bytes for each blob field

		checkMagicNumArray(f1, &i);
		uint64_t mode = fetchByteArray(&i, i + 2, f1);
		//printf("offset1: %lu\n", offset1);
        
        //Fetch the pathname length
		uint64_t pathname_length = fetchByteArray(&i, i + 1, f1);
		if (pathname_length < 1 ||
				pathname_length > BLOBETTE_MAX_PATHNAME_LENGTH) {
			fprintf(stderr, "The length of the pathname was too long\n");
			exit(1);
		}

        //Fetch the length of the content
		//printf("offset2: %lu\n", offset2);
		uint64_t content_length = fetchByteArray(&i, i + 5, f1);
		if (content_length < 0 ||
				pathname_length > BLOBETTE_MAX_CONTENT_LENGTH) {
			fprintf(stderr, "The size of the content was too large\n");
			exit(1);
		}

		//printf("offset3: %lu\n", i);
		//Allocate memory for the length of the string
		char *pathName = malloc((pathname_length + 1) * sizeof(char));
		fetchFileNameArray(&i, i + pathname_length, f1, pathName);
		//printf("%lu \n", i);

        //Check if the obj is a file or directory
        //By using the mode
        
        //Directory
        if (mode & S_IFDIR) {
            if (!mkdir(pathName, mode)) {
                printf("Creating directory: %s\n", pathName);
            }
            if( chmod(pathName, mode) ) {
                perror("Error2");
                exit(1);
            }
            i -=1;
        }
        //File
        else {
            printf("Extracting: %s\n", pathName);
            //Create a new file
            FILE *newFile = fopen(pathName, "w+");
            if (!newFile) {
                perror("Error");
                exit(1);
            }

            //Check if the file is in a directory
            i -=1;
            for (int j = 0; j < content_length; j +=1) {
                //Copy all the contents
                int c = fetchByteArray(&i, i, f1);
                fputc(c, newFile);
                //printf("c is %c\n", c);
            }

            //Set correct file permissions
            //Perform error checking
            if ( chmod(pathName, mode) == -1 ) {
                fprintf(stderr, "Error with changing permissions\n");
                exit(1);
            }

            fclose(newFile);
            free(pathName);
        }
        
        //printf("%s\n", pathName);
        //printf("%lu %lu \n", offset4, i);
        
		//Fetch the hash value
		uint8_t hash = fetchByteArray(&i, i, f1);
        //printf("Hash: %d\n", hash);
        i -=1;
		//printf("Hashing begins: %lu and ends at: %lu\n", hashBegin, i);
        //printf("count is: %lu\n", i);
		//Check the hash value;
		checkBlobHashArray(f1, hashBegin, i, hash);
        i +=1;
		//Shift the calculation of the hash blobette to the new
		//beginning position
		hashBegin = i;

    }

}

//A function that checks the bob hash of the array that 
//holds the file
void checkBlobHashArray (char *f, uint64_t begin, 
                uint64_t end, uint8_t h) 
{
    uint8_t hash = 0;
    //Check for the magic number

    for (uint64_t i = begin; i < end; i +=1) {
        hash = blobby_hash(hash, f[i]);
    }
    //printf("Evaluated: %d, From file: %d\n", hash, h);
    if (hash != h) {
        fprintf(stderr, "ERROR: blob hash incorrect\n");
        exit(1);
    }
}

//A helper function that copies a byte from the contents
//of the array that holds the file beginning from an offset
uint64_t copyContentArray (uint64_t *begin, uint64_t end, 
                           uint64_t offset, char *f) 
{
    uint64_t data = 0;
	uint64_t c = 0;
	for (int i = offset; i <= offset; i +=1) {
    	c = (EXTRACT & f[i]);
    	data = data | c;
        *begin +=1;
    }
    return data;

}

//A function that compresses a file
void compressFile(char *text, FILE *newBlob, char *blob_pathname) {

    //pipe #1 to allow the parent to send data to the child
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    int fd2[2];
    if (pipe(fd2) == -1) {
        perror("pipe2");
        exit(1);
    }

    // create a list of file actions to be carried out on spawned process
    posix_spawn_file_actions_t actions;
    if (posix_spawn_file_actions_init(&actions) != 0) {
        perror("posix_spawn_file_actions_init");
        exit(1);
    }
    // tell spawned process to replace file descriptor 0 (stdin)
    // with read end of the pipe
    if (posix_spawn_file_actions_adddup2(&actions, fd[0], 0) != 0) {
        perror("posix_spawn_file_actions_adddup2");
        exit(1);
    }
    //Close the write end, so we can send data
    if (posix_spawn_file_actions_addclose(&actions, fd[1]) != 0) {
        perror("posix_spawn_file_actions_close");
        exit(1);
    }

    // tell spawned process to replace file descriptor 1 (stdout)
    // with write end of the pipe
    if (posix_spawn_file_actions_adddup2(&actions, fd2[1], 1) != 0) {
        perror("posix_spawn_file_actions_adddup2");
        exit(1);
    }
    //Close the read end, so we can recieve data
    if (posix_spawn_file_actions_addclose(&actions, fd2[0]) != 0) {
        perror("posix_spawn_file_actions_close");
        exit(1);
    }

    
    pid_t pid;
    extern char **environ;
    char *xz[] = {"xz", "--stdout", NULL};
    if (posix_spawn(&pid, "/usr/bin/xz", &actions, NULL, xz, environ) != 0) {
        perror("spawn");
        exit(1);
    }

    close(fd[0]);
    close(fd2[1]);

    FILE *f = fdopen(fd2[0], "r");
    if (f == NULL) {
        perror("fdopen0");
        exit(1);
    }
    FILE *send = fdopen(fd[1], "w");
    if (send == NULL) {
        perror("fdopen0");
        exit(1);
    }
    int j = 0;

    //Send the buffer to xz to process data
    while (text[j] != EOF) {
        fputc(text[j], send);
        j +=1;
    }
    fclose(send);

    //Place the data into the file
    int c = 0;
    while ((c = fgetc(f)) != EOF) {
        fputc(c, newBlob);
    }
    fclose(f);
   
    
    // close read-end of the pipe
    // spawned process will now receive EOF if attempts to read input
    //fclose(f);

    int exit_status;
    if (waitpid(pid, &exit_status, 0) == -1) {
        perror("waitpid");
        exit(1);
    }

    // free the list of file actions
    posix_spawn_file_actions_destroy(&actions);
}



// YOU SHOULD NOT CHANGE CODE BELOW HERE

// Lookup table for a simple Pearson hash
// https://en.wikipedia.org/wiki/Pearson_hashing
// This table contains an arbitrary permutation of integers 0..255

const uint8_t blobby_hash_table[256] = {
    241, 18,  181, 164, 92,  237, 100, 216, 183, 107, 2,   12,  43,  246, 90,
    143, 251, 49,  228, 134, 215, 20,  193, 172, 140, 227, 148, 118, 57,  72,
    119, 174, 78,  14,  97,  3,   208, 252, 11,  195, 31,  28,  121, 206, 149,
    23,  83,  154, 223, 109, 89,  10,  178, 243, 42,  194, 221, 131, 212, 94,
    205, 240, 161, 7,   62,  214, 222, 219, 1,   84,  95,  58,  103, 60,  33,
    111, 188, 218, 186, 166, 146, 189, 201, 155, 68,  145, 44,  163, 69,  196,
    115, 231, 61,  157, 165, 213, 139, 112, 173, 191, 142, 88,  106, 250, 8,
    127, 26,  126, 0,   96,  52,  182, 113, 38,  242, 48,  204, 160, 15,  54,
    158, 192, 81,  125, 245, 239, 101, 17,  136, 110, 24,  53,  132, 117, 102,
    153, 226, 4,   203, 199, 16,  249, 211, 167, 55,  255, 254, 116, 122, 13,
    236, 93,  144, 86,  59,  76,  150, 162, 207, 77,  176, 32,  124, 171, 29,
    45,  30,  67,  184, 51,  22,  105, 170, 253, 180, 187, 130, 156, 98,  159,
    220, 40,  133, 135, 114, 147, 75,  73,  210, 21,  129, 39,  138, 91,  41,
    235, 47,  185, 9,   82,  64,  87,  244, 50,  74,  233, 175, 247, 120, 6,
    169, 85,  66,  104, 80,  71,  230, 152, 225, 34,  248, 198, 63,  168, 179,
    141, 137, 5,   19,  79,  232, 128, 202, 46,  70,  37,  209, 217, 123, 27,
    177, 25,  56,  65,  229, 36,  197, 234, 108, 35,  151, 238, 200, 224, 99,
    190
};

// Given the current hash value and a byte
// blobby_hash returns the new hash value
//
// Call repeatedly to hash a sequence of bytes, e.g.:
// uint8_t hash = 0;
// hash = blobby_hash(hash, byte0);
// hash = blobby_hash(hash, byte1);
// hash = blobby_hash(hash, byte2);
// ...

uint8_t blobby_hash(uint8_t hash, uint8_t byte) {
    return blobby_hash_table[hash ^ byte];
}
