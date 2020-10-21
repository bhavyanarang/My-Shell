#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<stdlib.h>

void main(int argc, char const* arg[]){
	char* token=arg[0];
	if(token==NULL){
		struct dirent **dir;
		int n=scandir(".",&dir,0,alphasort);
		int i=0;
		while(i<n){
			char* name;
			name=dir[i]->d_name;
			if(name[0]!='.'){
				printf("%s ",name);
				free(dir[i]);
			}
			i+=1;
		}
		free(dir);
		printf("\n");
	}
	else if(strcmp(token,"-R")){		//recursively print file directories
		struct dirent *dir;
		DIR *d=opendir(".");		//returns pointer of dir type
		if(d==NULL){
			printf("Error as type of directory is null\n");
		}
		else{
			while(dir!=NULL){
				printf("%s ",dir->d_name);
				dir=readdir(d);
			}
		}
		printf("\n");
		free(dir);
		free(d);
	}
	else if(strcmp(token,"-a")){		//print all files including those starting with .
		struct dirent **dir;
		int n=scandir(".",&dir,0,alphasort);
		int i=0;
		while(i<n){
			char* name;
			name=dir[i]->d_name;
			printf("%s ",name);
			free(dir[i]);
			i+=1;
		}
		free(dir);
		printf("\n");

	}
	else{
		printf("Command not supported\n");
	}
}