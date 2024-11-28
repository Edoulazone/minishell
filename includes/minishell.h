/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:00:29 by eschmitz          #+#    #+#             */
/*   Updated: 2024/11/28 14:12:13 by eschmitz         ###   ########.fr       */
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

// //List structure
// typedef struct s_list
// {
// 	void			*content;
// 	int				type;
// 	struct s_list	*next;
// }					t_list;

//Shell structure
typedef struct s_shell
{
	int		loop;
	char	*str;
	char	*command;
	int		num_commands;
	int		return_value;
	char	*delimiter;
	int		exit_status; //jai changé en int*
	t_env	*env;
	t_token	*token;
	t_ast	*ast;
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
void	ft_lstadd_back(t_shell *sh, t_token *new);
t_token	*ft_lstlast(t_token *lst);
t_token	*ft_lstnew(void *content, int type);
size_t	ft_strlen(const char *src);
void	ft_lstclear(t_token *lst, void (*del)(void *));

//libft_utils_2.c
char	*ft_strdup(const char *str);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strndup(const char *str, int n);
char	*ft_ssearch(char *str, int c, int flag);

//ft_split.c
char	**ft_split(char const *s, char c);

/*************************************
*			   EXECUTOR              *
*************************************/
// exec.c
void	print_value(char **arg);
int 	execute_ast(t_ast *node, t_env **env, t_shell *sh);
int 	is_built_in(t_ast *cmd, t_env **env, t_shell *sh);

// exec_cmd.c
int 	execute_command(t_ast *cmd, t_env *env, t_shell *sh);
void    add_path(t_ast *cmd, t_env *env);

/*************************************
*				LEXER                *
*************************************/
// lexer.c
int		lex(char *str, t_shell *sh);

// lexer_utils.c
void	check_qs(int sqs, int dqs, t_token *tokens);
void	new_qs(char c, int *sqs, int *dqs);
int		is_meta(char c, int *sqs, int *dqs);

// trimmer.c
void	t_trimmer(t_token *tokens, t_shell *sh);

// verif_lex.c
int		verif_lex(t_shell *sh, t_token *token);

/*************************************
*				PARSER               *
*************************************/
// parsing.c
int		parsing(t_shell *sh);
int		is_command(int type);
void	ast_printer(t_ast *node, int level);

//mult_tokens.c
int		verif_tokens(t_shell *sh, t_token *token);

/*************************************
*				 FREE                *
*************************************/
//free.c
void	free_ast(t_ast *node);
void    free_token(t_token *token);
void    ft_free(t_shell *sh);

/*************************************
*				 AST                 *
*************************************/
// ast.c
t_ast	*make_ast(t_token *tokens);
t_ast	*make_ast_node(char	**value, int type);
char	**get_command(t_token *token);

// ast_utils.c
t_ast	*ast_priority(t_token *tokens, t_ast *origin);
t_ast	*pipe_left(t_token *tokens);

/*************************************
*			   CHECKER               *
*************************************/
int		ft_error(char *str, int n, char var);

/*************************************
*	  \/      BUILT_INS      \/      *
*************************************/
//EXEC echo
void	ft_echo(t_ast *cmd);
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
void	ft_cd(t_ast *cmd, t_env *env);

//UNSET
int		special_strcmp(char *env_str, char *check, char c);
int		ft_unset(t_ast *cmd, t_env **env);
void	remove_env_node(t_env **head, char *check, t_env **save);

//EXPORT
int		valid_arg(char *var);
t_env	*env_var_exists(char *var, t_env *env);
void	ft_export(t_ast *cmd, t_env **env);
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

//EXEC_CMD
int 	execute_command(t_ast *cmd, t_env *env, t_shell *sh);
void    add_path(t_ast *cmd, t_env *env);
void    handle_cmd(t_ast *node, t_env **env, t_shell *sh);

//EXEC_HEREDOC
void	handle_heredoc(t_ast *node, t_env **env, t_shell *sh);

//EXEC_PIPE
void	decoupage_left_pipe(int *pipe_fd, t_ast *node, t_env **env, t_shell *sh);
void	decoupage_right_pipe(int *pipe_fd, t_ast *node, t_env **env, t_shell *sh);
void    handle_pipe(t_ast *node, t_env **env, t_shell *sh);

//EXEC_INPUT
void    handle_input(t_ast *node, t_env **env, t_shell *sh);

//EXEC_TRUNC_APPEND
void    handle_trunc_append(t_ast *node, t_env **env, t_shell *sh);

//EXEC
int 	is_built_in(t_ast *cmd, t_env **env, t_shell *sh);
int 	execute_ast(t_ast *node, t_env **env, t_shell *sh);

//print's du debugging
void	print_simple_ast(t_ast *root);
void	print_export(t_env *env);
void    print_full_command(t_ast *node);
void	print_value(char **arg);

#endif
