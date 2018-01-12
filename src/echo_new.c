/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 17:51:13 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/12 11:12:28 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

int		in_quote(char *str, char c)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	if (str[i] == c)
		quote = 1;
	i++;
	while (str[i])
	{
		if (str[i] == c && quote == 1)
			return (2);
		else if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	p_echo(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (in_quote(&str[i], '"') == 1)
		{
			ft_putsgap(&str[i], '"', 1);
			while (str[i + 1] != '"')
				i++;
		}
		
	}
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
		(cmd[i + 1]) ? ft_putchar(' ') : 0;
		i++;
	}
	ft_putchar('\n')
}
