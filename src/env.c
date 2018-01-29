/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 09:00:26 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/29 15:01:24 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

t_line	*fill_line(char **env)
{
	t_line	*first;

	first = NULL;
	s_env(&first, env);
	return (first);
}

void	s_env(t_line **env, char **cmd)
{
	t_line	*tmp;
	int		i;

	i = 0;
	while (cmd && cmd[i])
	{
		if (ft_strchr(cmd[i], '='))
			tmp = init_line(env, cmd[i]);
		i++;
	}
}

int		del_one_env(t_line **env, char *cmd)
{
	t_line	*tmp;
	t_line	*prev;

	tmp = *env;
	if (tmp && ft_strcmp(tmp->var, cmd) == 0)
		clean_line(env, tmp);
	prev = tmp;
	tmp = tmp->next;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, cmd) == 0)
			clean_line(&(prev->next), tmp);
		else
			prev = tmp;
		if (tmp)
			tmp = tmp->next;
	}
	return (0);
}

int		uns_env(t_line **env, char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		del_one_env(env, cmd[i]);
		i++;
	}
	return (0);
}
