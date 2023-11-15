#include "shell.h"

/**
 * _getline - read input from standard input by user
 * Return: the input string
 */
char *_getline()
{
	int index, rd, buffsize = BUFSIZE;
	char c = 0, *buffer, *buf;

	buffer = malloc(buffsize);
	if (buffer == NULL)
	{
		free(buffer);
		return (NULL);
	}
	for (index = 0; c != EOF && c != '\n'; index++)
	{
		fflush(stdin);
		rd = read(STDIN_FILENO, &c, 1);
		if (rd == 0)
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}
		buffer[index] = c;
		if (buffer[0] == '\n')
			return (handle_enter(buffer));
		if (index >= buffsize)
		{
			buffer = realloc(buffer, (buffsize + 2));
			if (buffer == NULL)
			{
				free(buffer);
				return (NULL);
			}
		}
	}
	buffer[index] = '\0';
	buf = handle_space(buffer);
	free(buffer);
	handle_hashtag(buf);
	return (buf);
}

/**
 * handle_enter - Handles newline character input
 * @string: String to be handled
 * Return: Empty string
 */
char *handle_enter(char *string)
{
	free(string);
	return ("\0");
}

/**
 * handle_space - Modifies the input string to remove preceeding whitespaces
 * @str: Input to be modifies
 * Return: Returns the modified string
 */
char *handle_space(char *str)
{
	int index, count = 0;
	char *buffer;

	buffer = malloc(sizeof(char) * (_strlen(str) + 1));
	if (buffer == NULL)
	{
		free(buffer);
		return (NULL);
	}
	for (index = 0; str[index] == ' '; index++)
		;
	for (; str[index + 1] != '\0'; index++)
	{
		buffer[count] = str[index];
		count++;
	}
	buffer[count] = '\0';
	if (buffer[0] == '\0' || buffer[0] == '#')
	{
		free(buffer);
		return ("\0");
	}
	return (buffer);
}

/**
 * handle_hashtag - function that removes everything after '#'
 * @buffer: pointer to input string buffer
 * Return: void
 */
void handle_hashtag(char *buffer)
{
	int index;

	for (index = 0; buffer[index] != '\0'; index++)
	{
		if (buffer[index] == '#' && buffer[index - 1] == ' '
		&& buffer[index + 1] == ' ')
		{
			buffer[index] = '\0';
		}
	}
}
