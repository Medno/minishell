/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 10:58:26 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/29 17:15:20 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

t_line	*init_line(t_line **env, char *cmd)
{
	t_line	*tmp;
	char	*variable;
	char	*value;

	if (!cmd)
		return (NULL);
	variable = (*cmd) ? ft_strfchr(cmd, '=') : NULL;
	value = (*cmd) ? ft_strdup(ft_strrchr(cmd, '=') + 1) : NULL;
	if (variable && (tmp = get_smtg(*env, variable)))
	{
		ft_strdel(&variable);
		ft_strdel(&tmp->value);
		tmp->value = (value) ? value : NULL;
		return (tmp);
	}
	if (!(tmp = (t_line *)malloc(sizeof(t_line))))
		return (NULL);
	tmp->var = (variable) ? variable : NULL;
	tmp->value = (value) ? value : NULL;
	tmp->next = NULL;
	line_pushback(env, tmp);
	return (tmp);
}

void	line_pushback(t_line **first, t_line *add)
{
	t_line	*tmp;

	if (add)
	{
		if (!(*first))
			(*first) = add;
		else
		{
			tmp = *first;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = add;
		}
	}
}

size_t	size_line(t_line *first)
{
	t_line	*tmp;
	size_t	res;

	res = 0;
	tmp = first;
	while (tmp != NULL)
	{
		res++;
		tmp = tmp->next;
	}
	return (res);
}

char	**line_to_tab(t_line **first)
{
	char	**res;
	t_line	*tmp;
	size_t	size;
	size_t	i;

	tmp = *first;
	if (!tmp || !*first)
		return (NULL);
	size = size_line(tmp);
	if (!(res = (char **)malloc(sizeof(char *) * size_line(tmp) + 1)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		res[i] = ft_strdup(tmp->var);
		res[i] = ft_strjoinfree(res[i], "=");
		res[i] = ft_strjoinfree(res[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	res[i] = NULL;
	return (res);
}

void	p_line(t_line *line)
{
	t_line	*tmp;

	tmp = line;
	while (tmp)
	{
		ft_putstr(tmp->var);
		ft_putchar('=');
		ft_putendl(tmp->value);
		tmp = tmp->next;
	}
}
