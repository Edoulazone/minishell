/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:00:29 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/10 19:04:40 by eschmitz         ###   ########.fr       */
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

/*Error messages*/

# define SYNTAX_ERROR	"minishell: syntax error near unexpected token''\n"
# define SYNTAX_TOKEN	"minishell: syntax error near unexpected token 'newline'\n"

/*Token types*/

// # define WORD		0
// # define INPUT		1	//"<"
// # define HEREDOC	2	//"<<"
// # define TRUNC		3	//">" //je l'appelerai plutot OUTPUT
// # define APPEND		4	//">>"
// # define PIPE		5	//"|"
// # define CMD		6	//"|"	??
// # define REDIR		7	//"|"

/*Exit defines*/

# define EXIT_SUCCESS	0
# define EXIT_FAILURE	1

/*Structures*/

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
typedef struct	s_ast
{
	int				type;
}	t_ast;

//Node types
typedef struct	s_cmd
{
	int				type;
	char			**arg;
	t_env			*env;
}	t_cmd;

typedef struct	s_redir
{
	int				type;
	t_ast			*cmd;
	char			*file;
}	t_redir;

typedef struct	s_pipe
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
typedef struct	s_env_exp
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
	int			exit_status; //jai changé en int*
	t_env		*env;
	t_token		*expander;
	t_token		*token;
	t_ast		*ast;
	t_env_exp	*env_exp;
}	t_shell;

/*FONCTIONS*/

/*************************************
*				 MAIN                *
*************************************/
// shell_int.c
int		shell_init(t_shell *sh);

// env.c
// int		make_env(t_shell *sh, char **envp);

/*************************************
*				UTILS                *
*************************************/
//libft_utils.c
void	ft_lstadd_back(t_token **token, t_token *new);
t_token	*ft_lstlast(t_token *lst);
t_token	*ft_lstnew(void *content, int type);
size_t	ft_strlen(const char *src);
void	ft_lstclear(t_token **lst, void (*del)(void *));

//libft_utils_2.c
char	*ft_strdup(const char *str);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strndup(const char *str, int n);
char	*ft_ssearch(char *str, int c, int flag);

//libft_utils_3.c
char	*ft_itoa(int n);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
void	ft_putstr_fd(char *s, int fd);

//ft_split.c
char	**ft_split(char const *s, char c);

//utils.c
int		countheredocs(t_token *token);
int		ft_lstsize(t_token *lst);
int		is_quote(char c);
int		ft_isdigit(int c);
void	list_append(t_token *token, char *content, int type);

/*************************************
*				LEXER                *
*************************************/
// lexer.c
int		lex(char *str, t_token **token, t_shell *sh);

// lexer_utils.c
void	check_qs(int sqs, int dqs, t_token **tokens);
void	new_qs(char c, int *sqs, int *dqs);
int		is_meta(char c, int *sqs, int *dqs);

// trimmer.c
void	trim_and_expand(t_token *tokens, t_shell *sh);

// verif_lex.c
int		verif_lex(t_shell *sh);

/*************************************
*		       EXPANDER              *
*************************************/
// expander.c
int		expander(t_shell *sh, t_token **expander);

// expand_heredoc.c
char	*expand_heredoc(char *str);

// expand_quotes.c
char	*expand_sq(char *copy, char *str, int *i);
char	*expand_dq(t_shell *sh, char *copy, char *str, int *i);

// expander_utils.c
char		*ft_substr(char const *s, unsigned int start, size_t len);
t_env_exp	*init_var_exp(void);
t_token		*init_token(void);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
t_env		*get_node(t_env *env, char *var);

// expander_utils2.c
void	check_node_null(t_shell *sh);
char	*ft_realloc(char *ptr, size_t new_size);

// get_word.c
char	*get_word(t_shell *sh, char *str);
char	*join_char(char *str, char c);

// env_var.c
char	*exp_env_var(t_shell *sh, char *copy, char *str, int *i);

/*************************************
*				PARSER               *
*************************************/
// pars.c
t_ast	*parser(t_token **token, t_env *env, int *heredocs, t_shell *sh);
int		ft_lstfind(t_token *token, int type);
void	ast_printer(t_ast *node, int level);

//cmd_parser.c
t_ast	*cmd_node(char **arg, t_env *env, t_token **token);
char	**get_arg(t_token *token);

//pipe_parser.c
t_token	*get_next_pipe(t_token *token, t_shell *sh);
t_token	*get_previous_pipe(t_token *token);
t_ast	*pipe_node(t_ast *left, t_ast *right, t_token **token);

