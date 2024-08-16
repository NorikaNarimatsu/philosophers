#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_list
{
	char			*tag;
	struct s_list	*next;
} t_list;

t_list *ft_create_node(char *tag)
{
	t_list *new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return NULL;
	new_node->tag = strdup(tag);
	new_node->next = NULL;
	return new_node;
}

void push(t_list **stack, char *tag)
{
	t_list *new_node = ft_create_node(tag);
	new_node->next = *stack;
	*stack = new_node;
}

char *pop(t_list **stack)
{
	if (*stack == NULL)
		return NULL;
	t_list *temp = *stack;
	char *popped_tag = temp->tag;
	*stack = (*stack)->next;
	free(temp);
	return popped_tag;
}

// Function to check if two tags match (opening and closing)
int tags_match(char *open_tag, char *close_tag)
{
	// Strip the '/' from the closing tag for comparison
	return strcmp(open_tag, close_tag + 1) == 0;
}

// Function to check if HTML tags are properly closed
int check_html_tags(char *html) {
	t_list *stack = NULL;
	char tag[100];
	int i = 0;
	int j;

	while (html[i] != '\0')
	{
		if (html[i] == '<')
		{
			j = 0;
			i++;
			// Check if tag is properly closed with '>'
			while (html[i] != '>' && html[i] != '\0')
			{
				tag[j++] = html[i++];
			}
			if (html[i] != '>') {
				printf("Error: Tag not properly closed with '>'.\n");
				return 0; // Tag is not properly closed
			}
			tag[j] = '\0';
			if (tag[0] != '/') {  // Opening tag
				push(&stack, tag);
			} else {  // Closing tag
				char *open_tag = pop(&stack);
				if (open_tag == NULL || !tags_match(open_tag, tag))
				{
					printf("Mismatched tag: <%s>\n", tag);
					return 0;
				}
				free(open_tag);  // Free the popped tag after comparison
			}
		}
		i++;
	}
	if (stack != NULL) {
		printf("Unmatched opening tag(s) remaining.\n");
		return 0;
	}

	return 1;
}

int main() {
	char html[] = "<html><body><h1>Title</h1><p>Paragraph</p></body></html>";
	char html_bad[] = "<html><body><h1>Title</h1><p>Paragraph</p></body></html>"; // Missing '>'

	if (check_html_tags(html)) {
		printf("All HTML tags are properly closed.\n");
	} else {
		printf("HTML tags are not properly closed.\n");
	}

	if (check_html_tags(html_bad)) {
		printf("All HTML tags are properly closed.\n");
	} else {
		printf("HTML tags are not properly closed.\n");
	}

	return 0;
}
