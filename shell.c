#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#define MAX_STR 300
#define MAX_ARG 30
#define MAX_CMD 10

void run(char **);
char** splitArg(char *);
char** splitCmd(char *);

int main()
{
    char* str;
    while (1) {
        str = (char *) malloc(MAX_STR * sizeof(char));
        // memset(str, 0, MAX_STR);

        // receive command from stdin
        printf("shell> ");
        scanf("%[^\n]", str);
        getchar();
        // realloc(str, strlen(str));

        // check if user type command 'quit'
        if (!strcmp(str, "quit"))
            return 0;

        // split multiple command
        char **cmds = splitCmd(str);

        run(cmds);

        // int i = 0;
        // char* cmd;
        // while (cmd = cmds[i++]) {
        //     // printf("%s\n", cmd);

        //     // split multiple arguments
        //     char** args = splitArg(cmd);

        //     // run command
        //     run(args);
        // }
        // free(str);
    }
    return 0;
}

void run(char** cmds)
{
    int i = 0;
    char* cmd;
    int status;
    while (cmd = cmds[i++]) {
        pid_t pid = fork();

        if (pid == 0) {     // child
            if (execvp(cmd[0], cmd) < 0) {
                printf("[%d]%s: command error!\n", pid, cmd[0]);
            }
            // execvp(cmd[0], cmd);
            // perror(cmd[0]);
            exit(0);
        }
    }
    wait(&status);
    free(cmds);

    // pid_t pid = fork();
    // int status;

    // if (pid == 0) {
    //     if (execvp(cmd[0], cmd) < 0) {
    //         printf("%s: command error!\n", cmd[0]);
    //     }
    //     // execvp(cmd[0], cmd);
    //     // perror(cmd[0]);
    //     exit(0);
    // } else {
    //     wait(&status);
    //     free(cmd);
    //     // printf("\n");
    // }
}

char** splitArg(char* cmd)
{
    int i;
    char* token;
    char** tokens = (char **) malloc(MAX_ARG * sizeof(char *));
    for (i = 0; token = strsep(&cmd, " "); i++) {
        // check if command contain more than one space or contain no character
        if (token != NULL && token[0] != 0 && token[0] != ' ') {
            tokens[i] = token;
        } else {
            i--;
        }
    }
    tokens[i++] = NULL;
    realloc(tokens, i);
    free(cmd);

    return tokens;
}

char** splitCmd(char* str)
{
    int i;
    char* cmd;
    char** cmds = (char **) malloc(MAX_ARG * sizeof(char *));
    for (i = 0; cmd = strsep(&str, ";"); i++) {
        // check if command contain more than one space or contain no character
        // if (cmd != NULL && cmd[0] != 0 && cmd[0] != ' ') {
            cmds[i] = cmd;
        // } else {
        //     i--;
        // }
    }
    cmds[i++] = NULL;
    realloc(cmds, i);
    free(str);

    return cmds;
}