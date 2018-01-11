/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 10:58:26 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/11 09:02:54 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

t_line	*init_line(void)
{
	t_line	*tmp;

	if (!(tmp = (t_line *)malloc(sizeof(t_line))))
		return (NULL);
	tmp->var = NULL;
	tmp->value = NULL;
	tmp->next = NULL;
	return (tmp);
}

void	line_pushback(t_line **first, t_line *add)
{
	t_line	*tmp;

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
	if (!tmp)
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

int		clean_line(t_line **prev, t_line *tmp)
{
	(*prev) = tmp->next;
	ft_strdel(&(tmp->var));
	ft_strdel(&(tmp->value));
	free(tmp);
	tmp = NULL;
	return (1);
}

void	del_line(t_line **first)
{
	if ((*first)->next == NULL)
	{
		ft_strdel(&(*first)->var);
		ft_strdel(&(*first)->value);
		free(*first);
		*first = NULL;
	}
	else
	{
		del_line(&(*first)->next);
		ft_strdel(&(*first)->var);
		ft_strdel(&(*first)->value);
		free(*first);
		*first = NULL;
	}
}
