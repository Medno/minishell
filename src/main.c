/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:58:40 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/09 18:04:19 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

uint8_t	is_built(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "setenv") == 0)
		return (1);
	else if (ft_strcmp(str, "unsetenv") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	return (0);
}

uint8_t	execute_cmd(char **env, char *cmd)
{
	char	**ncmd;
	uint8_t	res;
	uint8_t	built;

	if (!*cmd)
		return (1);
	res = 1;
	ncmd = ft_splitwsp(cmd);
	if (ft_strcmp(ncmd[0], "exit") != 0)
	{
		built = is_built(ncmd[0]);
		if (built > 0)
		{
			()
		}
		else
		{
			(ft_strcmp(ncmd[0], "env") == 0) ? ft_puttab(env) : 0;
		}
	}
	else
		res = 0;
	ft_tabdel(ncmd);
	return (res);
}

int	main(int ac, char **av, char **env)
{
	char	*cmd;
	uint8_t	again;
	char	**nenv;

	(void)ac;
	(void)av;
	again = 1;
	nenv = ft_tabdup(env);
	while (again)
	{
		ft_putstr(PROMPT);
		get_next_line(0, &cmd);
		again = execute_cmd(nenv, cmd);
		ft_strdel(&cmd);
	}
	if (*nenv)
		ft_tabdel(nenv);
	return (0);
}
