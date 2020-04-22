/* FILE: bank.c
 * AUTHOR: Christina Hinton
 * DATE: 2/18/20
 * DESCRIPTION: Tests 4 threads with a mutex. Two threads deposit $11 while two threads withdraw $10 ten times
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t m;		//mutex 
pthread_cond_t condW, condD;	//condition
int balance = 0;		//actual balance of bank

void* withdrawl(void *tid);
/* withdrawl
 * INPUT: void * tid: thread id
 * OUTPUT: VOID
 * DESCRIPTION: withdraws $10 from account while it has sufficient funds
*/

void* deposit(void *tid);
/* deposit
 * INPUT: void * tid : thread id
 * OUTPUT: VOID
 * DESCRIPTION: deposits $11 to account 10 times
 */

int main(){

	pthread_t d1, d2,		//deposit threads
		  w1, w2;		//withdraw threads

	//initialize thread variables
	pthread_mutex_init(&m, 0);
	pthread_cond_init(&condD, 0);
	pthread_cond_init(&condW, 0);

	//create threads
	pthread_create(&w1, 0, withdrawl,(void *) 0);
	pthread_create(&d1, 0, deposit, (void *) 0);
	pthread_create(&w2, 0, withdrawl,(void *) 1);
	pthread_create(&d2, 0, deposit,(void *) 1);

	//join threads
	pthread_join(d1, 0);
	pthread_join(w1, 0);
	pthread_join(d2, 0);
	pthread_join(w2, 0);

	//destroy thread variables
	pthread_cond_destroy(&condW);
	pthread_cond_destroy(&condD);
	pthread_mutex_destroy(&m);	

	return 0;
}

//withdraw money
void* withdrawl(void *tid){
	int id = (int)(intptr_t) tid;
	for(int i = 0; i < 10; i++){
		//lock other threads out
		pthread_mutex_lock(&m);
		//wait until account has enough money
		while(balance < 10)
			pthread_cond_wait(&condW, &m);
		int readbalance = balance;
		printf ("At time %d, the balance for withdrawl thread is %d is %d", i, id, balance);
		printf("\n");

		readbalance -= 10;	
		usleep(1);
		//withdraw $10
		balance = readbalance;
		//unlock and send signal
		pthread_cond_signal(&condD);
		pthread_mutex_unlock(&m);
		printf("At time %d, the balanace after withdrawl thread %d is %d", i, id, balance);
		printf("\n");

		usleep(1);
	}
	pthread_exit(0);
}

//deposit money
void* deposit(void *tid){
	int id = (int)(intptr_t) id;
	for(int i = 0; i < 10; i++){
		//lock other threads out
		pthread_mutex_lock(&m);	
		int readbalance = balance;
		printf("At time %d, the balance before depositing thread %d is %d", i, id, balance);
		printf("\n");
		//deposit $11
		readbalance += 11;
		usleep(10);
		balance = readbalance;
		//wake up withdraw and unlock
		pthread_cond_signal(&condW);
		pthread_mutex_unlock(&m);
		printf("At time %d, the balance after depositing thread %d, is %d", i, id, balance);
		printf("\n");
		usleep(10);
	}
	pthread_exit(0);
}


