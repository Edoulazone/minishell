/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:00:29 by eschmitz          #+#    #+#             */
/*   Updated: 2024/10/25 15:43:18 by eschmitz         ###   ########.fr       */
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

/*Error messages*/

# define SYNTAX_ERROR	"minishell: syntax error near unexpected token''\n"
# define SYNTAX_TOKEN	"minishell: syntax error near unexpected token 'newline'\n"

/*Token types*/

# define INPUT		1	//"<"
# define HEREDOC	2	//"<<"
# define TRUNC		3	//">"
# define APPEND		4	//">>"
# define PIPE		5	//"|"
# define CMD		6	//"|"
# define ARG		7	//"|"

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
/Edoulazone/Cursus-42
//Environnement structure
typedef struct s_env
{
	char			*value;
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
	char	**envp;
	char	*delimiter;
	char	*exit_status;
	t_env	*env;
	t_token	*token;
	t_ast	*ast;
}	t_shell;

/*FONCTIONS*/

/*************************************
*				 MAIN                *
*************************************/
//shell_int.c
void	init_shell(t_shell *sh);

//env.c
int		make_env(t_shell *sh, char **envp);

/*************************************
*				UTILS                *
*************************************/
//utils.c
char	*ft_strdup(const char *str);
char	*ft_strndup(const char *str, int n);
char	*ft_ssearch(char *str, int c, int flag);

/*************************************
*			   EXECUTOR              *
*************************************/


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
//ast.c
t_ast	*make_ast(t_token *tokens);
t_ast	*make_ast_node(char	**value, int type);
t_ast	*ast_priority(t_token *tokens, t_ast *origin);
char	**get_command(t_token *token);

/*************************************
*			   CHECKER               *
*************************************/
int		ft_error(char *str, int n, char var);

/*************************************
*		      BUILT_INS              *
*************************************/
//EXEC echo
void	ft_echo(t_ast_command *cmd);
bool 	only_n(char *str);
bool	option_new_line(char **args, int *p);

//PWD
void	ft_pwd(t_shell *sh);

//ENV
t_list	*init_env_list(char **env);
void	ft_env(t_list *head);
void	free_env_list(t_list *head);

//PATH
char	*find_home(t_list *env);
char	*find_paths(t_list *env);

//CD
void	ft_cd(t_ast *cmd, t_list *env);

//UNSET
int		special_strcmp(char *env_str, char *check, char c);
void	ft_unset(t_ast_command *cmd, t_list **env);
void	remove_env_node(t_list **head, char *check, t_list **save);

//EXPORT
int		valid_arg(char *var);
t_list	*env_var_exists(char *var, t_list *env);
void	ft_export(t_ast_command *cmd, t_list **env);
void	append_node(char *var, t_list *env);
void	update_content(t_list *node, char *new_var);

//EXPORT UTILS
	int	exp_strcmp(char *s1, char *s2);

//UTILS
void	free_split(char **mem);

#endif