#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>

#define server_fifo_name "/tmp/ser_fifo"
#define client_fifo_name "/tmp/clt_fifo"
#define __size 10000

typedef struct Exchange_data
{
	pid_t pid;
	char data[__size];
	
}Exchange_data;
int main()
{
	int ser_fd ,clt_fd , clt_id,i=0;
	Exchange_data message ;
	char con_msg[__size],ch;
	mkfifo(client_fifo_name,0777);
	ser_fd = open(server_fifo_name,O_WRONLY);
	
	printf("\n Enter Your message and please press @ to terminate your message : ");
	while((ch = getchar()) && ch != '@')
		con_msg[i++] = ch ;
	con_msg[i] = '\0';
	clt_id = getpid();
	
	strcpy(message.data,con_msg);
	message.pid = clt_id;
	printf("\n The Process no. %d sending the message to server which is : %s",message.pid,message.data);
	write(ser_fd,&message,sizeof(message));
	
	clt_fd = open(client_fifo_name,O_RDONLY);
	read(clt_fd,&message,sizeof(message));
	printf("\n Message Recieved from Server is : %s",message.data);
	return 0;
}
