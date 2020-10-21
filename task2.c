#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
char cwd[1000];
char prevWorkingDirectory[1000];
int historyLines=0;

void callExit(){
	printf("Exiting.\n");
	exit(0);
}
void callGetcwd(){
	getcwd(cwd,sizeof(cwd));
	if(cwd==NULL){
		printf("getcwd() error\n");
	}
}
int checkInternalCommand(char* token){
	if(strcmp(token,"cd")==0 || strcmp(token,"echo")==0 || strcmp(token,"history")==0 || strcmp(token,"pwd")==0 || strcmp(token,"exit")==0){
		return 1;
	}
	else{
		return 0;
	}
}
int checkExternalCommand(char* token){
	if(strcmp(token,"ls")==0 || strcmp(token,"cat")==0 || strcmp(token,"date")==0 || strcmp(token,"rm")==0 || strcmp(token,"mkdir")==0){
		return 1;
	}
	else{
		return 0;
	}
}
void callChdir(char* add){
	int x=chdir(add);
	if(x==-1){
		printf("Error in changing directory to %s\n",add);
	}
	else{
		//for maintaining previous working directory for only "cd" command
		strcpy(prevWorkingDirectory,cwd);Step 4: Now we will set up the remote, which tells git where the repository is located.
		strcpy(cwd,add);
	}
}
void cd(char* argument){
	if(argument==NULL || strcmp(argument,"-")==0){
		//getenv command gives the path to directory with environment variable name as mentioned
		// this case is for cd
		//go to previous working directory
		callChdir(prevWorkingDirectory);
	}
	else if(strcmp("..",argument)==0){
		callChdir("../");				
		//to go to parent directory
	}
	else if(strcmp("~",argument)==0){	
	//go to home directory
		callChdir(getenv("HOME"));		
	}
	else{
		if(strcmp("-L",argument)==0 || strcmp("-P",argument)==0){
			argument=strtok(NULL," ");
			if(argument==NULL){
				callChdir(getenv("HOME"));
			}
			else{
				callChdir(argument);
			}
		}
		else{
			callChdir(argument);			
			//go to specified directory if error then it is displayed in
		}								
		//callChdir itslef
	}
}
void pwd(char* argument){
	if(argument!=NULL){
		if(strcmp(argument,"-L")==0){
			printf("%s\n",cwd);
		}
		else if(strcmp(argument,"--help")==0){
			FILE* help=fopen("/home/bhavya/Desktop/os/assign1/My-Shell/pwdhelp.txt","r");
			char out[1000];
			while(fgets(out,sizeof(out),help)!=NULL){
				fputs(out,stdout);
			}
			fclose(help);
		}
		else{
			printf("Command not found \n");
		}
	}
	else{
		printf("%s\n",cwd);
	}
}
void history(char* argument){
	if(argument==NULL){
		FILE* his=fopen("/home/bhavya/Desktop/os/assign1/My-Shell/historystore.txt","r");
		char out[1000];
		int line=0;						
		//to read history
		while(fgets(out,sizeof(out),his)!=NULL){
			line+=1;
			printf(" %d\t",line);
			fputs(out,stdout);
		}
		fclose(his);
	}
	else{
		if(strcmp(argument,"-c")==0){	
		//to clear history
			FILE* his=fopen("/home/bhavya/Desktop/os/assign1/My-Shell/historystore.txt","w");
			fclose(his);
			historyLines=0;
		}
		else if(strcmp(argument,"-s")==0){
		//to add argument after -s to another line in history
			argument=strtok(NULL," ");
			FILE* his=fopen("/home/bhavya/Desktop/os/assign1/My-Shell/historystore.txt","a");
			while(argument!=NULL){
				fprintf(his, "%s ",argument);
				argument=strtok(NULL," ");
			}
			fprintf(his,"%s\n","");
			fclose(his);
			historyLines+=1;
		}
		else if(strcmp(argument,"--help")==0){
			FILE* help=fopen("/home/bhavya/Desktop/os/assign1/My-Shell/historyhelp.txt","r");
			char out[1000];
			while(fgets(out,sizeof(out),help)!=NULL){
				fputs(out,stdout);
			}
			fclose(help);
		}
		else{
			printf("Command not in history \n");
		}
	}
}
void exitt(char* token){
	if(token==NULL){
		exit(0);
	}
	else if(strcmp(token,"--help")==0){
		printf("Press 'exit' for exiting\n");
	}
	
	else{
		printf("Invalid command \n");
	}
}
void maintainHistoryStore(char* argument){
	FILE* his=fopen("/home/bhavya/Desktop/os/assign1/My-Shell/historystore.txt","a");
	fprintf(his, "%s\n",argument);
	fclose(his);
	historyLines+=1;
}
void echo(char* token){
	if(token==NULL){
		printf("\n");
	}
	else if(strcmp(token,"--help")==0){
		printf("Press echo and a and argument after it\n");
	}
	else{
		while(token!=NULL){
			printf("%s ",token);
			token=strtok(NULL," ");
		}
		printf("\n");
	}

}
void callInternalCommand(char* token){
	if(strcmp(token,"cd")==0){
		token=strtok(NULL," ");
		cd(token);

	}
	else if(strcmp(token,"echo")==0){
		token=strtok(NULL," ");
		echo(token);
	}
	else if(strcmp(token,"history")==0){
		token=strtok(NULL," ");
		history(token);
	}
	else if(strcmp(token,"pwd")==0){
		token=strtok(NULL," ");
		pwd(token);
	}
	else if(strcmp(token,"exit")==0){
		token=strtok(NULL," ");
		exitt(token);
	}

}
void callExternalCommand(char* token,char input[]){

	if(strcmp(token,"ls")==0){
		token=strtok(NULL," ");
		execl("/home/bhavya/Desktop/os/assign1/My-Shell/ls",token,NULL);
	}
	else if(strcmp(token,"cat")==0){
		token=strtok(NULL," ");
		execl("/home/bhavya/Desktop/os/assign1/My-Shell/cat",token,input,NULL);
	}
	else if(strcmp(token,"date")==0){
		token=strtok(NULL," ");
		
		execl("/home/bhavya/Desktop/os/assign1/My-Shell/date",token,NULL);
	}
	else if(strcmp(token,"rm")==0){
		token=strtok(NULL," ");
		execl("/home/bhavya/Desktop/os/assign1/My-Shell/rm",token,input,NULL);
		
	}
	else if(strcmp(token,"mkdir")==0){
		token=strtok(NULL," ");
		execl("/home/bhavya/Desktop/os/assign1/My-Shell/mkdir",token,input,NULL);
		
	}

}
void callHelp(){
	FILE* help=fopen("/home/bhavya/Desktop/os/assign1/My-Shell/help.txt","r");
	char out[1000];
	while(fgets(out,sizeof(out),help)!=NULL){
		fputs(out,stdout);
	}
	fclose(help);
}


int main(int arg,char const *argc[]){

	printf("Welcome to BHAVYA NARANG's shell\n");

	callGetcwd();
	strcpy(prevWorkingDirectory,cwd);
	
	while(1){
		callGetcwd();
		printf("%s ~$ ",cwd);
		char input[100];
		char nakli[105]="";

		scanf("%[^\n]%*c",input);
		maintainHistoryStore(input);

		strcat(nakli,input);
		strcat(nakli," ");

		char* token;
		token=strtok(input," ");

		if(checkInternalCommand(token)==1){
			callInternalCommand(token);
		}

		else if(checkExternalCommand(token)==1){
			pid_t pid;
			pid=fork();

			if(pid==0){
				//child process

				callExternalCommand(token,nakli);
				exit(0);
			}
			else if(pid>0){
				//parent process
				waitpid(0,NULL,0);
				//waiting for child process to end
			}
			else{
				printf("Error in forking\n");
			}

		}

		else{
			if(strcmp(token,"help")==0){
				callHelp();
			}
			else{
				printf("Command not found\n");
				printf("Enter help for supported commands\n");
			}
		}

	}

	return(0);
}