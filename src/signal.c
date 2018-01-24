/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 11:11:59 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/24 11:35:52 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

void	kill_child(int sig)
{
	sig = 0;
	(void)sig;
	if (g_fath > 0)
		kill(g_fath, SIGTERM);
	g_fath = -1;
	ft_putchar('\n');
	signal(SIGINT, (void (*)(int))kill_child);
}

void	ret_fath(pid_t fath)
{
	if (!WIFEXITED(fath))
	{
		ft_putstr("minishell: ");
		if (WIFSIGNALED(fath))
		{
			(WTERMSIG(fath) == SIGABRT) ? ft_putstr("abort      ") : 0;
			(WTERMSIG(fath) == SIGBUS) ? ft_putstr("bus error  ") : 0;
			(WTERMSIG(fath) == SIGSEGV) ?
				ft_putstr("segmentation fault  ") : 0;
		}
		ft_putendl(g_process);
	}
}
