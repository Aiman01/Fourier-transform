#include "resourcesManager.h"
#include <stdio.h>
#include <stdlib.h>



char* rdfl(const char *path){
  FILE *fptr, *temp;
  fptr = fopen(path, "r");
  temp = fopen(path, "r");
  if(fptr == NULL||temp == NULL){
    fprintf(stderr, "Could not open file '%s'\n", path);
    return NULL;
  }
  
  // Read file length
  int i, c;
  i = c = 0;
  while((c=fgetc(temp))!=EOF)i++;
  i++;
  char* content;
  if(ferror(temp))
        puts("I/O error when reading");
  else
    content = (char*)malloc(sizeof(char)*i);
    
  i=c=0;  
  while((c=fgetc(fptr))!=EOF)content[i++]=c; // won't check if buffer overflow...
  content[i]='\0';

  if (ferror(fptr))
        puts("I/O error when reading");
  
  fclose(fptr);
  fclose(temp);
  return content;
}

