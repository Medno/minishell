/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 17:51:13 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/17 15:56:48 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

void	ft_echo(t_line *env, char **cmd)
{
	int		i;
	char	*p;
	t_line	*smtg;

	i = 1;
	p = ft_getopt(cmd, &i);
	(ft_checkopt(p, "n", 1)) ? i-- :0;
	while (cmd[i])
	{
		smtg = get_smtg(env, &cmd[i][1]);
		if (cmd[i][0] == '$')
			(smtg != NULL) ? ft_putstr(smtg->value) : 0;
		else
			ft_putstr(cmd[i]);
		(cmd[i + 1]) ? ft_putchar(' ') : 0;
		i++;
	}
	if (p && p[0] == 'n')
	{
		ft_putstr(BG_GRAY);
		ft_putcolor("%", BLACK);
	}
	ft_putchar('\n');
}
