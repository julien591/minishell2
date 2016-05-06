/*
** comma.c for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/src
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 10:53:17 2016 julien
** Last update Fri May 06 11:04:24 2016 julien
*/

#include	<stdlib.h>
#include	"env.h"
#include	"builtin.h"
#include	"str.h"

int	is_comma(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] == ';')
	return (1);
      i++;
    }
  return (0);
}

void	free_cmd(char **cmd)
{
  int	i;

  i = 0;
  while (cmd[i] != NULL)
    {
      free(cmd[i]);
      i++;
    }
  free(cmd);
}

void	comma(char *s, t_envi *instuctions)
{
  char	**tmp;
  char	**cmd;
  int	i;

  i = 0;
  tmp = my_str_to_wordtab(s, ';');
  while (tmp[i] != NULL)
    {
      tmp[i] = del_space(tmp[i]);
      i++;
    }
  i = 0;
  while (tmp[i] != NULL)
    {
      cmd = my_str_to_wordtab(tmp[i], ' ');
      if (general_pars2(tmp[i], instuctions) == 0)
	{
	  if (test_builtin(instuctions, s) != 0)
	    my_test(instuctions, cmd);
	}
      free_cmd(cmd);
      i++;
    }
  free_cmd(tmp);
}
