/*
  Authors:
    A01361252 Martín Ruíz
    A01361162 Isaac Secundino
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAXLINE 4096

/*Construct a String to use for the minishell prompt*/
char *getPrompt(){
  // Obtain USER environment variable
  char *user = getenv("USER");
  int userlen = strlen(user);
  char *prompt = (char*) malloc(sizeof(userlen+3));
  strcpy(prompt,user);

  // Extra characters for prompt
  prompt[userlen] = '>';
  prompt[userlen+1] = ' ';
  prompt[userlen+2] = '\0';

  return prompt;
}

/*Print help section*/
void print_help(){
  printf("\n                      -- MINI SHELL Help Section --   \n");
  printf("\n[Description]\n");
  printf("\tThis a little section made for helping new users to interact with \n\tthis Mini Shell\n");

  printf("\n[Instructions]\n");
  printf("\t-Mini Shell reads your input after you press Enter\n");
  printf("\t-The first word of your input determines the commnad that \n\t will be executed\n");
  printf("\t-A word is an unbroken set of characters \n\t-Spaces and tabs separate words\n");

  printf("\n[Command Summary]\n");
  printf("\tapple - [Warning: DO NOT use this command]\n");
  printf("\tcal   - shows a calendar of the current month\n");
  printf("\tcp    - copies a file\n");
  printf("\tdate  - shows the current date and time\n");
  printf("\texit  - end Mini Shell program\n");
  printf("\thelp  - shows some information\n");
  printf("\tls    - shows files in the current directory\n");
  printf("\tman   - display manual of a command\n");
  printf("\tmv    - moves a file\n");
  printf("\tmkdir - make a new directory\n");
  printf("\trm    - removes a file\n");

  printf("\n[Notes]\n");
  printf("\tThis version supports more than 4 parameters\n");
  printf("\tWe use execvp instead of execlp to support more than 4 parameters\n");
  printf("\tDoes not support command history\n");
  printf("\tDoes not support arrow keys\n");
  printf("\tDoes not support 'cd' command\n");

  printf("\n[Version]\n");
  printf("\tversion 1.0   03/16/17\n");

  printf("\n[Authors]\n");
  printf("\tThis Mini Shell was made by: Martín Ruíz & Isaac secundino\n");
}

void print_eg1(){
  printf("Segmentation fault ");
}
void print_eg2(){
  fflush(stdout);
  sleep(1);
  printf(".");
  fflush(stdout);
  sleep(1);
  printf(".");
  fflush(stdout);
  sleep(1);
  printf(".\n");
  printf("Buuuuuuuuuuuuuuuuuuuuuu! \n" );
}

/*Get a String array from a Buffer*/
char **vector_from_buf(char* buffer){
  int argCounter = 0;
  int space = isspace(buffer[0]) == 0 ? 1 : 0;
  char **vector;

  // Count number of arguments/parameters
  for (size_t i = 0; i < strlen(buffer); i++) {
    if(isspace(buffer[i]) == 0 && space != 0){
      argCounter++;
      space = 0;
    }else if(isspace(buffer[i]) != 0){
      space = 1;
    }
  }

  vector = (char**)malloc((argCounter+1) * sizeof(char*));

  int arglen = 0;
  int index = 0;

  // Fill array
  for (size_t i = 0; i < strlen(buffer)+1; i++) {
    if(isspace(buffer[i]) != 0 || buffer[i] == '\0'){ //Find the end of a parameter
      if(arglen != 0){
        vector[index] = (char*)malloc(arglen+1);
        strncpy(vector[index],(buffer+(i-arglen)),arglen);
        index++;
        arglen = 0;
      }
      continue;
    }
    arglen++;
  }

  // Because of the use of execvp, the last element must be a NULL
  vector[argCounter] = NULL;

  return vector;
}

int main(void){
  char buf[MAXLINE];
  pid_t pid;
  int status;
  char *prompt = getPrompt();

  printf("%s",prompt);
  while (fgets(buf,MAXLINE,stdin) != NULL){
    // Check for blank spaces or none commands entered
    int isTrash = 0;
    for (size_t i=0; i<strlen(buf); i++) {
      if(isspace(buf[i]) == 0){
        isTrash = 1;
        break;
      }
    }
    if(buf[0]=='\n' || isTrash == 0){
      printf("%s",prompt);
      continue;
    }

    if (buf[strlen(buf)-1] == '\n'){
      buf[strlen(buf)-1] = '\0'; /* replace newline with null */
    }

    // Obtain an array with the introduced parameters
    char **vec = vector_from_buf(&buf[0]);

    /* Special commands */
    //Help command
    if(strcmp(vec[0],"help") == 0){
      print_help();
      printf("%s",prompt);
      continue;
    }
    //EasterEgg
    if(strcmp(vec[0],"apple") == 0){
      print_eg1();

      print_eg2();
      printf("%s",prompt);
      continue;
    }
    // Exit command
    if(strcmp(vec[0],"exit") == 0 ){
      exit(0);
    }

    if ((pid = fork()) < 0){
      printf("fork error\n");
      exit(1);
    }else if (pid == 0){ /* child process */
      execvp(vec[0],vec);
      printf("couldn’t execute: %s\n",buf);
      exit(127);
    }
    /* parent process*/
    if (pid = waitpid(pid,&status,0) < 0){
      printf("waitpid error\n");
      exit(1);
    }

    // Free vector
    printf("[%d]",sizeof(vec));

    /*
    for (int i=0; i<sizeof(vec); i++){
      char *tofree = vec[i];
      free(tofree); 
    }
    */

    printf("%s",prompt);
  }

  // Free memory
  free(prompt);

  exit(0);
}
