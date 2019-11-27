#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <string.h>

char ** parse_args( char * line ) {
  size_t str_len = strlen(line)+1;
  char ** final = calloc(sizeof(char *), 8);
  char * copy = calloc(sizeof(char), str_len);
  strncpy(copy, line, str_len);
  char * temp = copy;
  int i;
  for (i = 0; (temp = strsep(&copy, " ")) != NULL; i++) {
    int mini_len = strlen(temp);
    final[i] = calloc(sizeof(char), mini_len + 1);
    strncpy(final[i], temp, mini_len);
    final[i][mini_len] = 0;
  }
  free(copy);
  return final;
}

void free_args(char ** args) {
  size_t num_args = strlen((char *) args);
  int i;
  for (i = 0; i < num_args; i++) {
    free(args[i]);
  }
  free(args);
}

int main(int argc, char ** argv) {
  char input_str[] = "ls -a -l";
  char ** args = parse_args(input_str);
  execvp(args[0], args);

  //I know this won't be executed, but whatever
  free_args(args);
  return 0;
}
