#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

void run(char **);
char** splitArg(char *);
char** splitCmd(char *);

int main()
{
    char* cmd;
    while (1) {
        // receive command from stdin
        printf("shell> ");
        scanf("%[^\n]", cmd);
        getchar();

        // split multiple command

        // split multiple arguments

        // test run command
        // char **test = {"/bin/ls", 0};
        char** test = (char **) malloc(3 * sizeof(char *));
        test[0] = "/bin/ls";
        test[1] = ".";
        test[2] = NULL;
        run(test);
    }
    return 0;
}

void run(char** cmd)
{
    // test run command
    pid_t pid = fork();
    int status;
    if (pid == 0) {
        execv(cmd[0], cmd);
    } else {
        wait(&status);
        // printf("\n");
    }
}

char** splitArg(char* cmd)
{

}

char** splitCmd(char* cmd)
{

}