/* CS 4440 Project 1 - C Shell Brian Kan */
/* Pretty much all commands implemented*/
/* Commands that do not exec are still recorded in history, however */
/* Memory handling is abhorrent, I am not a C programmer */
/* other than that, it works */
/* - Bkan - */

#include <sys/wait.h>

#include <sys/types.h>

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

char *history[MAX_LINE/2+1][MAX_LINE/2+1];


int inArray=0;
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
* By Brian Kan

*/

inArray=0;
int converted=0;

if(!fgets(userInput,MAX_LINE,stdin))

break;

size_t length=strlen(userInput);

if(userInput[length-1]=='\n')

	userInput[length-1]='\0';


split=strtok(userInput," ");

int argc=0;





/* Splitting the String */

while (split != NULL)

  {

    args[argc]=strdup(split);  

    split = strtok (NULL," ");

    argc++;

  }

args[argc]=NULL;
if(args[0]==NULL||argc<1)
	printf("%s","");
else if(strcmp("&",args[argc-1])==0){
	inArray=1;
	args[argc-1]='\0';
}
/* Save History Function??? */
if(args[0]==NULL)
	printf("%s","");
else if(strcmp("history",args[0])==0);
else if(strcmp("!!",args[0])==0){
	if(entry!=0){
		for(historyC=0;historyC<10;historyC++)
			history[entry][historyC]=history[entry-1][historyC];
	entry++;
	}
}
else if(*args[0]=='!'){
	char subbuff[5];
	strcpy( subbuff,args[0]);
	subbuff[0]='0';
	converted=atoi(subbuff);
	if(!(converted>entry-1||converted<0)){{
		for(historyC=0;historyC<10;historyC++)
			history[entry][historyC]=history[converted][historyC];
		}
	entry++;
	}
}
else{
for(historyC=0;historyC<10;historyC++){ 

		if(args[historyC]!=0)

			history[entry][historyC]=args[historyC];

		else

			history[entry][historyC]="";

		}

	entry++;
}
/* End of Function */



if(args[0]==NULL)

	printf("%s","");

else

if(strcmp("exit",args[0])==0){

	should_run=0;

}

else{

pid_t pid;

pid = fork();

/* Child Process */

if (pid==0){

	if(args[0]==NULL){

	exit(0);

	}

	else if(strcmp("history",args[0])==0){

		int i2,i3;

		if(entry>9){

			for(i2=entry-10;i2<entry;i2++){

			printf("%d:",i2);

			for(i3=0;i3<sizeof(history[i2][i3])-1;i3++){

				printf("%s ",history[i2][i3]);

				}

			printf("\n");

			}

		}

		else if(entry<9&&entry>-1){

			for(i2=0;i2<entry;i2++){

			printf("%d:",i2);

			for(i3=0;i3<sizeof(history[i2][i3])-1;i3++){

				printf("%s ",history[i2][i3]);

				}

			printf("\n");

			}

		}

	}

else if(strcmp("!!",args[0])==0){
	if(entry==0){
		printf("%s","There are no commands!");
	}
	else{
	int i2=0;
	for(i2;i2<10;i2++){

		if(strcmp("",history[entry-2][i2])==0)

			args[i2]=NULL;

		else

			args[i2]=history[entry-2][i2];

		
	}
	}

	printf("\n%s",history[entry-2][0]);

	execvp(history[entry-2][0],args);

}
else if(*args[0]=='!'){
	if(!(converted>entry-1||converted<0)){
		if(entry==0){
		printf("%s","There are no commands!");
		}
		else{
		int i2=0;
		for(i2;i2<10;i2++){

		if(strcmp("",history[converted][i2])==0)

			args[i2]=NULL;

		else

			args[i2]=history[converted][i2];

		
	}
	}

	printf("\n%s",history[converted][0]);

	execvp(history[converted][0],args);
	}
	else
		printf("%s","Invalid Command!");
}
else
	execvp(args[0],args);

	exit(0);

}

/* End of Child Process */

/* Parent Process */

else if(inArray){

	printf("\nNOT WAITING FOR CHILD !!!!!!!!!!!! !!!!!!! \n");
	wait(NULL);
	}
else{

	wait(NULL);

	printf("\nChild Complete\n");

	}

}

/* End of Parent Process */



}



return 0;

}

/* End of the Main */




/* End of the Main2 */





