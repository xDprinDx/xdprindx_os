#ifndef COMMANDS
#define COMMANDS

#include "fm.h"

int inputSpaces = 0;

char* getCommand(char* input){
  if (inputSpaces == 0) return input; //if there is nothing but the command, just return the command
  char* ret = malloc(sizeof(char) * 257);
  int i, c;

  for (i = 0; input[i] != ' '; i++) { //go through input and put everything until the first space to ret
    c = (int) input[i];
    ret[i] = (char) c;
  }

  ret[i] = '\0'; //close the string

  return ret; //return ret
}

//if this command is called there will be an argument for sure, so there's no need to add a failsafe
char* getArg(char* input, int arg){
  char* ret = malloc(sizeof(char) * 256);
  int spaceC = 0, i, i2 = 0, c; //spaceC = space count, c = character

  for (i = 0; i != strlen(input); i++){
    if (spaceC == arg){
      c = (int) input[i];
      ret[i2++] = (char) c;
    }

    if (input[i] == ' ') spaceC++; //increment spaceC if there is a space
  }

  //copied this again because if the argument is at the end of input, it wont get last character
  if (spaceC == arg){
    c = (int) input[i];
    ret[i2++] = (char) c;
  }

  ret[i2 - 1] = '\0'; //end string
  return ret; //return ret
}

void doCommand(char* input, int debug){
  char* command = malloc(sizeof(char) * 257);
  strcpy(command, getCommand(input));

  if (strlen(input) != 0){ //cause sometimes it is annoying :v
    if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"user entered: \"%s\" \n",input);
    if (debug == 1) printf(KGRN"[DEBUG]: "KNRM"inputSpaces = %i \n", inputSpaces);
  }

  if (debug == 1) printf(KGRN"[DEBUG]: "KNRM "command entered is \"%s\"\n",command);

  //each command will have a comment above it to make it easier to read

  //test
  if ((strcmp(command,"test")) == 0 && inputSpaces == 2){
    printf("arguments: %s (size: %i) \n", (getArg(input, 1)), strlen(getArg(input, 1)));
  }

  //clear
  else if ((strcmp(command, "clear")) == 0 && inputSpaces == 0){
    for (int i = 0; i != 50; i++) printf("\n");
  }

  //makedir
  else if ((strcmp(command,"makedir")) == 0 && inputSpaces == 1){
    printf(KGRN"[DEBUG]: "KNRM"%s \n", getArg(input, 1));
    makedir(getArg(input, 1), debug);
  }

  //remdir
  else if ((strcmp(command, "remdir")) == 0 && inputSpaces == 1){
    remdir(getArg(input, 1), debug);
  }

  else {
    printf("Sorry, command doesn't exist\n");
  }

  free(command);
  free(arg);
}

void getInput(int debug){
  char* input = malloc(sizeof(char) * 2560);

  //i'll make a function later that can get the current directory
  //strcpy(cdir,directory); //so it wont be included in this current update

  printf("%s> ", username);
  fgets(input,2560, stdin);

  //cleaning the input string so that it can be somewhat usable
  input[strlen(input) - 1] = '\0'; //removing '\n' at the end of the string
  while(input[strlen(input) - 1] == ' ') input[strlen(input) - 1] = '\0'; //removing additional spaces at the end of the string
  while(input[0] == ' ') memmove(input, input + 1, strlen(input)); //removing additional spaces at the start of the string

  for(int i = 0; i != strlen(input); i++){ //this for loop look into input and checks for extra spaces inside of string
    if (input[i] == ' ' && input[i + 1] == ' '){ //checks for 2 spaces next to each other
      memmove(&input[i + 1], &input[i + 2], strlen(input) - (i + 1)); //removes the spaces
      i--; //for some reason it only works if i-- is done
    }
  }

  for (int i = 0; i != strlen(input); i++) //looping through string to see how many spaces there are
    if (input[i] == ' ')
      inputSpaces++;

  doCommand(input, debug);

  inputSpaces = 0;

  free(input);
  //free(cdir);
}

#endif
