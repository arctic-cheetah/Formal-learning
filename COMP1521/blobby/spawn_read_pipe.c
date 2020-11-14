#include <stdio.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int check_file_type(char *f);
char *decompressedFile(char *text);
#define MAX_LENGTH 0xFFFFFF

int main(void) {

    //check the type of the file
    char *text = "text_file";
    int fileType = check_file_type(text);
    if (!fileType) {
        printf("The file is XZ!\n");

        char *file = decompressedFile(text);

        int i = 0;
        while (file[i] != EOF) {
            printf("%c", file[i]);
            i +=1;
        }
    }
    else {
        printf("The file is ascii!\n");
        exit(1);
    }

    return 0;
}

//Returns 0 if the file is xz
int check_file_type(char *text) {

    char *xz = ": XZ compressed data\n";

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(1);
    }

    // create a list of file actions to be carried out on spawned process
    posix_spawn_file_actions_t actions;
    if (posix_spawn_file_actions_init(&actions) != 0) {
        perror("posix_spawn_file_actions_init");
        return 1;
    }

    //Close the read end of the pipe of the child process
    if (posix_spawn_file_actions_addclose(&actions, pipe_fd[0]) != 0) {
        perror("posix_spawn_file_actionsaddclose");
        exit(1);
    }

    //Tell the child process to set write end of the pipe to stdout
    if (posix_spawn_file_actions_adddup2(&actions, pipe_fd[1], STDOUT_FILENO) != 0 ) {
        perror("posix_spawn_file_actions_adddup2");
        exit(1);
    }

    pid_t pid;
    extern char **environ;
    char *file[] = {"file", text, NULL};
    if (posix_spawn(&pid, "/usr/bin/file", &actions, NULL, file, environ) != 0) {
        perror("spawn");
        return 1;
    }

    close(pipe_fd[1]);

    FILE *f = fdopen(pipe_fd[0], "r");
    if (!f) {
        perror("file");
        exit(1);
    }

    char line[256];
    int c = 0;
    int i = 0;
    int hasReachedSemiColon = 0;
    while ((c = fgetc(f)) != EOF) {
        printf("%c", c);
        if (c == ':') {
            hasReachedSemiColon = 1;
        }
        if (hasReachedSemiColon) {
            line[i] = c;
            i +=1;
        }
    }
    line[i] = '\0';
    //printf("%s", line);

    int exit_status;
    if (waitpid(pid, &exit_status, 0) == -1) {
        perror("waitpid");
        return 1;
    }

    posix_spawn_file_actions_destroy(&actions);
    fclose(f);
    return strcmp(line, xz);
}

char *decompressedFile(char *text) {
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
    char *line = malloc(MAX_LENGTH * sizeof(char));
    int c = 0;
    int i = 0;
    while ((c = fgetc(f)) != EOF) {
        //printf("%c", c);
        line[i] = c;
        i +=1;
    }
    line[i + 1] = EOF;

    //printf("\n\n\n");
    /*
    int j = 0;
    while (j < i) {
        printf("%c", line[j]);
        j +=1;
    }
    printf("\n");
    */
    // close read-end of the pipe
    // spawned process will now receive EOF if attempts to read input
    fclose(f);

    int exit_status;
    if (waitpid(pid, &exit_status, 0) == -1) {
        perror("waitpid");
        exit(1);
    }
    printf("/bin/date exit status was %d\n", exit_status);

    // free the list of file actions
    posix_spawn_file_actions_destroy(&actions);

    return line;
}


