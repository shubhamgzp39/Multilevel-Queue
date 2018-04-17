#include<stdio.h>
#include<unistd.h>

struct process 
{
int p_id ;
int priority ;
int at ;
int bt ;
int rt ;
int processed ;
};

struct process q1[100], q2[100], q3[100] ;

int rear1 = -1 ;
int front1 = -1 ;
int rear2 = -1 ;
int front2 = -1 ;
int rear3 = -1 ;
int front3 = -1 ;


void q1Push(struct process p) {
	if(front1 == -1) {
		front1 = 0 ;
	}
	rear1 = rear1 + 1 ;
	q1[rear1] = p;
}


void q1Pop() {
	front1 = front1 + 1 ;
}


struct process q1Front() {
	return q1[front1] ;
}


void q2Push(struct process p) {
	if(front2 == -1) {
		front2 = 0 ;
	}
	rear2 = rear2 + 1 ;
	q2[rear2] = p ;
}


void q2Pop() {
	front2 = front2 + 1 ;
}


struct process q2Front() {
	return q2[front2] ;
}


void q3Push(struct process p) {
	if(front3 == -1) {
		front3 = 0 ;
	}
	rear3 = rear3 + 1 ;
	q3[rear3] = p ;
}


void q3Pop() {
	front3 = front3 + 1 ;
}


struct process q3Front() {
	return q3[front3] ;
}


void process_creation(int n, struct process p[]) {	
	int i ;
	for(i=0; i<n; i++) {
		printf("Enter Process Id") ;
		scanf("%d",&p[i].p_id) ;
		printf("Enter Process Arrival Time") ;
		scanf("%d",&p[i].at) ;
		printf("Enter Process Burst Time") ;
		scanf("%d",&p[i].bt) ;
		printf("Enter Processes Priority") ;
		scanf("%d",&p[i].priority) ;
		p[i].rt = p[i].bt ;
	}
}


void assignProcessInQueue(int n, struct process p[]) {
	int i ;
	for(i=0; i<n; i++) {
		if((p[i].priority)>=0 && (p[i].priority)<50) {
			q1Push(p[i]) ;
		} else if ((p[i].priority)>=50 && (p[i].priority)<100) {
			q2Push(p[i]) ;
		} else if ((p[i].priority)>=100 && (p[i].priority)<150) {
			q3Push(p[i]) ;
		} 
	}	
}


void disp_front() {

	int i ;
	printf("Process in Queue 1 - ") ;
	for(i=0;i<=rear1;i++) {
		printf("P%d  ",q1[i].p_id) ;
	}
	printf("\nProcess in Queue 2 - ") ;
	for(i=0;i<=rear2;i++) {
		printf("P%d  ",q2[i].p_id) ;
	}
	printf("\nProcess in Queue 3 - ") ;
	for(i=0;i<=rear3;i++) {
		printf("P%d  ",q3[i].p_id) ;
	}
	printf("\n") ;
}


void round_robin(int n, struct process p[]) {
	int i,j,time,remain=n,flag=0,timeQuantum = 4,wt=0,tat=0 ;
	
	printf("\n\nProcess\t\tWaiting Time    Turnaround Time\n\n"); 
  	for(time=0,i=0;remain!=0;) {  	 
	    if((p[i].rt<=timeQuantum) && (p[i].rt)>0) { 
			time+=(p[i].rt); 
	      	(p[i].rt)=0; 
	      	flag=1; 
	    } else if((p[i].rt)>0) { 
			(p[i].rt)-=timeQuantum; 
			time+=timeQuantum; 
	    } if((p[i].rt)==0 && flag==1) { 
		    remain--; 
			printf("Process[%d]\t\t%d\t\t%d\n",p[i].p_id,time-((p[i].at)-(p[i].bt)),time-(p[i].at)); 
		    wt+=time-(p[i].at)-(p[i].bt); 
			tat+=time-(p[i].at); 
		    flag=0; 
	    } if(i==n-1) 
	    	i=0; 
	    else if((p[i+1].at)<=time) 
	    	i++; 
	    else 
	    	i=0; 
	} 
 
}


void fcfs(int n, struct process p[]) {
	float abTime[500],wTime[500],tat_time[500];
	int i = 0 ;
    float aw_time = 0, atat_time = 0;
    wTime[0] = 0;
    tat_time[0] = q3[front3].bt;
    abTime[0] = q3[front3].bt+q3[front3].at;
    for( i = 1 ; i < n ; i++){
        abTime[i] = abTime[i-1] + p[i].bt;
        tat_time[i] = abTime[i] - p[i].at;
        wTime[i] = tat_time[i] - p[i].bt;
    }
    for(i = 0 ; i < n ; i++){
        aw_time = aw_time + wTime[i];
        atat_time = atat_time + tat_time[i];
    }
    printf("\n\t\tWaiting Time    Turnaround Time\n");
    for(i = 0 ; i < n ; i++){
        printf("\nProcess[%d]\t\t%0.2f\t\t%0.2f\n",p[i].p_id,wTime[i],tat_time[i]);
    }
      
}


void priorityScheduling(int n, struct process p[]) {
	int time = 0,largest ;
	struct process temp;
int i,j,sum_bt;
for(i=0;i<n-1;i++)
for(j=i+1;j<n;j++)
{
if(p[i].at>p[j].at)
{
temp=p[i];
p[i]=p[j];
p[j]=temp;
}
}
for(i=0;i<n;i++)
 {
 	p[i].processed=0;
 sum_bt+=p[i].bt;
 }
 p[rear2+1].priority=-9999;
printf("\nProcess\t\tPriority\t\tWaiting Time\t\tTurnaround Time ");
  for(time=q2[front2].at;time<sum_bt;)
  {
    largest=rear2+1;
    for(i=0;i<n;i++)
    {
      if(p[i].at<=time && p[i].processed!=1 && p[i].priority>p[largest].priority)
        largest=i;
    }
      time+=p[largest].bt;
      int ct[100],wt[100],tt[100] ;
  ct[largest]=time;
          wt[largest]=ct[largest]-p[largest].at-p[largest].bt;
    tt[largest]=ct[largest]-p[largest].at;
    p[largest].processed=1;
    
printf("\nProcess[%d]\t\t%d\t\t\t%d\t\t\t%d\t",p[largest].p_id,p[largest].priority,wt[largest],tt[largest]);
}

printf("\n") ;
}


void queueScheduling1() {
	round_robin(rear1+1, q1) ;
}
void queueScheduling2() {
	priorityScheduling(rear2+1, q2) ;
}
void queueScheduling3() {
	fcfs(rear3+1, q3) ;
}

int main() {
	int n ;
	printf("How many process - ") ;
	scanf("%d",&n) ;
	struct process p[n] ;
	process_creation(n, p) ;
	assignProcessInQueue(n, p) ;
	disp_front() ;
	queueScheduling1() ;
	queueScheduling2() ;
	queueScheduling3() ;

}