//redir_parser.c
char 	*get_file_type(t_token *token, int *type, int *hd_index);
int		token_is_redir(t_token *token);
t_ast	*redir_node(char *file, t_ast *cmd, int type, t_token **token);
t_token	*get_previous_redir(t_token *token);

/*************************************
*				 FREE                *
*************************************/
//free.c
void    free_token(t_token *token);
void    ft_free(t_shell *sh);

//free_ast.c
void	free_ast(t_ast *node);

// /*************************************
// *				 AST                 *
// *************************************/
// // ast.c
// t_ast	*make_ast(t_token *tokens);
// t_ast	*make_ast_node(char	**value, int type);
// char	**get_command(t_token *token);

// // ast_utils.c
// t_ast	*ast_priority(t_token *tokens, t_ast *origin);
// t_ast	*pipe_left(t_token *tokens);

/*************************************
*			   CHECKER               *
*************************************/
//errors.c
int		ft_error(char *str, int n, char var);
void	error(char *str);

/*************************************
*	  \/      BUILT_INS      \/      *
*************************************/
//EXEC echo
void	ft_echo(t_cmd *cmd);
bool 	only_n(char *str);
bool	option_new_line(char **args, int *p);

//PWD
void	ft_pwd(t_shell *sh);

//ENV
int		length_untill_c(char *str, char c);
char	*strdup_until_c(char *str, char c);
t_env	*init_env_list(char **env);
void	ft_env(t_env *head);
void	free_env_list(t_env *head);

//PATH
char	*find_home(t_env *env);
char	*find_paths(t_env *env);

//CD
void	ft_cd(t_cmd *cmd, t_env *env);

//UNSET
int		special_strcmp(char *env_str, char *check, char c);
int		ft_unset(t_cmd *cmd, t_env **env);
void	remove_env_node(t_env **head, char *check, t_env **save);

//EXPORT
int		valid_arg(char *var);
t_env	*env_var_exists(char *var, t_env *env);
void	ft_export(t_cmd *cmd, t_env **env);
void	append_node(char *var, t_env *env, int sign);
void	update_content(t_env *node, char *new_var, int sign);

//EXPORT_PRINT
void	sort_array(char **array);
void	fill_env_array(char **array, t_env *env);
char    **env_to_array(t_env *env);

//EXPORT UTILS
int		exp_strcmp(char *s1, char *s2);
int		plus_exp_strcmp(char *s1, char *s2);

//UTILS
char	*safe_strdup(char *str);
void	*safe_malloc(unsigned int size);
void	free_split(char **mem);
char	*safe_strjoin(char *s1, char *s2);

/*************************************
*		\/	  EXECUTOR     \/        *
*************************************/
// exec.c
void	pre_ast(t_ast *node, t_env **env, t_shell *sh);
int 	execute_ast(t_ast *node, t_env **env, t_shell *sh);
int 	is_built_in(t_cmd *cmd, t_env **env, t_shell *sh);

//EXEC_CMD
int 	execute_command(t_cmd *cmd, t_env *env, t_shell *sh);
void    add_path(t_cmd *cmd, t_env *env);
//void    handle_cmd(t_cmd *node, t_env **env, t_shell *sh); //obsolete

//EXEC_HEREDOC
void	handle_heredoc(t_redir *node, t_env **env, t_shell *sh);

//EXEC_PIPE
void	decoupage_left_pipe(int *pipe_fd, t_pipe *node, t_env **env, t_shell *sh);
void	decoupage_right_pipe(int *pipe_fd, t_pipe *node, t_env **env, t_shell *sh);
void    handle_pipe(t_pipe *node, t_env **env, t_shell *sh);

//EXEC_INPUT
void    handle_input(t_redir *node, t_env **env, t_shell *sh);

//EXEC_TRUNC_APPEND
void    handle_trunc_append(t_redir *node, t_env **env, t_shell *sh);

//print's du debugging
void	print_simple_ast(t_ast *root);
void	print_export(t_env *env);
void    print_full_command(t_cmd *node);
void	print_value(char **arg);

//HARDCODE TESTING
t_ast *hard_ast1(t_shell *sh);
t_ast *hard_ast2(t_shell *sh);
t_ast *hard_ast3(t_shell *sh);
t_ast *hard_ast4(t_shell *sh);
t_ast *hard_ast5(t_shell *sh);
t_ast *hard_ast6(t_shell *sh);

#endif
