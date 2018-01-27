/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 09:00:26 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/27 15:33:27 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

t_line	*fill_line(char **env)
{
	t_line	*first;

	first = NULL;
	s_env(&first, env);
		//		add = init_line(first, ft_strfchr(env[i], '='),
		//				ft_strrchr(env[i], '=') + 1);
	return (first);
}

void	s_env(t_line **env, char **cmd)
{
	t_line	*tmp;
	int		i;

	i = 0;
	while (cmd && cmd[i])
	{
		tmp = init_line(env, cmd[i]);
		i++;
	}
	//add = init_line(env, cmd[1], copy);
	//	ft_strdel(&copy);
}

int		uns_env(t_line **env, char **cmd)
{
	t_line	*tmp;
	t_line	*prev;
	int		i;

	i = 0;
	while (cmd[i])
	{
		tmp = *env;
		if (tmp && ft_strcmp(tmp->var, cmd[i]) == 0)
			clean_line(env, tmp);
		prev = tmp;
		tmp = tmp->next;
		while (tmp)
		{
			if (ft_strcmp(tmp->var, cmd[i]) == 0)
				clean_line(&(prev->next), tmp);
			else
				prev = tmp;
			if (tmp)
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}
