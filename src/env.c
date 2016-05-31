/*
** env.c for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/src
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 10:53:26 2016 julien
** Last update Thu May 26 18:34:13 2016 Julien Leleu
*/

#include	<stdlib.h>
#include	"env.h"
#include	"free.h"
#include	"str.h"

char		**copy_env(char **env)
{
  char		**env_cpy;
  int		i;

  i = 0;
  while (env[i] != NULL)
    i++;
  env_cpy = my_double_malloc(sizeof(char *) * (i + 1));
  if (env_cpy == NULL)
    return (NULL);
  i = 0;
  while (env[i] != NULL)
    {
      env_cpy[i] = my_malloc(sizeof(char) * (my_strlen(env[i]) + 1));
      my_strcpy(env_cpy[i], env[i]);
      i++;
    }
  env_cpy[i] = NULL;
  return (env_cpy);
}

char		**replace_env(char **env, char *line, char *to_replace)
{
  int		i;
  int		j;
  int		k;
  char		*str;

  i = 0;
  j = 0;
  k = 1;
  str = my_malloc(sizeof(char) * (my_strlen(line) + my_strlen(to_replace) + 2));
  while (env != NULL && env[i] != NULL && (k = my_strcmp(env[i], line)) != 0)
    i++;
  if (k != 0)
    return (NULL);
  k = 0;
  while (line[j] != '\0')
    {
      str[j] = line[j];
      j++;
    }
  while (to_replace[k] != '\0')
    str[j++] = to_replace[k++];
  str[j] = '\0';
  free(env[i]);
  env[i] = str;
  return (env);
}

char		*set_new_value(char *str, char *setting, char *value)
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  while (setting[i] != '\0')
    {
      str[i] = setting[i];
      i++;
    }
  str[i] = '=';
  i++;
  if (value != NULL)
    {
      while (value[j] != '\0')
	{
	  str[i] = value[j];
	  i++;
	  j++;
	}
    }
  str[i] = '\0';
  return (str);
}

void		new_env(t_envi *ins)
{
  char 		**new;
  int		i;

  i = 0;
  while (ins->env[i] != NULL)
    i++;
  new = my_double_malloc(sizeof(char *) * (i + 2));
  i = 0;
  while (ins->env[i] != NULL)
    {
      new[i] = my_malloc(sizeof(char) * (my_strlen(ins->env[i]) + 1));
      my_strcpy(new[i], ins->env[i]);
      i++;
    }
  if (ins->cmd[2] != NULL)
    new[i] = my_malloc(sizeof(char) * (my_strlen(ins->cmd[1]) +
			      my_strlen(ins->cmd[2]) + 2));
  else
    new[i] = my_malloc(sizeof(char) * (my_strlen(ins->cmd[1]) + 2));
  new[i] = set_new_value(new[i], ins->cmd[1], ins->cmd[2]);
  new[i + 1] = NULL;
  free_env(ins->env);
  ins->env = new;
}
