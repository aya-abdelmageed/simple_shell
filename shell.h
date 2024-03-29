#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2


#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - for ingly linked list
 * @num: number field
 * @str: string
 * @next: for pointing to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - it contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: string that generated from getline containing arguements
 * @argv: an array of strings that generated from arg
 * @path: string path for the current command
 * @argc: argument for count
 * @line_count: error count
 * @err_num:  error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: for linked list local copy of environ
 * @environ: for custom modifing copy of environ from LL env
 * @history: history node
 * @alias: alias node
 * @env_changed: on if environ was changed
 * @status: return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; 
	int cmd_buf_type; 
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL,\
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


int shell_loop(info_t *, char **);
int builtin_finder(info_t *);
void cmd_finder(info_t *);
void cmd_fork(info_t *);


int check_cmd(info_t *, char *);
char *char_duplicates(char *, int, int);
char *path_finder(info_t *, char *, char *);


int loophsh(char **);


void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);


int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);


char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);


char *_copystr(char *, char *, int);
char *_concatstr(char *, char *, int);
char *_strchr(char *, char);


char **string_split(char *, char *);
char **split_string(char *, char);


char *_memiset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);


int free_pointer(void **);


int interactive(info_t *);
int check_delim(char, char *);
int _isalpha(int);
int _atoi(char *);


int _atoierr(char *);
void print_error(info_t *, char *);
int print_dec(int, int);
char *num_convert(long int, int, int);
void comments_remover(char *);


int _myexit(info_t *);
int _cd(info_t *);
int _help(info_t *);


int _history(info_t *);
int _alias(info_t *);


ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);


void data_clear(info_t *);
void set_data(info_t *, char **);
void free_data(info_t *, int);


char *_getenv(info_t *, const char *);
int _env(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int join_env_list(info_t *);


char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);


char *get_history_of_file(info_t *data);
int history_writes(info_t *data);
int history_reads(info_t *data);
int history_build_list(info_t *data, char *buf, int linecount);
int recount_history(info_t *data);


list_t *add_node(list_t **, const char *, int);
list_t *add_node_from_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list_nodes(list_t **);


size_t list_len(const list_t *);
char **convert_list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t node_index_get(list_t *, list_t *);


int is_chain(info_t *, char *, size_t *);
void chain_checker(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
