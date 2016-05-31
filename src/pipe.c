/*
** pipe.c for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/src
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 10:54:52 2016 julien
** Last update Thu May 26 18:40:17 2016 Julien Leleu
*/

#include	<stdlib.h>
#include	<sys/types.h>
#include	<sys/wait.h>
#include	<unistd.h>
#include	"env.h"
#include	"free.h"
#include	"str.h"
#include	"token.h"

int		check(char ***command, int nb)
{
  int		i;

  i = 0;
  while (i != nb)
    {
      if (command[i][0] == NULL || access(command[i][0], F_OK) != 0)
	return (-1);
      i++;
    }
  return (0);
}

int		is_pipe(char *str)
{
  int		i;
  int		pip;

  i = 0;
  pip = 0;
  while (str[i] != '\0')
    {
      if (str[i] == '|' && str[i + 1] != '|')
	pip++;
      i++;
    }
  return (pip);
}

void		end(int p[], int nb, char ***command)
{
  int		i;
  int		status;

  i = 0;
  status = 0;
  while (i < nb)
    {
      close(p[i]);
      i++;
    }
  i = 0;
  while (i < nb)
    {
      wait(&status);
      i++;
    }
  i = 0;
  while (command[i] != NULL)
    {
      free_env(command[i]);
      i++;
    }
  free(command);
}

void		exec_pipe(char **env, char ***command, int p[], int nb)
{
  pid_t		pid;
  int		i;
  int		j;
  int		k;

  i = 0;
  j = 0;
  while (command[i] != NULL)
    {
      if ((pid = fork()) == 0)
	{
	  if (command[i + 1] != NULL)
	    dup2(p[j + 1], 1);
	  if (j != 0)
	    dup2(p[j - 2], 0);
	  k = 0;
	  while (k < nb)
	    close(p[k++]);
	  execve(command[i][0], command[i], env);
	}
      i++;
      j = j + 2;
    }
  end(p, nb, command);
}

void		init_pipe(char *s, t_envi *instuctions)
{
  char		**tmp;
  int		p[2 * nb_pipes(s)];
  int		i;

  i = 0;
  tmp = my_str_to_wordtab(s, '|');
  while (tmp[i] != NULL)
    {
      tmp[i] = del_space(tmp[i]);
      i++;
    }
  i = 0;
  instuctions = my_triple_array(tmp, instuctions);
  while (i < nb_pipes(s))
    {
      if (pipe(p + i * 2) < 0)
	pipe_error();
      i++;
    }
  instuctions->command = set_commands(instuctions, instuctions->command);
  if (check(instuctions->command, instuctions->nb_cmd) != -1)
    exec_pipe(instuctions->env, instuctions->command, p, (2 * nb_pipes(s)));
  else
    special_free(instuctions->command, instuctions->nb_cmd);
}
