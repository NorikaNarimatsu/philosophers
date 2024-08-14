#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void	*roll_dice()
{
	int	value;
	int	*result;

	value = (rand() % 6) + 1;
	result = malloc(sizeof(int));
	*result = value;
	// printf("value is %d\n", value);
	printf("Thread result %p\n", result);
	return ((void *) result);
}

int	main(void)
{
	int			*result;
	srand(time(NULL));
	pthread_t	th;

	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
		return (-1);
	if (pthread_join(th, (void**) &result) != 0)
		return (-1);
	printf("Main result %p\n", result);
	printf("Result is %d\n", *result);
	free(result);
	return (0);
}
