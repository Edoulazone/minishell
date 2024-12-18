/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:48:03 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/18 17:39:26 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_ctrl_c(int signum)
{
	(void)signum;
	g_exit_status = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	child_ctrl_c(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	g_exit_status = 130;
}

void	ctrl_slash(int signum)
{
	(void)signum;
	g_exit_status = 131;
	write(2, "Quit: 3\n", 8);
}

void	testingg(int signum)
{
	(void)signum;
	write(2, "ctr C was pressed\n", 18);
}

void	handle_signal(int process)
{
	if (!process)
	{
		signal(SIGINT, handle_ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (process == 1)
	{
		signal(SIGINT, child_ctrl_c);
		signal(SIGQUIT, ctrl_slash);
	}
	else if (process == 2)
	{
		g_exit_status = 0;
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (process == 3)
	{
		signal(SIGINT, testingg);
		signal(SIGQUIT, SIG_IGN);
	}
}
