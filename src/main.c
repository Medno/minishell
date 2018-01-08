/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:58:40 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/08 17:52:18 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

uint8_t	execute_cmd(char *line)
{
	ft_putendl(line);
	return (1);
}

int	main(void)
{
	pid_t	father;
	char	*cmd;
	uint8_t	again;

	father = fork();
	again = 0;
	if (father > 0)
		wait(0);
	while (father == 0)
	{
		ft_putstr("$> ");
		get_next_line(0, &cmd);
		(ft_strcmp(cmd, "exit") == 0) ? exit(EXIT_SUCCESS) : 0;
		again = execute_cmd(cmd);
	}
	return (0);
}
