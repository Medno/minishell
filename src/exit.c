/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 11:12:51 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/24 11:12:52 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

unsigned char	p_exit(char **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i] != NULL)
		i++;
	if (i == 3)
	{
		error("exit", cmd[i], 8);
		return ((unsigned char)254);
	}
	ft_putcolor("exit 👋\n", LIGHT_RED);
	if (i == 2)
	{
		i = 0;
		while (cmd[1][i])
		{
			if (!ft_isdigit(cmd[1][i]))
				return (error("exit", cmd[1], 9));
			i++;
		}
		return ((unsigned char)ft_atoi(cmd[1]));
	}
	return (0);
}
