/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:54:50 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/10 19:02:20 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t radio = 1;

void	ft_printlst(t_token *e)
{
	t_token	*tokens;
	tokens = e;
	while(tokens)
	{
		dprintf(2,"token value: %s \n", (char *)tokens->content);
		dprintf(2, "token type: %d \n", tokens->t_type);
		dprintf(2, "---------------------------------------\n");
		tokens = tokens->next;
	}
}

//Exécute les étapes de fonctionnement de minishell en vérifiant le bon fonctionnement général après chaque étape
void	minilaunch(t_shell *sh)
{
	int		verif;
	int		heredocs;
	t_ast	*ast;

	verif = 0;
	verif = lex(sh->command, &sh->token, sh);
	verif = expander(sh, &sh->expander);
	ft_printlst(sh->expander);
	if (verif == 0)
	{
		heredocs = countheredocs(sh->expander);
		ast = parser(&sh->expander, sh->env, &heredocs, sh);
		// ast_printer(ast, 0);
		if (verif == 0)
		{
			pre_ast(ast, &sh->env, sh);
			free_ast(ast);
		}
	}
}

//Loop dans le programme
int	main(int argc, char **argv, char **envp)
{
	t_shell	*sh;

	if (argc != 1)
		return (ft_error("No argument is allowed\n", 0, 0));
	(void)argv;
	sh = safe_malloc(sizeof(t_shell));
	sh->env = NULL;
	sh->env = init_env_list(envp);
	if (shell_init(sh) == 0)
	{
		sh->loop = 0;
		while (sh->loop == 0 && radio == 1) //radio cest le global var pr signaux
		{
			sh->command = readline("minishell efficace> ");
			if (sh->command[0] == '\0') //ca cest un peu dla merde
				continue;
			if (!sh->command)// || sh->command[0] == '\0')
				return (ft_error("Error with shell launch\n", 0, 0));
			else
				add_history(sh->command);
			minilaunch(sh);
			ft_free(sh);
		}
	}
	free_env_list(sh->env);
	sh->env = NULL;
	return (0);
}

// //  SERVAIT A TESTER EXEC HARDTEST
// int main(int ac, char **av, char **env)
// {
// 	t_shell	*sh;

// 	if (ac != 1)
// 		return (ft_error("No argument is allowed\n", 0, 0));
// 	(void)av;
// 	sh = malloc(sizeof(t_shell));
// 	if (!sh)
// 		return (EXIT_FAILURE);
// 	sh->env = NULL;
// 	sh->env = init_env_list(env);
// 	sh->ast = hard_ast5(sh);
// 	execute_ast(sh->ast, &sh->env, sh);
// 	return (free_env_list(sh->env), 0);
// }
