/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 09:00:26 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/11 16:46:39 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

t_line	*fill_line(char **env)
{
	t_line	*first;
	t_line	*add;
	int		i;

	i = 0;
	first = NULL;
	while (env[i] != NULL)
	{
		add = init_line();
		add->var = ft_strfchr(env[i], '=');
		add->value = ft_strdup(ft_strrchr(env[i], '=') + 1);
		line_pushback(&first, add);
		i++;
	}
	return (first);
}

void	s_env(t_line **env, char **cmd)
{
	t_line	*add;
	t_line	*tmp;

	tmp = *env;
	if (!cmd[1] || !cmd[2])
		return;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, cmd[1]) == 0)
		{
			ft_strdel(&(tmp->value));
			tmp->value = ft_strdup(cmd[2]);
			return ;
		}
		tmp = tmp->next;
	}
	add = init_line();
	add->var = ft_strdup(cmd[1]);
	add->value = ft_strdup(cmd[2]);
	line_pushback(env, add);
}

int		uns_env(t_line **env, char **cmd)
{
	t_line	*tmp;
	t_line	*prev;
	int		i;

	i = 1;
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
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}
