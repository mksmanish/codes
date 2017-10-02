#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

sem_t ch[5];
sem_t room;
void *phil(void *arg)
{    
     int i=(int)arg;
     int left,right;
     printf("\n%d philosopher is created\n",i);
     sleep(10);
     left=i;
     right=(i+1)%5;
     printf("\n%d philosopher is hungry\n",i);
     sem_wait(&room);
     sem_wait(&ch[left]);
     sem_wait(&ch[right]);
     printf("\n%d philosopher is eating\n",i);
     sleep(5);
     sem_post(&ch[right]);
     sem_post(&ch[left]);
     printf("\n%d philosopher is completed\n",i);
    sem_post(&room);
}

main()
{
     pthread_t id[5];
     int i;
     sem_init(&room,0,4);
     for(i=0;i<5;i++)
      {
           sem_init(&ch[i],0,1);
      }
    for(i=0;i<5;i++)
      {
           pthread_create(&id[i],NULL,phil,(void *)i);
           sleep(1);

      }
    for(i=0;i<5;i++)
      {
           pthread_join(id[i],NULL);
           sleep(1);

      }
}


    
