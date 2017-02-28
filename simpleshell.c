
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#define MAX_LINE 80 /* The maximum length command */

int main(void)
{
char *args[MAX_LINE/2 + 1]; /* command line arguments */
char userInput[MAX_LINE/2+1];
char copyInput[MAX_LINE/2+1];
char *split;
const char *history[MAX_LINE/2+1][MAX_LINE/2+1];

int historyC=0;
int entry=0;
int should_run = 1; /* flag to determine when to exit program */
while (should_run) {
printf("osh>");
fflush(stdout);
/**
* After reading user input, the steps are:
* (1) fork a child process using fork()
* (2) the child process will invoke execvp()
* (3) if command included &, parent will invoke wait()
*/
if(!fgets(userInput,MAX_LINE,stdin))
break;
size_t length=strlen(userInput);
if(userInput[length-1]=='\n')
	userInput[length-1]='\0';

split=strtok(userInput," ");
int argc=0;

while (split != NULL)
  {

    args[argc]=strdup(split);  
/*    printf ("%s\n",splitArray); */
    split = strtok (NULL," ");
    argc++;
  }
args[argc]=NULL;
/* Save History Function??? */
	int i;
	for(i=0;i<3;i++){
	history[historyC][entry]=args[i];
	historyC++;
}
printf("%s",history[0][0]);
if(strcmp("exit",args[0])==0){
should_run=0;
}
else{
pid_t pid;
pid = fork();
if (pid==0){
execvp(args[0],args);

}
else {
wait(NULL);
printf("Child Complete\n");
}


}

}
return 0;
}
/* End of the Main */

bool intheArray(char text,char *array, int size){
	int i;
	for(i=0;i<size;i++){
		if(0==0)
			return true;
	}
}


/* End of the Main2 */

