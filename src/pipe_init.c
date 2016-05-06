/*
** pipe_init.c for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Thu May 05 23:35:54 2016 julien
** Last update Fri May 06 10:49:06 2016 julien
*/

#include	<stdlib.h>
#include	<unistd.h>
#include	"env.h"
#include	"free.h"
#include	"str.h"

char	***my_triple_array(char **cut)
{
  char	***cmd;
  int	i;

  i = 0;
  while (cut[i] != NULL)
    i++;
  if ((cmd = malloc(sizeof(char **) * (i + 1))) == NULL)
    return (NULL);
  i = 0;
  while (cut[i] != NULL)
    {
      cmd[i] = my_str_to_wordtab(cut[i], ' ');
      i++;
    }
  cmd[i] = NULL;
  free_env(cut);
  return (cmd);
}

char	***set_commaand(t_envi *instuctions, char ***command)
{
  int	i;

  i = 0;
  while (command[i] != NULL)
    {
      command[i][0] = get_path(instuctions->path, command[i][0]);
      i++;
    }
  return (command);
}

int	nb_pipes(char *str)
{
  int	i;
  int	pipes;

  i = 0;
  pipes = 0;
  while (str[i] != '\0')
    {
      if (str[i] == '|')
	pipes++;
      i++;
    }
  return (pipes);
}
