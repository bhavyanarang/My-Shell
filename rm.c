#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char const* arg[]){
	char* token=arg[0];
	char stri[105];
	strcpy(stri,arg[1]);
	//printf("%s\n",stri);
	if(token==NULL){
		printf("missing operand \n");
	}
	else if(strcmp(token,"-f")==0){		//flag which never raises an error even if file is not present
		char* vari=strtok(stri," ");
		if(strcmp(vari,"rm")==0){
			vari=strtok(NULL," ");
			if(strcmp(vari,"-f")==0){
				vari=strtok(NULL," ");
			}
		}

		while(vari!=NULL){
			remove(vari);
			
			vari=strtok(NULL," ");
		}

	}
	else if(strcmp(token,"-i")==0){		//asks user before very removal

		char* vari=strtok(stri," ");
		if(strcmp(vari,"rm")==0){
			vari=strtok(NULL," ");
			if(strcmp(vari,"-i")==0){
				vari=strtok(NULL," ");
			}
		}

		while(vari!=NULL){
			printf("remove file %s ? Enter 'y' for yes \n",vari);
			char input;
			scanf("%[^\n]%*c",input);
			if(input=='y'){
				remove(vari);
			}
			else{
				return 0;
			}
			vari=strtok(NULL," ");
		}

	}
	else{
		
		char* vari=strtok(stri," ");
		if(strcmp(vari,"rm")==0){
			vari=strtok(NULL," ");
		}

		while(vari!=NULL){
			int x=remove(vari);
			if(x!=0){
				printf("File %s does not exist. \n",vari);
			}
			vari=strtok(NULL," ");
		}

	}
}