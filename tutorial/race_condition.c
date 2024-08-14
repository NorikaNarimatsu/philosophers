#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int	mails = 0;

/*
race condition:
gcc -S race_condition.c
.L3:
	movl	mails(%rip), %eax
	addl	$1, %eax
	movl	%eax, mails(%rip)
	addl	$1, -4(%rbp)
*/
void	*routine()
{
	int	i;

	i = 0;
	sleep(1);
	while (i < 1000000)
	{
		mails ++;
		// read the values in (int) mails
		// increment
		// write (int) mails
		i++;
	}
}

int	main(void)
{
	pthread_t t1; //create variabel (struct)
	pthread_t t2; //create variabel (struct)

	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (-1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (-1);
	if (pthread_join(t1, NULL) != 0)
		return (-1);
	if (pthread_join(t2, NULL) != 0)
		return (-1);
	printf("NUMBER OF MAIL: %d\n", mails);
	return (0);
}