#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

int ft_strlen_biggest(char *s1, char *s2)
{
	int len1 = ft_strlen(s1);
	int len2 = ft_strlen(s2);

	if (len1 > len2)
		return(len1);
	return (len2);
}

int ft_parsing(char *str)
{
	int i = 0;
	int j = 0;
	char **str_keys = (char **)malloc(sizeof(char *) * 10000);
	int key = 0;
	int open = 0;
	int close = 0;

	while (str[i])
	{
		if (strncmp(&str[i], "</", 2) == 0)
		{
			i = i + 2;
			j = 0;
			while (str[i + j] && strncmp(&str[i + j], ">", 1) != 0
							  && strncmp(&str[i + j], " ", 1) != 0
							  && strncmp(&str[i + j], "\t", 1) != 0)
				j++;
			str_keys[key] = (char *)malloc(sizeof(char) * j + 1);
			str_keys[key] = strncpy(str_keys[key], &str[i], j);
			str_keys[key][j] = '\0';
			i = i + j;
			open ++;
			printf("%s vs %s\n",str_keys[key], str_keys[key - 1]);
			if (strncmp(str_keys[key], str_keys[key - 1], ft_strlen_biggest(str_keys[key],str_keys[key - 1])) == 0)
			{
				free(str_keys[key]);
				str_keys[key] = NULL;
				key --;
				printf("key is %d\n", key);
			}
			else
				return (1);
		}
		else if (strncmp(&str[i], "<", 1) == 0)
		{
			i = i + 1;
			j = 0;
			while (str[i + j] && strncmp(&str[i + j], ">", 1) != 0
							  && strncmp(&str[i + j], " ", 1) != 0
							  && strncmp(&str[i + j], "\t", 1) != 0)
				j++;
			str_keys[key] = (char *)malloc(sizeof(char) * j + 1);
			str_keys[key] = strncpy(str_keys[key], &str[i], j);
			str_keys[key][j] = '\0';
			if (strncmp(str_keys[key], "img", ft_strlen_biggest(str_keys[key], "img")) == 0)
			{
				free(str_keys[key]);
				str_keys[key] = NULL;
			}
			else
			{
				close ++;
				i = i + j;
				key ++;
			}
		}
		i++;
	}
	if (open != close)
		return (1);
	return (0);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	return(ft_parsing(argv[1]));
}
