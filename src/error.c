/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 17:04:03 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/30 15:11:39 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

int	error(char *built, char *cmd, int code)
{
	ft_putstr("bash: ");
	if (code != 5)
		ft_putstr(built);
	(code == 1) ? ft_putstr(": string not in pwd: ") : 0;
	(code == 2) ? ft_putstr(": permission denied: ") : 0;
	(code == 3) ? ft_putstr(": no such file or directory: ") : 0;
	(code == 4) ? ft_putstr(": not a directory: ") : 0;
	(code == 5) ? ft_putstr("command not found: ") : 0;
	(code == 6) ? ft_putstr(": not a directory: ") : 0;
	(code == 7 || code == 9) ? ft_putstr(": ") : 0;
	if (code != 8)
		(code == 7 || code == 9) ? ft_putstr(cmd) : ft_putendl(cmd);
	(code == 7) ? ft_putendl(" not set") : 0;
	(code == 8) ? ft_putendl(": too many arguments") : 0;
	(code == 9) ? ft_putendl(": numeric argument required") : 0;
	return (0);
}

int	usage(char *name, char *opt, char err, int e)
{
	ft_putstr(name);
	(e == 1) ? ft_putstr(": illegal option -- ") : 0;
	(e == 2) ? ft_putstr(": option requires an argument -- ") : 0;
	ft_putchar(err);
	ft_putstr("\nusage: ");
	ft_putstr(name);
	ft_putstr(" [-");
	ft_putstr(opt);
	ft_putendl("]");
	return (0);
}
