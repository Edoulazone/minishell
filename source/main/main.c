/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:54:50 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/18 17:40:37 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minilaunch(t_shell *sh)
{
	int		verif;
	int		heredocs;
	t_ast	*ast;

	verif = 0;
	verif = lex(sh->command, &sh->token);
	if (verif == 0)
		verif = expander(sh, &sh->expander);
	if (verif == 0)
	{
		heredocs = countheredocs(sh->expander);
		ast = parser(&sh->expander, sh->env, &heredocs, sh);
		if (verif == 0)
		{
			pre_ast(ast, &sh->env, sh);
			free_ast(ast);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*sh;

	if (argc != 1 || argv[1])
		return (ft_error("No argument is allowed\n", 0, 0));
	sh = safe_malloc(sizeof(t_shell));
	sh->env = NULL;
	sh->env = init_env_list(envp, 0);
	if (shell_init(sh) == 0)
	{
		while (sh->loop == 0)
		{
			handle_signal(0);
			sh->command = readline("minishell> ");
			if (!sh->command)
				return (ft_error("exit\n", 0, 0));
			if (sh->command[0] == '\0')
				continue ;
			else
				add_history(sh->command);
			minilaunch(sh);
			ft_free(sh);
		}
	}
	free_env_list(sh->env);
	return (0);
}
