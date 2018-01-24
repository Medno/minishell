/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 11:12:39 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/24 11:12:41 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

void	entry_message(char **av, char **env)
{
	pid_t	father;

	father = fork();
	if (father)
		wait(0);
	else
		execve("/usr/bin/clear", av, env);
	ft_putendl("Welcome to the pchadeni's minishell !");
}

void	p_prompt(void)
{
	char	*tmp;

	tmp = NULL;
	tmp = getcwd(tmp, 0);
	ft_putcolor(tmp, LIGHT_BLUE);
	ft_putstr(PROMPT);
	ft_strdel(&tmp);
}

void	prompt(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar('\n');
		p_prompt();
		signal(SIGINT, (void (*)(int))prompt);
	}
}
