/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 17:51:13 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/11 18:34:34 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"


void	p_echo(char *str)
{
	int	i;

	i = 0;
	ft_putstr(str);
}

void	ft_echo(char **cmd)
{
	int	i;
		i = 1;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '"'))
			p_echo(cmd[i]);
		else
			ft_putstr(cmd[i]);
		(cmd[i + 1]) ? ft_putchar(' ') : ft_putchar('\n');
		i++;
	}
}
