/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 17:18:06 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/24 18:11:59 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

t_line	*dup_line(t_line *env)
{
	t_line	*dup;
	char	**tab_env;

	tab_env = line_to_tab(&env);
	dup = fill_line(tab_env);
	tabdel(tab_env);
	return (dup);
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
	if (*first)
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
}
