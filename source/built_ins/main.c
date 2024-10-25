/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:19:30 by gnyssens          #+#    #+#             */
/*   Updated: 2024/10/15 17:09:00 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_command *make_cmd_node(void)
{
	t_ast_command *cmd;

	cmd = malloc(sizeof(t_ast_command));
	return (cmd);
}

int	main(int ac, char **av, char **env)
{
	char			*input;
	t_ast_command	*cmd;
	t_shell			sh[1];
	t_list			*head;

	(void)ac;
	(void)av;
	head = init_env_list(env);
	while (1)
	{
		input = readline("built-ins for minishell: ");
		if (!input)
			break;
		else if (ft_strcmp(input, "stop") == 0)
		{
			free(input);
			free_env_list(head);
			exit(EXIT_SUCCESS);
		}
		else
			add_history(input);
		cmd = make_cmd_node();
		cmd->args = ft_split(input, ' ');
		if (ft_strncmp(input, "echo", 4) == 0)
			ft_echo(cmd);
		if (ft_strcmp(input, "pwd") == 0)
			ft_pwd(sh);
		if (ft_strcmp(input, "env") == 0)
			ft_env(head);
		if (ft_strncmp(input, "cd", 2) == 0)
			ft_cd(cmd, head);
		if (ft_strncmp(input, "unset", 5) == 0)
			ft_unset(cmd, &head);
		if (ft_strncmp(input, "export", 6) == 0)
			ft_export(cmd, &head);
		free(cmd->args);
		free(input);
	}
	free_env_list(head);

	return (0);
}
