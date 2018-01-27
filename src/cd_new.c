/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 18:31:11 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/27 11:43:45 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

t_line	*get_pwd(t_line **env, char *str)
{
	t_line *pwd;

	pwd = NULL;
	if (*env)
	{
		pwd = *env;
		while (pwd && pwd->next)
		{
			if (ft_strequ(pwd->var, str))
				return (pwd);
			pwd = pwd->next;
		}
	}
	pwd = init_line(env, "");
	pwd->var = ft_strdup(str);
	pwd->value = getcwd(pwd->value, 0);
	return (pwd);
}

char	*copy_home(t_line *env, char *path)
{
	t_line	*home;
	char	*tmp;

	home = get_smtg(env, "HOME");
	if (home)
	{
		tmp = ft_strdup(home->value);
		tmp = ft_strjoinfree(tmp, "/");
		tmp = (path && path[0] == '~' && path[1]) ?
			ft_strjoinfree(tmp, &path[2]) : tmp;
		ft_strdel(&path);
		path = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	else
		ft_strdel(&path);
	return (path);
}

uint8_t	go_oldpwd(t_line *env)
{
	t_line	*pwd;
	t_line	*oldpwd;
	char	*tmp;

	if ((oldpwd = get_smtg(env, "OLDPWD")))
	{
		pwd = get_pwd(&env, "PWD");
		tmp = pwd->value;
		pwd->value = oldpwd->value;
		oldpwd->value = tmp;
		chdir(pwd->value);
		return (0);
	}
	else
	{
		error("cd", "OLDPWD", 7);
		return (7);
	}
}

uint8_t	slash_del(char **tab, int i)
{
	if ((tab[i + 1] && tab[i] && ft_strequ(tab[i + 1], "..") &&
				!ft_strequ(tab[i], "..")) || ft_strequ(tab[i], ".")
			|| ((!tab[i + 1] || (tab[i + 1] && ft_strequ(tab[i], "..")))
				&& ft_strequ(tab[i], "..")))
		return (1);
	return (0);
}

uint8_t	check_path(char *str, uint8_t i)
{
	t_stat	sb;

	if (lstat(str, &sb) == 0)
	{
		if (i == 1)
			return (1);
		if (ft_isdir(sb) || ft_islink(sb))
		{
			if (access(str, X_OK) == 0)
				return (0);
			return (2);
		}
		return (6);
	}
	return (3);
}

char	*concat_cdpath(char *cmd, char *path)
{
	char	*gap;
	int		i;

	i = 1;
	while ((gap = ft_strgap(path, ':', i)))
	{
		if (ft_lastchar(gap) != '/')
		gap = ft_strjoinfree(gap, "/");
		gap = ft_strjoinfree(gap, cmd);
		if (!check_path(gap, 0))
			return (gap);
		ft_strdel(&gap);
		i++;
	}
	return (NULL);
}

char	**clean_slash(char **slash, int j)
{
	char	**tmp;
	int		i;
	int		k;

	if (!(tmp = (char **)malloc(sizeof(char *) * j + 1)))
		return (NULL);
	i = 0;
	k = 0;
	while (slash[k])
	{
		if (!slash_del(slash, k))
		{
			tmp[i] = ft_strdup(slash[k]);
			i++;
		}
		k++;
	}
	tmp[i] = NULL;
	return (tmp);
}

uint8_t	checkpath(t_list *list, char *tmp)
{
	char	*str;
	t_stat	sb;

	if (!list)
		return (4);
	str = ft_strjoin(tmp, list->content);
	if (lstat(str, &sb) == 0)
	{
		ft_strdel(&str);
		if (!ft_isexe(sb))
		{
			if (list->next && ft_strequ(list->next->content, "..") &&
					!ft_strequ(list->content, ".."))
				return (2);
			return (error("cd", tmp, 2));
		}
		if (list->next && ft_strequ(list->next->content, "..") &&
				!ft_strequ(list->content, ".."))
			return (2);
		return (1);
	}
	ft_strdel(&str);
	return (3);
}

void	clean_path(char **tmp)
{
	char	**epur;
	char	**slash;
	int		i;
	int		j;

	i = 0;
	j = 0;
	slash = ft_strsplit(*tmp, '/');
	while (slash && slash[i])
	{
		j = (!slash_del(slash, i)) ? j + 1 : j;
		i++;
	}
	ft_strdel(tmp);
	epur = clean_slash(slash, j);
	*tmp = ft_strdup("/");
	i = 0;
	while (epur && epur[i])
	{
		*tmp = ft_strjoinfree(*tmp, epur[i]);
		*tmp = (epur[i + 1]) ? ft_strjoinfree(*tmp, "/") : *tmp;
		i++;
	}
	ft_tabdel(slash);
	ft_tabdel(epur);
}

int		step_8(char *tmp, t_line *pwd, t_line *oldpwd)
{
	int	check;

	clean_path(&tmp);
	check = check_path(tmp, 0);
	if (check == 0)
	{
		ft_strdel(&(oldpwd->value));
		oldpwd->value = ft_strdup(pwd->value);
		ft_strdel(&(pwd->value));
		pwd->value = ft_strdup(tmp);
		chdir(tmp);
	}
	ft_strdel(&tmp);
	return (check);
}
/*
void	del_dot(t_list **first, t_list **list, t_list **prev, uint8_t dot)
{
	dot = 0;
	if (*list == *first)
		*first = (*list)->next->next;
	else if (dot == 1)
	{
		(*prev)->next = ((*list)->next) ? (*list)->next->next : NULL;
		ft_lstdelone(&(*list)->next, ft_lstclean);
	}
	else
		(*prev)->next = ((*list)) ? (*list)->next : NULL;
	ft_lstdelone(list, ft_lstclean);
}
*/
int		compress_path(t_list **first, t_list **list, t_list **prev, char **tmp)
{
	int	check;

	check = 0;
	if (*list && (check = checkpath(*list, *tmp)) == 2)
	{
		if (*list == *first)
			*first = (*list)->next->next;
		else
			(*prev)->next = ((*list)->next) ? (*list)->next->next : NULL;
		ft_lstdelone(&(*list)->next, ft_lstclean);
		ft_lstdelone(list, ft_lstclean);
		ft_strdel(tmp);
		*tmp = ft_strdup("/");
		*list = *first;
		*prev = *list;
	}
	else if (*list && check == 1)
	{
		*tmp = ft_strjoinfree(*tmp, (char *)(*list)->content);
		*tmp = ft_strjoinfree(*tmp, "/");
	}
	*prev = *list;
	*list = ((*list) && check != 2) ? (*list)->next : *list;
	return (check);
}
/*
void	delete_dot(t_list **first)
{
	t_list	*lst;
	t_list	*prev;

	lst = *first;
	prev = lst;
	while (lst)
	{
		if (lst == *first && ft_strequ(lst->content, "."))
		{
			*first = lst->next;
			ft_lstdelone(&lst, ft_lstclean);
			lst = *first;
			prev = lst;
		}
		else if (ft_strequ(lst->content, "."))
		{
			prev->next = (lst) ? lst->next : NULL;
			ft_lstdelone(&lst, ft_lstclean);
			lst = prev;
		}
		else
		{
			prev = lst;
			lst = lst->next;
		}
	}
}
*/
int	final_curpath(char *str, t_line *pwd, t_line *oldpwd)
{
	t_list	*list;
	t_list	*first;
	t_list	*prev;
	char	*tmp;
	uint8_t	check;

	first = ft_lstsplit(str, '/');
	check = 1;
	list = first;
	prev = list;
	tmp = ft_strdup("/");
	while (list && check != 3)
		check = compress_path(&first, &list, &prev, &tmp);
	(first) ? ft_lstdel(&first, ft_lstclean) : 0;
	if (check == 0 || check == 3)
		ft_strdel(&tmp);
	else
		check = step_8(tmp, pwd, oldpwd);
	return (check);
}

int		opt_l(char *curpath, t_line *pwd, t_line *oldpwd)
{
	char	*tmp;
	int		res;

ft_putendl("old_l_1");
	if (curpath[0] != '/')
	{
ft_putendl("old_l_2");
		tmp = ft_strdup(pwd->value);
		if (ft_lastchar(pwd->value) != '/')
			tmp = ft_strjoinfree(tmp, "/");
		tmp = ft_strjoinfree(tmp, curpath);
	}
	else
		tmp = ft_strdup(curpath);
	ft_strdel(&curpath);
ft_putendl("old_l_3");
	res = final_curpath(tmp, pwd, oldpwd);
ft_putendl("old_l_4");
	ft_strdel(&tmp);
	return (res);
}

uint8_t	isdot(char *str)
{
	if (str)
	{
		if (str[0] && str[0] == '.')
			return (1);
	}
	return (0);
}

int		check_fold(char *cmd, t_line **env, char *p)
{
	char	*curpath;
	t_line	*cdpath;
	t_line	*pwd;

	pwd = get_pwd(env, "PWD");
	if (cmd[0] != '/' && !isdot(cmd))
	{
		if ((cdpath = get_smtg(*env, "CDPATH")))
			curpath = concat_cdpath(cmd, cdpath->value);
		else
			curpath = ft_strdup(cmd);
	}
	else if (isdot(cmd) || cmd[0] == '/')
		curpath = ft_strdup(cmd);
	if (p && ft_strchr(p, 'P') && check_path(curpath, 0))
	{
		chdir(curpath);
		ft_strdel(&(pwd->value));
		pwd->value = getcwd(pwd->value, 0);
		ft_strdel(&curpath);
	}
	else if (!p || (p && ft_strchr(p, 'L')))
	{
ft_putendl("check_f");
		return (opt_l(curpath, pwd, get_pwd(env, "OLDPWD")));
	}
	return (0);
}

int		p_cd(t_line **env, char **cmd)
{
	char	*path;
	char	*p;
	int		err;
	int		i;

	i = 1;
	p = ft_getopt(cmd, &i);
	(!ft_checkopt(p, "LP", 2) || !(i - 1)) ? 0 : i--;
	err = (cmd[i] && cmd[i + 1]) ? 1 : 0;
	path = (cmd[i]) ? ft_strdup(cmd[i]) : NULL;
	if (path && ft_strequ(path, "-"))
		err = go_oldpwd(*env);
	else
	{
ft_putendl("p_cd_1");
		path = ((!path || path[0] == '~')) ? copy_home(*env, path) : path;
ft_putendl("p_cd_2");
		err = (!path) ? error("cd", "HOME", 7) : check_fold(path, env, p);
ft_putendl("p_cd_3");
	}
	(err && err != 7) ? error("cd", cmd[i], err) : 0;
	ft_strdel(&path);
	ft_strdel(&p);
	return (err);
}
