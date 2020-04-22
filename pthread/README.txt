FILE: bank.c
AUTHOR: Christina Hinton
DATE: 2/18/20
DESCRIPTION: tests pthread mutex with 4 threads
		2 deposits, and 2 withdrawls
OVERVIEW:
	main creates 2 deposit threads and 2 withdrawl threads
		to test mutex

	
	void * deposit
		- deposits $11 in account 10 times
		- prints before and after deposit
		- blocks others before accessing balance
		- no wait condition, as there is no reason to NOT deposit
		- after update, releases block and sends signal to withdrawl
		- template taken from assignment page
		- additional reference from pthread notes

	void * withdrawl
		- withdraws $10 from account 10 times
		- prints before and after withdrawl
		- locks thread before any update is made
		- waits if balance is less than 10
		- after update, releases block and sends signal to deposit 
		- template taken from assignment page
		- additional reference from pthread notes

OUTPUT:
	given inputs (11 added 20 times, 10 deducted 20 times)
	
	EXPECTED OUTPUT: (11*20) - (10*20) = $20
	
	ACTUAL OUTPUT: $20 
		
INSTALL: make bank