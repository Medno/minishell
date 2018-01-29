/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:58:40 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/29 15:35:38 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

int		get_cmd(t_line **env, unsigned char again)
{
	char	car;
	char	*cmd;
	int		i;
	char	**semicolon;

	i = 0;
	cmd = NULL;
	p_prompt();
	signal(SIGINT, (void (*)(int))prompt);
	while ((again = (read(0, &car, 1))) > 0 && car != '\n')
		ft_put_in_str(&cmd, car);
	if (again)
	{
		again = 254;
		semicolon = ft_strsplit(cmd, ';');
		while (semicolon && semicolon[i])
		{
			again = execute_cmd(env, semicolon[i]);
			i++;
		}
		ft_tabdel(semicolon);
	}
	again = (again == 0 && !cmd) ? p_exit(NULL) : again;
	ft_strdel(&cmd);
	return (again);
}

int		main(int ac, char **av, char **env)
{
	unsigned char	again;
	t_line			*nenv;

	(void)ac;
	g_fath = -1;
	entry_message(av, env);
	again = 254;
	nenv = fill_line(env);
	incr_shlvl(&nenv);
	while (again == 254)
		again = get_cmd(&nenv, again);
	del_line(&nenv);
	return (again);
}
