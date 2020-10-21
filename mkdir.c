#include<stdio.h>
#include<string.h>
#include <sys/stat.h> 
#include <sys/types.h> 
#include<dirent.h>

char cwd[1000];
void callChdir(char* add){
	int x=chdir(add);
	if(x==-1){
		printf("Error in changing directory to %s\n",add);
	}
	else{
		//for maintaining previous working directory for only "cd" command
		strcpy(cwd,add);
	}
	getcwd(cwd,sizeof(cwd));
	if(cwd==NULL){
		printf("getcwd() error\n");
	}
}
int main(int argc, char const* arg[]){

	char* token=arg[0];
	getcwd(cwd,sizeof(cwd));
	//printf("%s\n",token );
	char stri[105];
	strcpy(stri,arg[1]);

	if(cwd==NULL){
		printf("getcwd() error\n");
	}

	if(token==NULL){
		printf("Argument missing, Try 'mkdir --help' for more information. \n");
	}
	else{
		if(strcmp(token,"--help")==0){
			printf("Help prompt for mkdir \n");
		}
		else if(strcmp(token,"-v")==0){

			char* vari=strtok(stri," ");
			if(strcmp(vari,"mkdir")==0){
				vari=strtok(NULL," ");
				if(strcmp(vari,"-v")==0){
					vari=strtok(NULL," ");
				}
			}
			getcwd(cwd,sizeof(cwd));
			
			while(vari!=NULL){
				struct  stat s={0};
				char temp[1000];
				getcwd(temp,sizeof(temp));
				strcat(temp,"/");
				strcat(temp,vari);

				printf("%s\n",temp );
				int x=mkdir(temp,0777);
				if(x==-1){
					printf("cannot create '%s' directory, it already exist\n",vari);
					vari=strtok(NULL," ");
				}
				else{
					printf("directory %s created\n",vari);
					vari=strtok(NULL," ");
				}
			}
		}
		else{

			char* vari=strtok(stri," ");
			if(strcmp(vari,"mkdir")==0){
				vari=strtok(NULL," ");
			}
			getcwd(cwd,sizeof(cwd));
			
			while(vari!=NULL){
				struct  stat s={0};
				char temp[1000];

				getcwd(temp,sizeof(temp));
				strcat(temp,"/");
				strcat(temp,vari);

				int x=mkdir(temp,0777);
				if(x==-1){
					printf("cannot create directory, it already exist\n");
				}
				else{
					
					vari=strtok(NULL," ");
				}
			}
			
		}

	}
	return 0;
}