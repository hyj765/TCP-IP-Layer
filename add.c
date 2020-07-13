#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<netinet/in.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{

 	if(argc <4)
	{
		printf("인자 수가 부족합니다<useranme>  <file1> <file2> \n");
		return 0;
	}

	 uint32_t data1,data2,sum;
	FILE *one,*two;
	char path[200];
	char path2[200]; 
	sprintf(path,"/home/%s/%s",argv[1],argv[2]);
	sprintf(path2,"/home/%s/%s",argv[1],argv[3]);
	char  buffer[512];
	one=fopen(path,"r");
	if(one == NULL)
	{
	printf("file not found...\n");
	return 0;
	}
	two=fopen(path2,"r");
	if(two == NULL)
	{
	printf("file2 not found...\n");
	return 0;
	}

	fread(buffer,4,sizeof(buffer),one);
	
	data1 = strtol(buffer,NULL,16);
	fread(buffer,4,sizeof(buffer),two);	
	

	data2 = strtol(buffer,NULL,16);

	data1=ntohl(data1);
	
	data2=ntohl(data2);
	
	sum = data1 + data2;
       	printf("0x%x\n",data1);

	printf("0x%x\n",data2);

	printf("0x%x\n",sum);



}
