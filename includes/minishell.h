/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:00:29 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/18 14:55:36 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*Libraries*/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

int	g_exit_status;

/*Error messages*/

# define SYNTAX_ERROR	"minishell: syntax error near unexpected token''\n"
# define SYNTAX_TOK	"minishell: syntax error near unexpected token 'newline'\n"

/*Exit defines*/

# define EXIT_SUCCESS	0
# define EXIT_FAILURE	1

/*******************************************************************
*                                                                  *
*                            STRUCTURES                            *
*                                                                  *
*******************************************************************/

//Environnement structure
typedef struct s_env
{
	char			*content;
	char			*value;
	int				type;
	struct s_env	*next;
}	t_env;

//Enumeration of different possible types of nodes
enum e_char_token
{
	WORD,
	INPUT,
	HEREDOC,
	TRUNC,
	APPEND,
	PIPE,
	CMD,
	REDIR,
};

//AST structure
typedef struct s_ast
{
	int				type;
}	t_ast;

//Node types
typedef struct s_cmd
{
	int				type;
	char			**arg;
	t_env			*env;
}	t_cmd;

typedef struct s_redir
{
	int				type;
	t_ast			*cmd;
	char			*file;
}	t_redir;

typedef struct s_pipe
{
	int				type;
	t_ast			*left;
	t_ast			*right;
}	t_pipe;

//Token structure
typedef struct s_token
{
	char			*content;
	int				t_type;
	struct s_token	*next;
}	t_token;

//Getal structure
typedef struct s_getal
{
	size_t	i;
	size_t	j;
	size_t	x;
	size_t	words;
	char	**final;
}				t_getal;

//Expander environment structure
typedef struct s_env_exp
{
	int		end;
	int		sub;
	int		start;
	int		var_len;
	char	*var;
	char	*expand;
}	t_env_exp;

//Shell structure
typedef struct s_shell
{
	int			loop;
	char		*str;
	char		*command;
	int			num_commands;
	int			return_value;
	char		*delimiter;
	t_env		*env;
	t_token		*expander;
	t_token		*token;
	t_ast		*ast;
	t_env_exp	*env_exp;
}	t_shell;

/*******************************************************************
*                                                                  *
*                            FONCTIONS                             *
*                                                                  *
*******************************************************************/

/*************************************
*				 MAIN                *
*************************************/
// shell_int.c
int			shell_init(t_shell *sh);

// env.c
// int		make_env(t_shell *sh, char **envp);

/*************************************
*				LEXER                *
*************************************/
// lexer.c
int			lex(char *str, t_token **token);

// lexer_utils.c
int			check_qs(int sqs, int dqs, t_token **tokens);
void		new_qs(char c, int *sqs, int *dqs);
int			is_meta(char c, int *sqs, int *dqs);

// verif_lex.c
int			verif_lex(t_token *token);

/*************************************
*		       EXPANDER              *
*************************************/
// expander.c
int			expander(t_shell *sh, t_token **expander);

// expand_heredoc.c
char		*expand_heredoc(char *str);

// expand_quotes.c
char		*expand_sq(char *copy, char *str, int *i);
char		*expand_dq(t_shell *sh, char *copy, char *str, int *i);

// expander_utils.c
char		*ft_substr(char const *s, unsigned int start, size_t len);
t_env_exp	*init_var_exp(void);
t_token		*init_token(void);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
t_env		*get_node(t_env *env, char *var);

// expander_utils2.c
void		check_node_null(t_shell *sh);
char		*ft_realloc(char *ptr, size_t new_size);

// get_word.c
char		*get_word(t_shell *sh, char *str);
char		*join_char(char *str, char c);

// env_var.c
char		*exp_env_var(t_shell *sh, char *copy, char *str, int *i);

/*************************************
*				PARSER               *
*************************************/
// pars.c
t_ast		*parser(t_token **token, t_env *env, int *heredocs, t_shell *sh);
int			ft_lstfind(t_token *token, int type);

// cmd_parser.c
t_ast		*cmd_node(char **arg, t_env *env);
char		**get_arg(t_token *token);

// pipe_parser.c
t_token		*get_next_pipe(t_token *token, t_token *prev);
t_token		*get_previous_pipe(t_token *token);
t_ast		*pipe_node(t_ast *left, t_ast *right);

// redir_parser.c
char		*get_file_type(t_token *token, int *type, int *hd_index);
int			token_is_redir(t_token *token);
t_ast		*redir_node(char *file, t_ast *cmd, int type);
t_token		*get_previous_redir(t_token *token);

// redir_parser2.∫c
int			ft_strcmp2(char *str, char *str_to_find);
int			ft_cmdlen(char *str);
t_token		*ft_delheredoc(t_token **token);
void		ft_del_hdfiles(void);
void		ft_write_hdline(char *str, char *file);

