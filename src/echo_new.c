/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 17:51:13 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/15 17:28:40 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

void	ft_echo(t_line *env, char **cmd)
{
	int		i;
	t_line	*smtg;

	i = 1;
	while (cmd[i])
	{
		if (cmd[i][0] == '$')
		{
			smtg = get_smtg(env, &cmd[i][1]);
			(smtg != NULL) ? ft_putstr(smtg->value) : 0;
		}
		else
			ft_putstr(cmd[i]);
		(cmd[i + 1]) ? ft_putchar(' ') : 0;
		i++;
	}
	ft_putchar('\n');
}
