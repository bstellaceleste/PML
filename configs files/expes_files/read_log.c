#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define buf_size 512

int main(int argc, char *argv[])
{
	FILE *to_read=fopen("log.txt","r"), *to_write=fopen("to_plot.txt","a+");
	char buf[buf_size]="", *token;
	int nb;

	if(to_read!=NULL && to_write!=NULL){

		while(fgets(buf, buf_size, to_read)!=NULL){

			if(buf[0]!='\n'){
	
				token = strtok(buf, " ");
				token = strtok(NULL, " ");
				nb = atoi(token);
				if(atoi(token)!=0)
					fprintf(to_write,"%s %d\n",argv[1],nb);
			}
		}
	
		fclose(to_write);
		fclose(to_read);
	}
	
}

