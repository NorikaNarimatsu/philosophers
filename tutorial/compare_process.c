#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

//process
int	main(void)
{
	int	pid;
	int x;

	x = 2;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		x ++;
	sleep(2);
	printf("x == %d\n", x);
	// printf("Hello from processes\n");
	// printf("process id %d\n", getpid());
	if (pid != 0)
		wait (NULL);
	return (0);
}

// two different pid