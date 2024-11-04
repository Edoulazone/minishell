/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:00:29 by eschmitz          #+#    #+#             */
/*   Updated: 2024/11/04 16:56:50 by eschmitz         ###   ########.fr       */
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

/*Path vers .h de libft*/

# include "../libft/libft.h"

/*Error messages*/

# define SYNTAX_ERROR	"minishell: syntax error near unexpected token''\n"
# define SYNTAX_TOKEN	"minishell: syntax error near unexpected token 'newline'\n"

/*Token types*/

# define INPUT		1	//"<"
# define HEREDOC	2	//"<<"
# define TRUNC		3	//">" //je l'appelerai plutot OUTPUT
# define APPEND		4	//">>"
# define PIPE		5	//"|"
# define CMD		6	//"|"	??
# define ARG		7	//"|"	??

/*Exit defines*/

# define EXIT_SUCCESS	0
# define EXIT_FAILURE	1

/*Structures*/

//AST structure
typedef struct s_ast
{
	char			**value;
	int				n_type;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

//Token structure
typedef struct s_token
{
	char			*str;
	int				t_type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

//Environnement structure
typedef struct s_env
{
	char			*content;
	char			*value;
	int				type;
	struct s_env	*next;
}	t_env;

//Shell structure
typedef struct s_shell
{
	int		loop;
	char	*str;
	char	*command;
	char	**commands;
	int		num_commands;
	int		return_value;
	char	*delimiter;
	int		*exit_status; //jai changé en int*
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
// utils.c
char	*ft_strdup(const char *str);
char	*ft_strndup(const char *str, int n);
char	*ft_ssearch(char *str, int c, int flag);

/*************************************
*			   EXECUTOR              *
*************************************/
// exec.c
int 	execute_ast(t_ast *node, t_env **env, t_shell *sh);
int 	is_built_in(t_ast *cmd, t_env **env, t_shell *sh);

// exec_cmd.c
int 	execute_command(t_ast *cmd, t_env *env, t_shell *sh);
void    add_path(t_ast *cmd, t_env *env);

/*************************************
*				LEXER                *
*************************************/

/*************************************
*				PARSER               *
*************************************/
//parsing.c
int		parsing(t_shell *sh);
int		is_command(int type);

/*************************************
*				 AST                 *
*************************************/
// ast.c
t_ast	*make_ast(t_token *tokens);
t_ast	*make_ast_node(char	**value, int type);
char	**get_command(t_token *token);

// ast_utils.c
t_ast	*ast_priority(t_token *tokens, t_ast *origin);

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
void	print_export(t_env *env);

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

//EXEC
int 	is_built_in(t_ast *cmd, t_env **env, t_shell *sh);
int 	execute_ast(t_ast *node, t_env **env, t_shell *sh);

#endif