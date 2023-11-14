#ifndef SHELL_H
#define SHELL_H

/***** MACROS *****/
#define PRINT(c) (write(STDERR_FILENO, c, _strlen(c)))
#define BUFSIZE 10240
#define DELIMITER " \t\r\n\a"

/*** STANDARD LIBRARIES ***/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/limits.h>

/******** STRING HANDLER FUNCTIONS **********/

char *_strncpy(char *dest, char *src, int n);
int _strlen(char *s);
int _putchar(char c);
int _atoi(char *s);
void _puts(char *str);
int _strcmp(char *s1, char *s2);
int _isalpha(int c);
void array_rev(char *arr, int len);
int intlen(int num);
char *_itoa(unsigned int n);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strchr(char *s, char c);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strdup(char *str);

/*********** MEMORY HANDLERS ***********/

void free_env(char **env);
void *fill_an_array(void *a, int el, unsigned int len);
char *_memcpy(char *dest, char *src, unsigned int n);
void *_calloc(unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_all(char **input, char *line);

/****** MISCELLANEOUS AND INPUT FUNCTIONS *******/

char *_getline();
char *handle_space(char *str);
char *handle_enter(char *string);
void handle_hashtag(char *buff);
void prompt(void);
unsigned int parse_delim(char c, const char *str);
char *_strtok(char *str, const char *delim);
int history(char *input);
char **insert_sep(char *input);

/****** FILE ARGUMENT HANDLER FUNCTIONS ******/

void read_file(char *file, char **argv);
void handle_file(char *line, int count, FILE *fp, char **argv);
void exit_bul_for_file(char **cmd, char *line, FILE *fd);

/****** PARSED ARGUMENT HANDLER FUNCTIONS *****/

char **parse_cmd(char *input);
int handle_builtin(char **cmd, int er);
int execute_Args(char **cmd, char *input, int c, char **argv);
void handle_signal(int sig);

/******* ERROR HANDLERS ******/

void _perror(char *input, int counter, char **argv);
void _prerror(char **argv, int c, char **cmd);
void error_file(char **argv, int c);

/****** ENVIRONMENT HANDLERS ******/

extern char **environ;
void new_env(char **envi);
void free_env(char **env);

/****** PRINTING FUNCTIONS *****/

void _p_number(unsigned int n);
void _p_int_number(int n);
int print_echo(char **cmd);

/******* PATH FINDER *******/

int find_path_dir(char **cmd);
char *build(char *token, char *value);
char *_getenv(char *name);

/******* HELP HANDLERS *******/

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);
void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
int display_help(char **cmd, __attribute__((unused)) int st);

/****** BUILTIN COMMAND HANDLERS AND EXECUTE ******/

int check_builtin(char **cmd);
int handle_builtin(char **cmd, int st);
void __exit(char **cmd, char *input, char **argv, int c, int stat);
int _chdir(char **cmd, __attribute__((unused)) int st);
int _penv_var(__attribute__((unused)) char **cmd,
	      __attribute__((unused)) int st);
int _echo(char **cmd, int st);
int _history(__attribute__((unused)) char **c,
	     __attribute__((unused)) int st);

/****** BUILT-IN COMMANDS STRUCT *****/

/**
 * struct _builtin - Defines a struct that contains built-in commands
 * @command: - Built-in command
 * @function: - Pointer to custom functions
 */
typedef struct _builtin
{
	char *command;
	int (*function)(char **line, int st);
} builtin;

#endif /*SHELL_H*/
