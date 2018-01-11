/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:58:40 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/11 18:35:43 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

uint8_t	is_built(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "setenv") == 0)
		return (1);
	else if (ft_strcmp(str, "unsetenv") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	return (0);
}

void	exec_built(t_line **env, char **ncmd)
{
	(ft_strcmp(ncmd[0], "echo") == 0) ? ft_echo(ncmd) : 0;
	(ft_strcmp(ncmd[0], "cd") == 0) ? p_cd(env, ncmd) : 0;
	(ft_strcmp(ncmd[0], "setenv") == 0) ? s_env(env, ncmd) : 0;
	(ft_strcmp(ncmd[0], "unsetenv") == 0) ? uns_env(env, ncmd) : 0;
	(ft_strcmp(ncmd[0], "env") == 0) ? p_line(*env) : 0;
}

t_line	*get_path(t_line *env)
{
	t_line	*path;

	path = env;
	while (path)
	{
		if (ft_strcmp(path->var, "PATH") == 0)
			return (path);
		path = path->next;
	}
	return (NULL);
}

void	check_bin(char **tenv, char **ncmd, char *path)
{
	char	*gap;
	int		i;

	i = 1;
	while ((gap = ft_strgap(path, ':', i)))
	{
		gap = ft_strjoinfree(gap, "/");
		execve(ft_strjoin(gap, ncmd[0]), ncmd, tenv);
		ft_strdel(&gap);
		i++;
	}
}

void	exec_bin(t_line **env, char **ncmd)
{
	char	**tenv;
	t_line	*path;
	pid_t	fath;

	path = get_path(*env);
	fath = fork();
	tenv = line_to_tab(env);
	if (fath > 0)
		wait(NULL);
	if (fath == 0)
	{
		(path != NULL) ? check_bin(tenv, ncmd, path->value) : 0;
		execve(ncmd[0], ncmd, tenv);
		error("zsh", ncmd[0], 5);
		(tenv != NULL) ? ft_tabdel(tenv) : 0;
		(ncmd != NULL) ? ft_tabdel(ncmd) : 0;
		exit(0);
	}
	(tenv != NULL) ? ft_tabdel(tenv) : 0;
}

uint8_t	execute_cmd(t_line **env, char *cmd)
{
	char	**ncmd;
	uint8_t	res;
	uint8_t	built;

	if (!*cmd)
		return (1);
	res = 1;
	if ((ncmd = ft_splitwsp(cmd)) == NULL)
		return (1);
	if (ncmd && ft_strcmp(ncmd[0], "exit") != 0)
	{
		built = is_built(ncmd[0]);
		if (built > 0)
			exec_built(env, ncmd);
		else
			exec_bin(env, ncmd);
	}
	else
		res = 0;
	ft_tabdel(ncmd);
	return (res);
}

int	main(int ac, char **av, char **env)
{
	char	*cmd;
	uint8_t	again;
	t_line	*nenv;

	(void)ac;
	(void)av;
	again = 1;
	nenv = fill_line(env);
	while (again)
	{
		ft_putstr(PROMPT);
		get_next_line(0, &cmd);
		again = execute_cmd(&nenv, cmd);
		ft_strdel(&cmd);
	}
	if (nenv)
		del_line(&nenv);
	//	while(1) ft_putchar('\0');
	return (0);
}