/*************************************
*			   CHECKER               *
*************************************/
// errors.c
int			ft_error(char *str, int n, char var);
void		error(char *str);

/*************************************
*	          BUILT_INS              *
*************************************/
//EXEC echo
void		ft_echo(t_cmd *cmd);
bool		only_n(char *str);
bool		option_new_line(char **args, int *p);

//PWD
void		ft_pwd(t_shell *sh);
char		*find_old_pwd(t_env *env);

//ENV
int			length_untill_c(char *str, char c);
char		*strdup_until_c(char *str, char c);
t_env		*init_env_list(char **env, int i);
void		ft_env(t_env *head);
void		free_env_list(t_env *head);

//PATH
char		*find_home(t_env *env);
char		*find_paths(t_env *env);

//CD
void		ft_cd(t_cmd *cmd, t_env *env, char *path);
void		my_write(int fd, char *str, int flag);

//UNSET
int			special_strcmp(char *env_str, char *check, char c);
int			ft_unset(t_cmd *cmd, t_env **env);
void		remove_env_node(t_env **head, char *check, t_env **save);

//EXPORT
int			valid_arg(char *var);
t_env		*env_var_exists(char *var, t_env *env);
void		ft_export(t_cmd *cmd, t_env **env);
void		append_node(char *var, t_env *env, int sign);
void		update_content(t_env *node, char *new_var, int sign);

// export_print.c
void		sort_array(char **array);
void		fill_env_array(char **array, t_env *env);
char		**env_to_array(t_env *env, int mustsort);
void		print_export(t_env *env);

// export_print2.c
int			is_there_equal(char *str);
void		filler(char **array, t_env *env, int *i);

//EXPORT UTILS
int			exp_strcmp(char *s1, char *s2);
int			plus_exp_strcmp(char *s1, char *s2);

//UTILS
char		*safe_strdup(char *str);
void		*safe_malloc(unsigned int size);
void		free_split(char **mem);
char		*safe_strjoin(char *s1, char *s2);

//EXIT
void		ft_exit(t_cmd *node, t_shell *sh);
long long	my_atoi(const char *str);

/*************************************
*		  	  EXECUTOR               *
*************************************/
// exec.c
void		exit_status(void);
void		pre_ast(t_ast *node, t_env **env, t_shell *sh);
void		execute_ast(t_ast *node, t_env **env, t_shell *sh);
int			is_built_in(t_cmd *cmd, t_env **env, t_shell *sh);

//EXEC_CMD
int			execute_command(t_cmd *cmd, t_env *env);
void		add_path(t_cmd *cmd, t_env *env);
void		decrement_shell_level(t_env *env);

//EXEC_PIPE
void		handle_pipe(t_pipe *node, t_env **env, t_shell *sh);
void		set_exit_status(int status);

//EXEC_INPUT
void		handle_input(t_redir *node, t_env **env, t_shell *sh);

//EXEC_TRUNC_APPEND
void		handle_trunc_append(t_redir *node, t_env **env, t_shell *sh);

//SIGNAUX
void		rl_clear_history(void);
void		rl_replace_line(const char *text, int clear_undo);
void		handle_ctrl_c(int signum);
void		child_ctrl_c(int signum);
void		ctrl_slash(int signum);
void		handle_signal(int process);

/*************************************
*				 FREE                *
*************************************/
//free.c
void		free_token(t_token *token);
void		ft_free(t_shell *sh);

//free_ast.c
void		free_ast(t_ast *node);

/*************************************
*				UTILS                *
*************************************/
//libft_utils.c
void		ft_lstadd_back(t_token **token, t_token *new);
t_token		*ft_lstlast(t_token *lst);
t_token		*ft_lstnew(void *content, int type);
size_t		ft_strlen(const char *src);
void		ft_lstclear(t_token **lst, void (*del)(void *));

//libft_utils_2.c
char		*ft_strdup(const char *str);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strndup(const char *str, int n);
char		*ft_ssearch(char *str, int c, int flag);

//libft_utils_3.c
char		*ft_itoa(int n);
size_t		ft_strlcpy(char *dest, const char *src, size_t dstsize);
char		*ft_strchr(const char *s, int c);
void		ft_putstr_fd(char *s, int fd);

//ft_split.c
char		**ft_split(char const *s, char c);

//utils.c
int			countheredocs(t_token *token);
int			ft_lstsize(t_token *lst);
int			is_quote(char c);
int			ft_isdigit(int c);
void		list_append(t_token *token, char *content, int type);

// utils2.c
int			token_is_redir(t_token *token);

#endif
