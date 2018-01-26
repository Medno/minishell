/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:58:40 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/26 11:39:28 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

t_line	*get_smtg(t_line *env, char *str)
{
	t_line	*path;

	path = env;
	while (path)
	{
		if (ft_strcmp(path->var, str) == 0)
			return (path);
		path = path->next;
	}
	return (NULL);
}

int	get_cmd(t_line **env, unsigned char again)
{
	char	car;
	char	*cmd;
	int		i;
	char	**semicolon;

	i = 0;
	again = 254;
	cmd = NULL;
	p_prompt();
	signal(SIGINT, (void (*)(int))prompt);
	while ((read(0, &car, 1)) > 0 && car != '\n')
		ft_put_in_str(&cmd, car);
	semicolon = ft_strsplit(cmd, ';');
	while (semicolon && semicolon[i])
	{
		again = execute_cmd(env, semicolon[i]);
		i++;
	}
	ft_tabdel(semicolon);
	ft_strdel(&cmd);
	if (car == '\0')
		again = p_exit(NULL);
	return (again);
}

int	main(int ac, char **av, char **env)
{
	unsigned char	again;
	t_line			*nenv;

	(void)ac;
	g_fath = -1;
	entry_message(av, env);
	again = 254;
	nenv = fill_line(env);
	incr_shlvl(nenv);
	while (again == 254)
		again = get_cmd(&nenv, again);
	del_line(&nenv);
	return (again);
}
