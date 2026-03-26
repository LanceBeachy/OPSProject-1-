
#include <stdio.h>       // Standard I/O
#include <string.h>       // String operations
#include <unistd.h>       // POSIX API
#include <stdlib.h>       // Standard library
#include <sys/wait.h>     // Wait for processes

#define MAX_ARGS		64        // Max number of arguments
#define MAX_ARG_LEN		16        // Max argument length
#define MAX_LINE_LEN	80        // Max line length
#define WHITESPACE		" ,\t\n"   // Whitespace delimiters

struct command_t {           // Command structure
   char *name;              // Command name
   int argc;                // Argument count
   char *argv[MAX_ARGS];    // Argument array
};

/* Function prototypes */
int parseCommand(char *, struct command_t *);    // Parse command line
void printPrompt();                               // Display prompt
void readCommand(char *);                         // Read user input
void printHelp();                                 // Display help menu
void runListCommand();                            // List directory

int main(int argc, char *argv[]) {               // Main function
   int pid;                                       // Process ID
   int status;                                    // Process status
   char cmdLine[MAX_LINE_LEN];                   // Input buffer
   struct command_t command;                      // Command structure

   while (1) {                                    // Main loop
      printPrompt();                              // Show prompt
      /* Read the command line and parse it */
      readCommand(cmdLine);                       // Get input

     if (parseCommand(cmdLine, &command) == 0) { // Parse command
	continue;                                      // Skip if empty
}
    if(strcmp(command.name, "C") ==0) {           // Copy command
	command.name = "cp";                           // Map to cp
	command.argv[0] = "cp";                        // Set argument
}
if(strcmp(command.name, "D") ==0){               // Delete command
	command.name = "rm";                           // Map to rm
	command.argv[0] = "rm";                        // Set argument
}

if(strcmp(command.name, "M") ==0){               // Make/edit command
	command.name = "nano";                         // Map to nano
	command.argv[0] = "nano";                      // Set argument
}
if(strcmp(command.name, "P") ==0){               // Print command
	command.name = "more";                         // Map to more
	command.argv[0] = "more";                      // Set argument
}
if(strcmp(command.name, "W") ==0){               // Wipe command
	command.name = "clear";                        // Map to clear
	command.argv[0] = "clear";                     // Set argument
}

if(strcmp(command.name, "X") == 0){              // Execute command
    int i;                                        // Loop counter
    for(i=0; i< command.argc - 1; i++){          // Shift arguments
        command.argv[i] = command.argv[i + 1];   // Move argument
    }
    command.argc--;                               // Decrease count
    command.argv[command.argc] = NULL;           // Null terminate
    command.name = command.argv[0];              // Set name

}

if(strcmp(command.name, "Q") == 0){              // Quit command
    break;                                        // Exit loop
}    

if(strcmp(command.name, "E") == 0){              // Echo command
    int i;                                        // Loop counter
    for(i=1; i < command.argc; i++){             // Print arguments
        printf("%s", command.argv[i]);            // Output argument
        if(i<command.argc - 1){                   // If not last
            printf(" ");                          // Add space
        }
    }
    printf("\n");                                 // New line
    continue;                                     // Skip execution
}

if(strcmp(command.name, "H") == 0){              // Help command
    printHelp();                                  // Show help
    continue;                                     // Skip execution
}

if(strcmp(command.name, "L") == 0){              // List command
    runListCommand();                             // List directory
    continue;                                     // Skip execution
}

    pid = fork();                                 // Create process

    if (pid<0){                                   // Fork failed
        perror("fork");                           // Print error

    } else if(pid == 0){                          // Child process
        execvp(command.name, command.argv);      // Execute command
        perror("execvp");                         // Print error
        exit(1);                                  // Exit with error
    }else{                                        // Parent process
        wait(&status);                            // Wait for child
    }
}
    printf("\n\nshell: Ternminating Successfully\n");  // Exit message
    return 0;                                     // Return success

}

int parseCommand(char *cLine, struct command_t *cmd){  // Parse command
    int argc;                                    // Argument count
    char **clPtr;                                 // Command line pointer

    clPtr = &cLine;                               // Initialize pointer
    argc = 0;                                     // Initialize count

    while ((cmd->argv[argc] = strsep(clPtr, WHITESPACE)) != NULL) {  // Split tokens
        if(*(cmd->argv[argc]) == '\0'){           // Skip empty
            continue;                             // Continue loop
        }
        argc++;                                   // Increment count
        if(argc >= MAX_ARGS -1){                  // Check limit
            break;                                // Exit loop
        }
    }

    if (argc ==0){                                // No arguments
        cmd->argc = 0;                            // Set count
        cmd->name = NULL;                         // Clear name
        cmd->argv[0] = NULL;                      // Clear argv
        return 0;                                 // Return failure
    }

    cmd->argc = argc;                             // Set argument count
    cmd->argv[argc] = NULL;                       // Null terminate
    cmd->name = cmd->argv[0];                     // Set command name
    return 1;                                     // Return success
}

void printPrompt(){                               // Print prompt function
    printf("linux 4800828|> ");                   // Prompt text
    fflush(stdout);                               // Flush output
}

void readCommand(char *buffer){                   // Read command function
    fgets(buffer, MAX_LINE_LEN, stdin);           // Get line from input
}

void printHelp(){                                 // Print help function
    printf("\nSimple Linux Shell Help\n");        // Help header
    printf("C file1 file2 - copy file1 to file2\n");    // Copy help
    printf("D file      - delete file\n");       // Delete help
    printf("E comment   - echo comment\n");       // Echo help
    printf("H       - display help\n");           // Help help
    printf("L       - list current directory\n"); // List help
    printf("M file      - edit file with nano\n");     // Make/edit help
    printf("P file      - display file with more\n");  // Print help
    printf("Q       - quit shell\n");             // Quit help
    printf("W       - clear screen\n");           // Wipe help
    printf("X program       - execute program\n");     // Execute help
    
}

void runListCommand(){                            // List command function
    int st;                                       // Status variable
    pid_t pid;                                    // Process ID

    printf("\n");                                 // New line

    pid = fork();                                 // Create child process
    if(pid == 0){                                 // In child
        char *args[] = {"pwd", NULL};             // Arguments for pwd
        execvp("pwd", args);                      // Execute pwd
        perror("execvp");                         // Print error
        exit(1);                                  // Exit with error
    }else {                                       // In parent
        wait(&st);                                // Wait for child
    }

    printf("\n");                                 // New line

    pid = fork();                                 // Create child process
    if(pid == 0){                                 // In child
        char *args[] = {"1s", "-l", NULL };      // Arguments for ls
        execvp("1s", args);                       // Execute ls
        perror("execvp");                         // Print error
        exit(1);                                  // Exit with error
    }else {                                       // In parent
        wait(&st);                                // Wait for child
    }
}

