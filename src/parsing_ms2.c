/*
** parsing_ms2.c for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/src
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 10:54:40 2016 julien
** Last update Fri May 06 15:07:57 2016 julien
*/

#include	<unistd.h>
#include	"env.h"
#include	"str.h"
#include	"token.h"

int	check_pipe(char *s)
{
  int	i;

  i = 0;
  while (i != my_strlen(s))
    {
      if (s[i] == '|' && s[i + 1] == '\0')
	return (-1);
      i++;
    }
  return (0);
}

int	check_error_m2(char *s, char **cmd)
{
  int	i;

  i = 0;
  if (my_strcmp(cmd[0], "|") == 0)
    {
      write(2, "Invalid null command.\n", 22);
      return (-1);
    }
  while (cmd[i] != NULL)
    {
      if (((my_strcmp(cmd[i], "|") == 0) && cmd[i + 1] == NULL)
	  || (check_pipe(s) == -1))
	{
	  write(2, "Invalid null command.\n", 22);
	  return (-1);
	}
      if (((cmd[i][0] == '<') || (cmd[i][0] == '>')) && cmd[i + 1] == NULL)
	{
	  write(2, "Missing name for redirect.\n", 27);
	  return (-1);
	}
      i++;
    }
  return (0);
}

int	check_chevron(char *s, t_envi *instuctions)
{
  int	i;

  if ((i = is_right_chevron(s)) >= 1)
    {
      right_chevron(s, instuctions, i);
      return (1);
    }
  if (is_left_chevron(s) == 1)
    {
      left_chevron(s, instuctions);
      return (1);
    }
  if (is_left_chevron(s) == 2)
    {
      double_left_chevron(s, instuctions);
      return (1);
    }
  return (0);
}

int	general_pars2(char *s, t_envi *instuctions)
{
  int	i;

  if (check_error_m2(s, instuctions->cmd) == -1)
    return (-1);
  if (is_comma(s) == 1)
    {
      comma(s, instuctions);
      return (1);
    }
  if (check_chevron(s, instuctions) == 1)
    return (1);
  if ((i = is_pipe(s)) >= 1)
    {
      init_pipe(s, instuctions);
      return (1);
    }
  return (0);
}
