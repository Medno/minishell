/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 09:00:26 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/24 18:11:49 by pchadeni         ###   ########.fr       */
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
		add = init_line(*env, ft_strfchr(env[i], '='),
				ft_strdup(ft_strrchr(env[i], '=') + 1));
		i++;
	}
	return (first);
}

void	s_env(t_line **env, char **cmd)
{
	t_line	*add;
	t_line	*tmp;
	char	*copy;

	tmp = *env;
	if (!cmd[1] || !cmd[2])
		return ;
	copy = (ft_strchr(cmd[2], '"')) ?
		ft_strsub(cmd[2], 1, ft_strlen(cmd[2]) - 2) : ft_strdup(cmd[2]);
	while (tmp)
	{
		if (ft_strcmp(tmp->var, cmd[1]) == 0)
		{
			ft_strdel(&(tmp->value));
			tmp->value = ft_strdup(copy);
			ft_strdel(&copy);
			return ;
		}
		tmp = tmp->next;
	}
	add = init_line();
	add->var = ft_strdup(cmd[1]);
	add->value = ft_strdup(copy);
	ft_strdel(&copy);
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
