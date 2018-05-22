/* The header files                               */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>

typedef struct
{
  int total_process,tq;
  int bt[5],pr[5],at[5];
} parm;

/* The maximum number of threads                  */
#define MAX_THREADS 5

/*FCFS Algorithm*/
void *FCFS(void *arg)
{
	sleep(10);	
	parm *p = (parm *) arg;
	int wt[20],tat[20];
        float avwt=0,avtat=0;
	int i,j;
	wt[0]=0;    //waiting time for first process is 0
 	FILE *f = fopen("FCFS.txt","w");
	if(f==NULL)
	{
		printf("Error");
	}
        else{
    	//calculating waiting time
   	 for(i=1;i<p->total_process;i++)
    	{
       	 wt[i]=0;
       	 for(j=0;j<i;j++)
	{
            wt[i]+=p->bt[j];
	}
	}
    	printf("\n\nFCFS\t");
	fprintf(f,"\nFCFS\t");
    	printf("\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time");
	fprintf(f,"\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time");
	
	 
    	//calculating turnaround time
    	for(i=0;i<p->total_process;i++)
    	{
       	 tat[i]=p->bt[i]+wt[i];
       	 avwt+=wt[i];
         avtat+=tat[i];
       	 printf("\nP[%d]\t\t%d\t\t%d\t\t%d",i+1,p->bt[i],wt[i],tat[i]);
	 fprintf(f,"\nP[%d]\t\t%d\t\t%d\t\t%d",i+1,p->bt[i],wt[i],tat[i]);
        }
 
   	 avwt/=(float)i;
   	 avtat/=(float)i;
    	printf("\nAverage Waiting Time:%f",avwt);
	fprintf(f,"\n\nAverage Waiting Time:%f",avwt);    	
	printf("\nAverage Turnaround Time:%f",avtat);
	fprintf(f,"\nAverage Turnaround Time:%f",avtat);	
	}
	fclose(f);
}
/*SJF Algorithm*/
void *SJF(void *arg)
{
	sleep(25);
	parm *p = (parm *) arg;
	int wt[20],tat[20],p1[20];
	int i,j,total=0,pos,temp;
        float avg_wt,avg_tat;
	FILE *f = fopen("SJF.txt","w");
	if(f==NULL)
	{
		printf("Error");
	}
        else{
	
	//sorting burst time in ascending order using selection sort
    for(i=0;i<p->total_process;i++)
    {
        pos=i;
        for(j=i+1;j<p->total_process;j++)
        {
            if(p->bt[j]<p->bt[pos])
                pos=j;
        }
 
        temp=p->bt[i];
        p->bt[i]=p->bt[pos];
        p->bt[pos]=temp;
 
        temp=p1[i];
        p1[i]=p1[pos];
        p1[pos]=temp;
    }
 
    wt[0]=0;            //waiting time for first process will be zero
 
    //calculate waiting time
    for(i=1;i<p->total_process;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=p->bt[j];
 
        total+=wt[i];
    }
 
    avg_wt=(float)total/p->total_process;      //average waiting time
    total=0;
    printf("\n\nSJF");
    fprintf(f,"\nSJF");
    printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    fprintf(f,"\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for(i=0;i<p->total_process;i++)
    {
        tat[i]=p->bt[i]+wt[i];     //calculate turnaround time
        total+=tat[i];
        printf("\np[%d]\t\t  %d\t\t    %d\t\t\t%d",i+1,p->bt[i],wt[i],tat[i]);
	fprintf(f,"\np[%d]\t\t  %d\t\t    %d\t\t\t%d",i+1,p->bt[i],wt[i],tat[i]);
    }
 
    avg_tat=(float)total/p->total_process;     //average turnaround time
    printf("\nAverage Waiting Time=%f",avg_wt);
    fprintf(f,"\n\nAverage Waiting Time=%f",avg_wt);
    printf("\nAverage Turnaround Time=%f\n",avg_tat);
    fprintf(f,"\nAverage Turnaround Time=%f\n",avg_tat);
    }
    fclose(f);
} 
 /*RR Algorithm*/
void *RR(void *arg)	
{
	sleep(5);
	parm *p = (parm *) arg;
	int rem_bt[5], wt[5], tat[5], total_wt=0, total_tat=0;
	int i;
	float avg_wt,avg_tat=0;
	FILE *f = fopen("RR.txt","w");
	if(f==NULL)
	{
		printf("Error");
	}
        else
	{ 
    		for (i = 0 ; i < p->total_process ; i++)
        		rem_bt[i] =  p->bt[i];
 
    		int t = 0;
    		while (1)
    		{
        		int flag=0;
        		for (i = 0 ; i < p->total_process; i++)
        		{
            			if (rem_bt[i] > 0)
           			{
                			flag = 1; // There is a pending process
                			if (rem_bt[i] > p->tq)
                			{
                    				t += p->tq;
                    				rem_bt[i] -= p->tq;
                			}
                
                			else
                			{
                    				t = t + rem_bt[i];
						wt[i] = t - p->bt[i];
 						rem_bt[i] = 0;
                			}
            			}
        		}
 
        // If all processes are done
        		if (flag == 0)
          			break;
    		}

    		for (i = 0; i < p->total_process ; i++)
        		tat[i] = p->bt[i] + wt[i];
		printf("\n\nRR");
		fprintf(f,"\n\nRR");
    		printf("\nProcesses  Burst time  Waiting time  Turn around time\n");
		fprintf(f,"\nProcesses  Burst time  Waiting time  Turn around time\n");
    		for (i=0; i<p->total_process; i++)
    		{
        		total_wt = total_wt + wt[i];
        		total_tat = total_tat + tat[i];
        		printf("P[%d] \t\t %d \t\t %d \t\t %d \n",i+1 ,p->bt[i] ,wt[i] ,tat[i]);
			fprintf(f,"P[%d] \t\t %d \t\t %d \t\t %d \n",i+1 ,p->bt[i] ,wt[i] ,tat[i]);
    		}
 
    		printf( "Average waiting time = %f",(float)total_wt / (float)p->total_process);
		fprintf(f,"\nAverage waiting time = %f",(float)total_wt / (float)p->total_process);
    		printf("\nAverage turn around time = %f",(float)total_tat / (float)p->total_process);
  		fprintf(f,"\nAverage turn around time = %f",(float)total_tat / (float)p->total_process);
    		return 0;
	}
	fclose(f);
}
/*Priority Algorithm*/

void *PS(void *arg)
{
	sleep(20);
	parm *p = (parm *) arg;
	int p1[20],wt[20],tat[20],i,j,total=0,pos,temp;
	float avg_wt,avg_tat;
	FILE *f = fopen("PS.txt","w");
	if(f==NULL)
	{
		printf("Error");
	}
        else{
	for(i-0;i<p->total_process;i++)
	{ 
		p1[i]=i+1;
	}
	for(i=0;i<p->total_process;i++)
       {
        pos=i;
        for(j=i+1;j<p->total_process;j++)
        {
            if(p->pr[j]<p->pr[pos])
                pos=j;
        }
 
        temp=p->pr[i];
        p->pr[i]=p->pr[pos];
        p->pr[pos]=temp;
 
        temp=p->bt[i];
        p->bt[i]=p->bt[pos];
        p->bt[pos]=temp;
 
        temp=p1[i];
        p1[i]=p1[pos];
        p1[pos]=temp;
       }
 
    wt[0]=0;    //waiting time for first process is zero
 
    //calculate waiting time
    for(i=1;i<p->total_process;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=p->bt[j];
 
        total+=wt[i];
    }
 
    avg_wt=(float)total/(float)p->total_process;      //average waiting time
    total=0;
    printf("\n\nPS");
    fprintf(f,"\nPS");
    printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    fprintf(f,"\n\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for(i=0;i<p->total_process;i++)
    {
        tat[i]=p->bt[i]+wt[i];     //calculate turnaround time
        total+=tat[i];
        printf("\nP[%d]\t\t  %d\t\t    %d\t\t\t%d",p1[i],p->bt[i],wt[i],tat[i]);
        fprintf(f,"\nP[%d]\t\t  %d\t\t    %d\t\t\t%d",p1[i],p->bt[i],wt[i],tat[i]);
    }
 
    avg_tat=(float)total/(float)p->total_process;     //average turnaround time
    printf("\nAverage Waiting Time=%f",avg_wt);
    fprintf(f,"\n\nAverage Waiting Time=%f",avg_wt);
    printf("\nAverage Turnaround Time=%f\n",avg_tat);
    fprintf(f,"\nAverage Turnaround Time=%f\n",avg_tat);
    return 0;
    }
    fclose(f);	
}
/*SRTN*/

void *SRTN(void *arg)
{
	sleep(15);
	parm *p = (parm *) arg;
	int temp[10];
	int i, smallest, count = 0, time,j=0;
	double wait_time,turnaround_time,end;
        double wt[10],tat[10];
        float average_waiting_time, average_turnaround_time;
        FILE *f = fopen("SRTN.txt","w");
	if(f==NULL)
	{
		printf("Error");
	}
        else{
	for (i = 0 ; i < p->total_process ; i++)
        		temp[i] =  p->bt[i];
	temp[9] = 9999;  
	printf("\n\nSRTN");
        fprintf(f,"\nSRTN");
        printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time\n");
        fprintf(f,"\n\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time\n");
 
      for(time = 0; count != p->total_process; time++)
      {
            smallest = 9;
            for(i = 0; i < p->total_process; i++)
            {
                  if(p->at[i] <= time && temp[i] < temp[smallest] && temp[i] > 0)
                  {
                        smallest = i;
                  }
            }
            temp[smallest]--;
            if(temp[smallest] == 0)
            {
                  count++;
                  end = time + 1;
                  wait_time = wait_time + end - p->at[smallest] - p->bt[smallest];
		  wt[j]=wait_time;
                  turnaround_time = turnaround_time + end - p->at[smallest];	
		  tat[j]=turnaround_time;
		  j++;
            }
	
      }
	for(i=0;i<p->total_process;i++)
	{
		printf("P[%d] \t\t %d  \t\t %.2f \t\t %.2f\n",i+1 ,p->bt[i],wt[i],tat[i]);
		fprintf(f,"P[%d] \t\t %d  \t\t %.2f \t\t %.2f\n",i+1 ,p->bt[i],wt[i],tat[i]);
	}
      average_waiting_time = wait_time / p->total_process; 
      average_turnaround_time = turnaround_time / p->total_process;
      printf("Average Waiting Time:%lf\n", average_waiting_time);
      fprintf(f,"Average Waiting Time:%lf\n", average_waiting_time);
      printf("Average Turnaround Time:%lf\n", average_turnaround_time);
      fprintf(f,"Average Turnaround Time:%lf\n", average_turnaround_time);
      return 0;
      }
      fclose(f);
}

/*The main function.*/
int main() {
  pthread_t threads[MAX_THREADS];
  int total_processes,tq = 0;
  int bt[10],pt[10],at[10];
  parm      p;
  int i;
      printf("\nCPU Scheduling Algorithms.");
      printf("\n1.RR");
      printf("\n2.FCFS");
      printf("\n3.PS");
      printf("\n4.SRTN");
      printf("\n5.SJF");	
      printf("\nEnter the total numbers of processes:\t");
      scanf("%d", &p.total_process); 

      printf("Enter the burst time for each process: \n");
      for(i=0;i<p.total_process;i++)
    {
        printf("Process[%d]:",i+1);
        scanf("%d",&p.bt[i]);
    }
      printf("\n");
      
       printf("Enter the arrival time for each process: \n");
      for(i=0;i<p.total_process;i++)
    {
        printf("Process[%d]:",i+1);
        scanf("%d",&p.at[i]);
    }
      printf("\n");

	printf("Enter the time quantum:\t"); 
  	scanf("%d",&p.tq); 
	
	printf("\n");

      printf("Enter the priority for each process: \n");
      for(i=0;i<p.total_process;i++)
    {
        printf("Process[%d]:",i+1);
        scanf("%d",&p.pr[i]);
    }

 printf("\nThe process is generating %d threads.\n", MAX_THREADS);			 
  /* Start up thread */
   
  pthread_create(&threads[0], NULL, RR, (void *)&p);  
  pthread_create(&threads[1], NULL, FCFS, (void *)&p);
  pthread_create(&threads[2], NULL, SRTN, (void *)&p); 	
  pthread_create(&threads[3], NULL, PS, (void *)&p); 
  pthread_create(&threads[4], NULL, SJF, (void *)&p); 
  /* Synchronize the completion of each thread.   */
 for (i = 0; i < MAX_THREADS; i++) {
    /* Use man pthread_join to see what it does.  */
    pthread_join(threads[i], NULL);
 }
  exit(0);
}
