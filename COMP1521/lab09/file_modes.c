//A program which checks the permissions of a file
//or directory
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main (int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Not enough arguments\n");
		exit(1);
	}

	struct stat s;
	int i = 1;
	while (i < argc) {
		if (stat(argv[i], &s) ) {
			perror("Error: ");
			exit(1);
		}
		//Check if argument is a directory
		if (s.st_mode & S_IFDIR) {
			putchar('d');
			//check the permissions for a user
			if (s.st_mode & S_IRUSR) {
				putchar('r');
			}
			else {
				putchar('-');
			}
			if (s.st_mode & S_IWUSR) {
				putchar('w');
			}
			else {
				putchar('-');
			}
			if (s.st_mode & S_IXUSR) {
				putchar('x');
			}
			else {
				putchar('-');
			}
			//check the permissions for a group
			if (s.st_mode & S_IRGRP) {
				putchar('r');
			}
			else {
				putchar('-');
			}
			if (s.st_mode & S_IWGRP) {
				putchar('w');
			}
			else {
				putchar('-');
			}
			if (s.st_mode & S_IXGRP) {
				putchar('x');
			}
			else {
				putchar('-');
			}
			//Check the permissions for others
			if (s.st_mode & S_IROTH) {
				putchar('r');
			}
			else {
				putchar('-');
			}
			if (s.st_mode & S_IWOTH) {
				putchar('w');
			}
			else {
				putchar('-');
			}
			if (s.st_mode & S_IXOTH) {
				putchar('x');
			}
			else {
				putchar('-');
			}


		}
		else {
			putchar('-');
			//check the permissions for a user
			if (s.st_mode & S_IRUSR) {
				putchar('r');
			}
			else {
				putchar('-');
			}
			if (s.st_mode & S_IWUSR) {
				putchar('w');
			}
			else {
				putchar('-');
			}
			if (s.st_mode & S_IXUSR) {
				putchar('x');
			}
			else {
				putchar('-');
			}

			//check the permissions for a group
			if (s.st_mode & S_IRGRP) {
				putchar('r');
			}
			else {
				putchar('-');
			}
			if (s.st_mode & S_IWGRP) {
				putchar('w');
			}
			else {
				putchar('-');
			}
			if (s.st_mode & S_IXGRP) {
				putchar('x');
			}
			else {
				putchar('-');
			}
			//Check the permissions for others
			if (s.st_mode & S_IROTH) {
				putchar('r');
			}
			else {
				putchar('-');
			}
			if (s.st_mode & S_IWOTH) {
				putchar('w');
			}
			else {
				putchar('-');
			}
			if (s.st_mode & S_IXOTH) {
				putchar('x');
			}
			else {
				putchar('-');
			}

		}

		printf(" %s\n", argv[i]);

		i +=1;
	}


}
