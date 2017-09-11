#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
 int main()
{
      
     int mk1,mk2,MK3;
     int a,b,c;
     char finame[30];
     char buffer[500];
     system("touch mksk.txt");
     mk1=open("mksk.txt",O_WRONLY);
     printf("Enter the data to enter");
     gets(buffer);
   //  scanf("%c",buffer);
     write(mk1,buffer,strlen(buffer));
     close(mk1);

     printf("Enter the filename to read:");
     scanf("%s",finame);
     
     mk2=open(finame, O_RDONLY);
      if(mk2!=3)
       {


            printf("File does not exists\n");
            exit(0);



       }
     read(mk2,buffer,sizeof(buffer));
     printf("The contents of the file are:\n");
     printf("%s\n",buffer);
     close(mk2);
     return 0;
}
    
