/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:54:50 by eschmitz          #+#    #+#             */
/*   Updated: 2024/10/25 14:44:56 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Exécute les étapes de fonctionnement de minishell en vérifiant le bon fonctionnement général après chaque étape
void	minilaunch(t_shell *sh)
{
	int	verif;

	verif = 0;
	verif = lex(sh, sh->command);
	if (verif == 0)
	{
		verif = parsing(sh);
		if (verif == 0)
		{
			verif = execute_heredoc(sh, sh->ast);
			if (verif == 0)
				execute(sh, sh->ast);
			// free_ast(sh->ast);
		}
	}
}

//Loop dans le programme
int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	(void)argc;
	(void)argv;
	sh.env = NULL;
	sh.str = NULL;
	// checker();
	make_env(&sh, envp);
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
}
