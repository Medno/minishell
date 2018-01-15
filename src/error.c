/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 17:04:03 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/15 15:06:50 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

int	error(char *built, char *cmd, int code)
{
	ft_putstr(built);
	(code == 1) ? ft_putstr(": string not in pwd: ") : 0;
	(code == 2) ? ft_putstr(": permission denied: ") : 0;
	(code == 3) ? ft_putstr(": no such file or directory: ") : 0;
	(code == 4) ? ft_putstr(": not a directory: ") : 0;
	(code == 5) ? ft_putstr(": command not found: ") : 0;
	(code == 6) ? ft_putstr(": not a directory: ") : 0;
	ft_putendl(cmd);
	return (0);
}
