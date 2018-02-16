#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

// Maximum length of input commands
#define MAX_STR 300
// Maximum amount of arguments in single command
#define MAX_ARG 30
// Maximum amount of commands from input
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

            // execute multiple commands with concurrent
            run(cmds);
        }
    }
    // BATCH MODE
    else if (argc == 2)
    {
        // TODO: read from file, run commands
    }
    // WRONG USAGE
    else
    {
        printf("Usage: shell [batch_file]");
    }
    return 0;
}

/**
 * Execute multiple commands with concurrent
 * @param   char** cmd      array of commands
 */
void run(char** cmds)
{
    int i = 0, j, status;
    char** cmd;
    while (cmd = splitArg(cmds[i++])) {
        // let only child process work
        if (fork() == 0) {
            // check if there is any error in command
            if (execvp(cmd[0], cmd) < 0) {
                // print error out with stderr
                fprintf(stderr, "%s: command error!\n", cmd[0]);
            }
            // execvp(cmd[0], cmd);
            // perror(cmd[0]);

            // exit child process
            exit(0);
        }
    }
    // wait for all child process to be done
    // waitpid(-1);
    for (j = 0; j < i; j++)
        wait(&status);

    // free memory
    free(cmds);
}

/**
 * Split multiple arguments into array
 * @param   char* cmd     input command string
 * @return  char**        array of arguments
 */
char** splitArg(char* cmd)
{
    // check if input is null
    if (cmd == NULL) {
        return NULL;
    }

    int i;
    char* token;
    char** tokens = (char **) malloc(MAX_ARG * sizeof(char *));
    // split string with whitespace
    for (i = 0; token = strsep(&cmd, " "); i++) {
        // check if command contain more than one space or contain no character
        if (token != NULL && token[0] != 0 && token[0] != ' ') {
            tokens[i] = token;
        } else {
            // not count
            i--;
        }
    }
    // add null character to show end of array
    tokens[i++] = NULL;
    // realloc(tokens, i);

    // free memory
    free(cmd);

    return tokens;
}

/**
 * Split multiple command into array
 * @param   char* str     input commands string
 * @return  char**        array of commands
 */
char** splitCmd(char* str)
{
    // check if input is null
    if (str == NULL) {
        return NULL;
    }
    
    int i;
    char* cmd;
    char** cmds = (char **) malloc(MAX_CMD * sizeof(char *));
    // split string with semi-colon
    for (i = 0; cmd = strsep(&str, ";"); i++) {
        cmds[i] = cmd;
    }
    // add null character to show end of array
    cmds[i++] = 0;
    // realloc(cmds, i);

    // free memory
    free(str);

    return cmds;
}