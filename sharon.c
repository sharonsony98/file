#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
sem_t P_P;
sem_t Paper_qP;
sem_t Pen_qP;
sem_t D_A;
void doAssignment(char *s)
{
    printf("%s is doing his Assignment\n",s);
}

void *teacher()
{
  while(1)
  {
  sem_wait(&D_A);
   int r=rand()%3;
   //Signal which ever combination was chosen
   if(r==0)
   {
	printf("Teacher has put Pen and Paper on table:\n");
    sem_post(&P_P);
   }
    else if(r==1)
	{
	printf("Teacher has put Paper and QuestionPaper on the table:\n");
    sem_post(&Paper_qP);
	}
    else if(r==2)
    {
    printf("Teacher has put Pen and QuestionPaper on the Table:\n");
    sem_post(&Pen_qP);
	}
   sleep(rand()%5);
 }
}
void *Student_1()
{
  while(1){
    //Wait for our two ingredients
      sem_wait(&P_P);
        doAssignment("Student 1(has QuestionPaper)");
        //Wait for student A to complete his assignment
          sleep(rand()%6);
        //Signal that we are done doing assignment so that the teacher can put down
        //next ingredients.
        printf("Student 1 has done Assignment:\n");
        sem_post(&D_A);
  }

}
void *Student_2()
{
  while(1){
    //Wait for our two ingredients
      sem_wait(&Paper_qP);
        doAssignment("Student 2(has Pen)");
        //wait for student B to complete his assignment
        sleep(rand()%6);
        //Signal that we are done doing assignment so that the teacher can put down
        //next ingredients.
        printf("Student 2 has done Assignment\n");
        sem_post(&D_A);
  }
}
void *Student_3()
{
  while(1){
    //Wait for our two ingredients
      sem_wait(&Pen_qP);
        doAssignment("Student 3(has Paper)");
        //Wait for student C to complete his Assignment
          sleep(rand()%6);

        //Signal that we are done doing assignment so that the teacher can put down
        //next ingredients.
        printf("Student 3 has done Assignment\n");
        sem_post(&D_A);
  }

}
int main() {
   printf("Welcome to Teacher Student Processs Syncronization simulation \n");
   printf("Student 1 has QuestionPaper\n");
   printf("Student 2 has Pen\n");
   printf("Student 3 has Paper\n");
   sem_init(&P_P,0,0);
   sem_init(&Paper_qP,0,0);
   sem_init(&Pen_qP,0,0);
   sem_init(&D_A,0,1);
   pthread_t s1,s2,s3,t;
   pthread_create(&s1,NULL,Student_1,NULL);
   pthread_create(&s2,NULL,Student_2,NULL);
   pthread_create(&s3,NULL,Student_3,NULL);
   pthread_create(&t,NULL,teacher,NULL);
   pthread_join(s1,NULL);
   pthread_join(s2,NULL);
   pthread_join(s3,NULL);
   pthread_join(t,NULL);
  return 0;
}
