/*
** setenv_unsetenv.c for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/src
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 10:55:11 2016 julien
** Last update Fri May 06 11:18:51 2016 julien
*/

#include	<stdlib.h>
#include	<unistd.h>
#include	"env.h"
#include	"builtin.h"
#include	"str.h"
#include	"free.h"

char	*replace_value(char *ret, int i, char *value, char **env)
{
  int	j;

  j = 0;
  while (env[i][j] != '=')
    {
      ret[j] = env[i][j];
      j++;
    }
  ret[j] = '=';
  j++;
  free(env[i]);
  i = 0;
  if (value != NULL)
    {
      while (value[i] != '\0')
	{
	  ret[j] = value[i];
	  j++;
	  i++;
	}
    }
  ret[j] = '\0';
  return (ret);
}

void	setenv_(t_envi *ins)
{
  int	i;
  char	*ret;

  i = 0;
  while ((my_strcmp(ins->env[i], ins->cmd[1])) != 0)
            i++;
  ret = my_malloc(sizeof(char) * (my_strlen(ins->env[i])
			 + my_strlen(ins->cmd[1]) + 1));
  ret = replace_value(ret, i, ins->cmd[2], ins->env);
  ins->env[i] = ret;
}

int	is_exist(char **env, char *to_find)
{
  int	i;

  i = 0;
  while (env[i] != NULL)
    {
      if (my_strcmp(env[i], to_find) == 0)
	return (1);
      i++;
    }
  return (0);
}

void	del_value(t_envi *ins)
{
  char	**new;
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (ins->env[i] != NULL)
    i++;
  new = my_double_malloc(sizeof(char *) * (i + 1));
  i = 0;
  while (ins->env[i] != NULL)
    {
      if (my_strcmp(ins->env[i], ins->cmd[1]) == 0)
	i++;
      if (ins->env[i] != NULL)
	{
	  new[j] = my_malloc(sizeof(char) * (my_strlen(ins->env[i]) + 1));
	  my_strcpy(new[j], ins->env[i]);
	  i++;
	  j++;
	}
    }
  new[j] = NULL;
  free_env(ins->env);
  ins->env = new;
}

void	setenv_unsetenv(t_envi *instuctions)
{
  if (my_strcmp(instuctions->cmd[0], "setenv") == 0)
    {
      if (instuctions->cmd[1] == NULL)
	builtin_env(instuctions->env);
      else if (is_exist(instuctions->env, instuctions->cmd[1]) == 1)
	setenv_(instuctions);
      else if (is_exist(instuctions->env, instuctions->cmd[1]) == 0)
	new_env(instuctions);
    }
  if (my_strcmp(instuctions->cmd[0], "unsetenv") == 0)
    {
      if (instuctions->cmd[1] == NULL)
	write(2, "unsetenv: Too few arguments.\n", 29);
      else if (is_exist(instuctions->env, instuctions->cmd[1]) == 1)
	del_value(instuctions);
    }
}
