/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:54:50 by eschmitz          #+#    #+#             */
/*   Updated: 2024/11/12 15:17:49 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Exécute les étapes de fonctionnement de minishell en vérifiant le bon fonctionnement général après chaque étape
void	minilaunch(t_shell *sh)
{
	int	verif;

	verif = 0;
	verif = lex(sh);
	if (verif == 0)
	{
		verif = parsing(sh);
		if (verif == 0)
		{
			execute_ast(sh->ast, &sh->env, sh);
			// free_ast(sh->ast);
		}
	}
}

//Loop dans le programme
int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	if (argc != 1)
		return (ft_error("No argument is allowed\n", 0, 0));
	(void)argv;
	sh.env = NULL;
	// checker();
	sh.env = init_env_list(envp);
	if (shell_init(&sh) == 0)
	{
		sh.loop = 0;
		while (sh.loop == 0)
		{
			sh.command = readline("minishell efficace> ");
			if (!sh.command)
				return (ft_error("Error with shell launch", 0, 0));
			else
				add_history(sh.command);
			minilaunch(&sh);
			// ft_free(&sh);
		}
	}
	// free_env(&sh);
	// sh.env = NULL;
	return (0);
}
