#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// cc -Wall -Wextra -Werror -pthread test.c -o test

void	*routine()
{
	printf("test from threads\n");
	sleep(3);
	printf("Ending threads\n");
}

int	main(void)
{
	pthread_t t1; //create variabel (struct)
	pthread_t t2; //create variabel (struct)

	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (-1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (-1);
	// pointer to the variable, NULL -> default, actual function to run, argument for function
	if (pthread_join(t1, NULL) != 0) // wait function for thread
		return (-1);
	if (pthread_join(t2, NULL) != 0) // wait function for thread
		return (-1);

	return (0);
}

/*
// creating thread
-> execute functions (routines)

place where API can store the infoprmation about the thread 
-> new variable (type pthread_t)

*/