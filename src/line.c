/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 10:58:26 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/09 13:32:58 by pchadeni         ###   ########.fr       */
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
