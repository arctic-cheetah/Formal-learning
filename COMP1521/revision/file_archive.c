#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <sys/wait.h>


int main (int argc, char **argv) {
	
	char *tar[5];
	
	//Compress the file
	if (argc == 3) {
		tar[0] = "tar";
		tar[1] = "-cf";
		tar[2] = argv[1];
		tar[3] = argv[2];
		tar[4] = NULL;
	}
	//Uncompress
	else if (argc == 2) {
		tar[0] = "tar";
		tar[1] = "-xf";
		tar[2] = argv[1];
		tar[3] = NULL;
	}
	pid_t pid;
	extern char **environ;
	if (posix_spawn(&pid, "/usr/lib/tar", NULL, NULL, tar, environ) != 0) {
		perror("posix_spawn");
		exit(1);
	}
	
	int exit_status;
	if (waitpid(pid, &exit_status, 0) == -1) {
		perror("waitpid");
		exit(1);
	}
	
	return exit_status;
}




