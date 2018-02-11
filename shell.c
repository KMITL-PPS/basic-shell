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

int main(int argc, char** argv)
{
    // INTERACTIVE MODE
    if (argc == 1)
    {
        char str[MAX_STR];
        while (1) {
            // in case user did not type anything
            str[0] = '\0';

            // receive command from stdin
            printf("shell> ");
            scanf("%[^\n]", str);
            getchar();

            // check if user type command 'quit' or user did not type anything
            if (!strcmp(str, "quit")) {
                return 0;
            } else if (strlen(str) == 0) {
                continue;
            }

            // split multiple command
            char **cmds = splitCmd(str);

            // run commands
            run(cmds);
        }
    }
    // BATCH MODE
    else if (argc == 2)
    {
        // TODO: read from file, run commands
    }
    // ERROR
    else
    {
        printf("Usage: shell [batch_file]");
    }
    return 0;
}

void run(char** cmds)
{
    int i = 0, j, status;
    char** cmd;
    while (cmd = splitArg(cmds[i++])) {
        if (fork() == 0) {     // child
            if (execvp(cmd[0], cmd) < 0) {
                printf("%s: command error!\n", cmd[0]);
            }
            // execvp(cmd[0], cmd);
            // perror(cmd[0]);
            exit(0);
        }
    }
    // waitpid(-1);
    for (j = 0; j < i; j++)
        wait(&status);

    free(cmds);
}

char** splitArg(char* cmd)
{
    if (cmd == NULL) {
        return NULL;
    }

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
    // realloc(tokens, i);
    free(cmd);

    return tokens;
}

char** splitCmd(char* str)
{
    if (str == NULL) {
        return NULL;
    }
    
    int i;
    char* cmd;
    char** cmds = (char **) malloc(MAX_CMD * sizeof(char *));
    for (i = 0; cmd = strsep(&str, ";"); i++) {
        cmds[i] = cmd;
    }
    cmds[i++] = 0;
    // realloc(cmds, i);
    free(str);

    return cmds;
}