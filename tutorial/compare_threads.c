#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//thread

int x = 2;

void	*routine()
{
	x ++;
	sleep(2);
	printf("x == %d\n", x);
}

// void	*routine()
// {
// 	printf("Hello from threads\n");
// 	printf("process id %d\n", getpid());
// 	// sleep(2);
// 	// printf("x == %d\n", x);
// }

int	main(void)
{
	pthread_t	t1;
	pthread_t	t2;


	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (-1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (-1);
	if (pthread_join(t1, NULL) != 0)
		return (-1);
	if (pthread_join(t2, NULL) != 0)
		return (-1);
	return (0);
}

// two same pid
/*
process can  contain multiple threads
BUT thread cannot contain multiple process
*/

/*
in process, forking duplicating all varibales in child process\
but all threads can access same variable, they have common address sppace (variabels)


tradeoff
issue -> some certain issues with certain thread modifying the varibale
*/

