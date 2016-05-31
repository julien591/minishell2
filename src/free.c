/*
** free.c for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/src
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 10:53:44 2016 julien
** Last update Thu May 26 18:37:07 2016 Julien Leleu
*/

#include	<stdlib.h>
#include	"env.h"

void		free_path(char *envp, char **path)
{
  int		i;

  i = 0;
  if (path != NULL)
    {
      while (path[i] != NULL)
	{
	  free(path[i]);
	  i++;
	}
      free(path);
    }
  if (envp != NULL)
    free(envp);
}

void		free_command(char *s, char **cmd)
{
  int		i;

  i = 0;
  while (cmd[i] != NULL)
    {
      free(cmd[i]);
      i++;
    }
  if (cmd != NULL)
    free(cmd);
  if (s != NULL)
    free(s);
}

void		free_all(t_envi *instuctions, char *s)
{
  int		i;

  i = 0;
  if (instuctions->cmd != NULL)
    {
      while (instuctions->cmd[i] != NULL)
	free(instuctions->cmd[i++]);
      free(instuctions->cmd);
    }
  i = 0;
  while (instuctions->path != NULL && instuctions->path[i] != NULL)
    free(instuctions->path[i++]);
  i = 0;
  while (instuctions->env[i] != NULL)
    free(instuctions->env[i++]);
  if (instuctions->envp != NULL)
    free(instuctions->envp);
  if (instuctions->path != NULL)
    free(instuctions->path);
  if (instuctions->env != NULL)
    free(instuctions->env);
  if (s != NULL)
    free(s);
  free(instuctions);
}

void		double_free(char **cmd1, char **cmd2)
{
  int		i;

  i = 0;
  if (cmd1 != NULL)
    {
      while (cmd1[i] != NULL)
	{
	  free(cmd1[i]);
	  i++;
	}
      free(cmd1);
    }
  i = 0;
  if (cmd2 != NULL)
    {
      while (cmd2[i] != NULL)
	{
	  free(cmd2[i]);
	  i++;
	}
      free(cmd2);
    }
}

void		free_env(char **env)
{
  int		i;

  i = 0;
  if (env != NULL)
    {
      while (env[i] != NULL)
	{
	  free(env[i]);
	  i++;
	}
      free(env);
    }
}
