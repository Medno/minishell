/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 15:06:46 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/27 15:28:12 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H

# define PROMPT "$> "
# include "./libft/libft.h"
# include <sys/stat.h>
# include <signal.h>

pid_t			g_fath;
char			*g_process;

typedef struct	s_line
{
	char			*var;
	char			*value;
	struct s_line	*next;
}				t_line;

void			s_env(t_line **env, char **cmd);
int				uns_env(t_line **env, char **cmd);
void			n_env(t_line *env, char **cmd);
int				p_cd(t_line **env, char **cmd);
unsigned char	p_exit(char **cmd);
void			ft_echo(t_line *env, char **cmd);

void			replace_ls(t_line *env, char **cmd);
t_line			*get_smtg(t_line *env, char *str);

t_line			*init_line(t_line **env, char *cmd);
t_line			*fill_line(char **env);
t_line			*dup_line(t_line *env);
void			line_pushback(t_line **first, t_line *add);
char			**line_to_tab(t_line **first);
void			p_line(t_line *line);
int				clean_line(t_line **prev, t_line *tmp);
void			del_line(t_line **first);

uint8_t			execute_cmd(t_line **env, char *cmd);
void			check_bin(char **env, char **cmd, char *path);

void			entry_message(char **av, char **env);
void			prompt(int sig);
void			p_prompt(void);

void			kill_child(int sig);
void			ret_fath(pid_t fath);
void			incr_shlvl(t_line **env);

int				error(char *built, char *cmd, int code);
int				usage(char *name, char *opt, char err, int e);

#endif
