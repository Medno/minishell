/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:58:40 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/22 18:19:30 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

pid_t	g_fath = -1;

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
	(ft_strcmp(ncmd[0], "echo") == 0) ? ft_echo(*env, ncmd) : 0;
	(ft_strcmp(ncmd[0], "cd") == 0) ? p_cd(env, ncmd) : 0;
	(ft_strcmp(ncmd[0], "setenv") == 0) ? s_env(env, ncmd) : 0;
	(ft_strcmp(ncmd[0], "unsetenv") == 0) ? uns_env(env, ncmd) : 0;
	(ft_strcmp(ncmd[0], "env") == 0) ? n_env(*env, ncmd) : 0;
}

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

void	kill_child(int sig)
{
	sig = 0;
	(void)sig;
	if (g_fath > 0)
		kill(g_fath, SIGTERM);
	g_fath = -1;
	ft_putchar('\n');
	signal(SIGINT, (void (*)(int))kill_child);
}

void	exec_bin(t_line **env, char **ncmd)
{
	char	**tenv;
	t_line	*path;

	path = get_smtg(*env, "PATH");
	g_fath = fork();
	tenv = line_to_tab(env);
	signal(SIGINT, (void (*)(int))kill_child);
	if (g_fath == 0)
	{
		(path != NULL) ? check_bin(tenv, ncmd, path->value) : 0;
		execve(ncmd[0], ncmd, tenv);
		error("zsh", ncmd[0], 5);
		(tenv != NULL) ? ft_tabdel(tenv) : 0;
		(ncmd != NULL) ? ft_tabdel(ncmd) : 0;
		exit(0);
	}
	if (g_fath > 0)
		wait(&g_fath);
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
	while (ft_iswsp(*cmd))
		cmd++;
	if (!*cmd || ((ncmd = ft_splitwsp(cmd)) == NULL))
		return (1);
	if (ncmd && ft_strcmp(ncmd[0], "exit") != 0)
	{
		built = is_built(ncmd[0]);
		(built > 0) ? exec_built(env, ncmd) : exec_bin(env, ncmd);
	}
	else
		res = 0;
	ft_tabdel(ncmd);
	return (res);
}

void	p_prompt(void)
{
	char	*tmp;

	tmp = NULL;
	tmp = getcwd(tmp, 0);
	ft_putcolor(tmp, LIGHT_BLUE);
	ft_putstr(PROMPT);
	ft_strdel(&tmp);
}

void	prompt(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar('\n');
		p_prompt();
		signal(SIGINT, (void (*)(int))prompt);
	}
}

void	putinstr(char **str, char c)
{
	char	*tmp;

	tmp = NULL;
	if (!*str)
	{
		*str = ft_strnew(1);
		**str = c;
	}
	else
	{
		tmp = ft_strnew(1);
		tmp[0] = c;
		*str = ft_strjoinfree(*str, tmp);
	}
	ft_strdel(&tmp);
}

int	exec(t_line **env, uint8_t again)
{
	char	car;
	char	*cmd;
	int		i;
	char	**semicolon;

	i = 0;
	again = 1;
	cmd = NULL;
	p_prompt();
	signal(SIGINT, (void (*)(int))prompt);
	while ((read(0, &car, 1)) > 0 && car != '\n')
		putinstr(&cmd, car);
	semicolon = ft_strsplit(cmd, ';');
	while (semicolon && semicolon[i])
	{
		again = execute_cmd(env, semicolon[i]);
		i++;
	}
	ft_tabdel(semicolon);
	ft_strdel(&cmd);
	return (again);
}

int	main(int ac, char **av, char **env)
{
	uint8_t	again;
	t_line	*nenv;

	(void)ac;
	(void)av;
	again = 1;
	nenv = fill_line(env);
	while (again)
		again = exec(&nenv, again);
	ft_putcolor("exit\n", LIGHT_RED);
	del_line(&nenv);
	return (0);
}
