#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>


int rc=0;
sem_t m,wrt;

void *reader(void *arg)
{
    int i=(int)arg;
    printf("\n%d reader is created\n",i);
    sleep(10);
    sem_wait(&m);
    rc++;
    if(rc==1)
    sem_wait(&wrt);
    sem_post(&m);
    printf("\n%d reader is reading\n",i);
    sleep(5);
    sem_wait(&m);
    rc--;
    if(rc==0)
    sem_post(&wrt);
    sem_post(&m);
    printf("\n%d reader is completed\n",i);
}

void *writer(void *arg)
{
    int i=(int)arg;
    printf("\n%d writer is created\n",i);
    sleep(10);
    sem_wait(&wrt);
    printf("\n%d writer is writing\n",i);
    sleep(5);
    sem_post(&wrt);
    printf("\n%d writer is completed\n",i);
}

main()
{
    pthread_t r[5],w[5];
    sem_init(&m,0,1);
    sem_init(&wrt,0,1);
   int i;

   for(i=0;i<3;i++)
      {
          pthread_create(&w[i],NULL,writer,(void *)i);
          sleep(1);
          pthread_create(&r[i],NULL,reader,(void *)i);
          sleep(1);
      }

     for(i=0;i<3;i++)
      {
          pthread_join(w[i],NULL);
          pthread_join(r[i],NULL);
      }
}
