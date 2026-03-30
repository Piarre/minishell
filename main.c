#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_INPUT_BUFFER_SIZE 1024

#define PIPE "|"

int main()
{
    char buffer[MAX_INPUT_BUFFER_SIZE];
    char *argv[64];
    char cwd[512];

    pid_t pid;

    for (;;)
    {
        printf("$ ~> ");
        char *input =
            fgets(buffer, sizeof(char) * MAX_INPUT_BUFFER_SIZE, stdin);

        buffer[strcspn(buffer, "\n")] = '\0';

        // Handle EOF
        if (input == NULL) break;

        char *tokens = strtok(buffer, " ");

        if (tokens == NULL) continue;

        int i = 0;
        while (tokens != NULL)
        {
            argv[i] = tokens;
            i++;
            tokens = strtok(NULL, " ");
        }

        char **cmd2 = NULL;
        for (int j = 0; j < i; j++)
        {

            if (strcmp(argv[j], PIPE) == 0)
            {
                argv[j] = NULL;
                cmd2 = &argv[j + 1];
            }
        }

        argv[i] = NULL;

        if (strcmp(argv[0], "exit") == 0)
        {
            return 0;
        }

        if (strcmp(argv[0], "cd") == 0)
        {
            if (argv[1] == NULL) continue;

            chdir(argv[1]);
            continue;
        }

        if (strcmp(argv[0], "pwd") == 0)
        {
            if (getcwd(cwd, 512) == NULL) return 1;

            printf("Current working directory: %s\n", cwd);
            continue;
        }

        pid = fork();

        if (pid == 0)
        {
            execvp(argv[0], argv);
            perror("Unknow command");
            _exit(127);
        }
        else if (pid == -1)
        {
            perror("Error on creating child process.");
            continue;
        }
        else if (pid > 0)
        {
            wait(NULL);
        };

        printf("\n");
    }

    return 0;
}