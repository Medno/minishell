/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 11:11:59 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/27 15:30:27 by pchadeni         ###   ########.fr       */
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
		if (WIFSIGNALED(fath))
		{
			(WTERMSIG(fath) != SIGINT) ? ft_putstr("minishell: ") : 0;
			(WTERMSIG(fath) == SIGABRT) ? ft_putstr("abort      ") : 0;
			(WTERMSIG(fath) == SIGBUS) ? ft_putstr("bus error  ") : 0;
			(WTERMSIG(fath) == SIGSEGV) ?
				ft_putstr("segmentation fault  ") : 0;
			(WTERMSIG(fath) != SIGINT) ? ft_putendl(g_process) : 0;
		}
	}
}

void	incr_shlvl(t_line **env)
{
	t_line	*tmp;
	int		i;

	if ((tmp = get_smtg(*env, "SHLVL")))
	{
		i = ft_atoi(tmp->value) + 1;
		ft_strdel(&tmp->value);
		tmp->value = ft_itoa(i);
	}
	else
		tmp = init_line(env, "SHLVL=1");
}
