/*
Einfache Kommandozeilen-Shell (LSH), die Benutzerbefehle liest,
diese in Argumente aufteilt und ausführt. Unterstützt interne Befehle
wie cd, help, exit und startet externe Programme mit fork und execvp.
*/


#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define LSH_RL_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

int lsh_cd(char** args);
int lsh_help(char** args);
int lsh_exit(char** args);

const char* builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[])(char**) = {
    &lsh_cd,
    &lsh_help,
    &lsh_exit
};

int lsh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char*);
}

int lsh_cd(char** args) {
    if (args[1] == NULL) {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("lsh");
        }
    }
    return 1;
}

int lsh_help(char** args) {
    int i;
    printf("Mohammad Abu Saleh's LSH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < lsh_num_builtins(); i++) {
        printf("%s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

int lsh_exit(char** args) {
    return 0;
}

char* lsh_read_line(void) {
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char* buffer = (char*)malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "lsh allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        c = getchar();
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        if (position >= bufsize) {
            bufsize += LSH_RL_BUFSIZE;
            char* temp = (char*)realloc(buffer, bufsize);
            if (!temp) {
                free(buffer);
                fprintf(stderr, "lsh allocation error\n");
                exit(EXIT_FAILURE);
            }
            buffer = temp;
        }
    }
}

char** lsh_split_line(char* line) {
    int bufsize = LSH_TOK_BUFSIZE;
    int position = 0;
    char** tokens = (char**)malloc(bufsize * sizeof(char*));
    char* token;

    if (!tokens) {
        fprintf(stderr, "lsh allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += LSH_TOK_BUFSIZE;
            char** temp = (char**)realloc(tokens, bufsize * sizeof(char*));
            if (!temp) {
                free(tokens);
                fprintf(stderr, "lsh allocation error\n");
                exit(EXIT_FAILURE);
            }
            tokens = temp;
        }
        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

int lsh_launch(char** args) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("lsh");
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int lsh_execute(char** args) {
    int i;
    if (args[0] == NULL) {
        return 1;
    }

    for (i = 0; i < lsh_num_builtins(); ++i) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return lsh_launch(args);
}

void lsh_loop(void) {
    char* line;
    char** args;
    int status;

    do {
        printf("> ");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);

        free(line);
        free(args);

    } while (status);
}

int main(void) {

    lsh_loop();
    
    return EXIT_SUCCESS;
}
