#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int	mails = 0;
pthread_mutex_t mutex;

void	*routine()
{
	int	i;

	i = 0;
	while (i < 1000000)
	{
		pthread_mutex_lock(&mutex);
		mails ++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
}

int	main(void)
{
	pthread_t	th[4]; //create variabel (struct)
	int			i;

	pthread_mutex_init(&mutex, NULL); // initialize mutex
	i = 0;
	while (i < 4)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
			perror("Failed to create threads\n");
			return (-1);
		}
		printf("Thread %d has started\n", i);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("Failed to wait threads\n");
			return (-1);
		}
		printf("Thread %d has finished excution\n", i);
		i++;
	}
	pthread_mutex_destroy(&mutex); //destroy mutex
	printf("NUMBER OF MAIL: %d\n", mails);
	return (0);
}
