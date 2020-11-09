// blobby.c
// blob file archiver
// COMP1521 20T3 Assignment 2
// Written by <YOUR NAME HERE>
//MKV: Major step in extracting folders and files


//TODO
//Perform error checking for all file functions
//Consider edge cases for length name of files!

//BUG!
//max file size is 6 bytes, need to change byte count to uint64_t
//Check for file permissions when using fopen


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

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
void create_blob(char *blob_pathname, char *pathnames[], int compress_blob);

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
//Three classes of functions for subset 3
char *getDir (int begin, int end, char *name);
int addDirToBlob (char *dir, uint64_t *byteCount,
         uint64_t *beginBobblet, FILE *newBlob);
int addFileToBlob (char *dir, uint64_t *byteCount,
         uint64_t *beginBobblet, FILE *newBlob);
void addRecurToBlob (char *basePath, uint64_t *byteCount,
         uint64_t *beginBobblet, FILE * newBlob);
int addParent (int numBackSlash, char *pathName, FILE *newBlob,
         uint64_t *byteCount, uint64_t *beginBobblet);


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


// extract the contents of blob_pathname
void extract_blob(char *blob_pathname) {

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
		printf("Extracting: %s\n", pathName);
		uint64_t offset4 = offset3 + pathname_length;
		//printf("%lu \n", offset4);

		//Get the offset for the newFile in the correct position
		if (hashBegin) {
			offset4 +=1;
		}

		//Create a new file
		FILE *newFile = fopen(pathName, "w+");
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

		//Fetch the hash value
		uint8_t hash = fetchByte(i, i, f1);
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

// create blob_pathname from NULL-terminated array pathnames
// compress with xz if compress_blob non-zero (subset 4)

void create_blob(char *blob_pathname, char *pathnames[], int compress_blob) {

    // REPLACE WITH YOUR CODE FOR -c
    /*
    printf("create_blob called to create %s blob '%s' containing:\n",
           compress_blob ? "compressed" : "non-compressed", blob_pathname);
    */
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
        if (pathName.st_mode & S_IFDIR) {
            addDirToBlob(pathnames[p], &byteCount, &beginBobblet, newBlob);
            addRecurToBlob(pathnames[p], &byteCount, &beginBobblet, newBlob);
        }
        //Dealing with a file
        else {
            addFileToBlob(pathnames[p], &byteCount, &beginBobblet, newBlob);
        }
    }

    fclose(newBlob);
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//My functions:

//A recursive function which adds a file or directory to a blob
//With code adapted from the COMP1521 week08 slides
//on mkdir

//There's a bug, readdir can only read a max of 256 characters.
//It will break if the name of the file/directory exceeds 256 chars
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

//A function which checks if a file is under a directory
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
