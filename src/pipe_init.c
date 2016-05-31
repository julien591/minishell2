/*
** pipe_init.c for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Thu May 05 23:35:54 2016 julien
** Last update Thu May 26 18:39:28 2016 Julien Leleu
*/

#include	<stdlib.h>
#include	<unistd.h>
#include	"env.h"
#include	"free.h"
#include	"str.h"

void		special_free(char ***command, int nb)
{
  int		i;

  i = 0;
  while (i != nb)
    {
      if (command[i] != NULL)
	free_env(command[i]);
      i++;
    }
  free(command);
}

void		pipe_error()
{
  write(2, "Could not pipe, exit\n", 21);
  exit(-1);
}

t_envi		*my_triple_array(char **cut, t_envi *instuctions)
{
  int		i;

  i = 0;
  instuctions->nb_cmd = 0;
  while (cut[i] != NULL)
    i++;
  if ((instuctions->command = malloc(sizeof(char **) * (i + 1))) == NULL)
    return (NULL);
  i = 0;
  while (cut[i] != NULL)
    {
      instuctions->command[i] = my_str_to_wordtab(cut[i], ' ');
      instuctions->nb_cmd++;
      i++;
    }
  instuctions->command[i] = NULL;
  free_env(cut);
  return (instuctions);
}

char		***set_commands(t_envi *instuctions, char ***command)
{
  int		i;

  i = 0;
  while (command[i] != NULL)
    {
      command[i][0] = get_path(instuctions->path, command[i][0]);
      i++;
    }
  return (command);
}

int		nb_pipes(char *str)
{
  int		i;
  int		pipes;

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
