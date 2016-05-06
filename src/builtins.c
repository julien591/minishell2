/*
** builtins.c for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/src
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 10:51:21 2016 julien
** Last update Fri May 06 14:41:56 2016 julien
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	"env.h"
#include	"str.h"
#include	"free.h"
#include	"builtin.h"

void	builtin_env(char **env)
{
  int	i;

  i = 0;
  while (env[i] != NULL)
    {
      my_putstr(env[i]);
      write(1, "\n", 1);
      i++;
    }
}

int	exit_check(char *str)
{
  int	i;

  i = (str[0] == '-') ? 1 : 0;
  while (str[i] != '\0')
    {
      if (str[i] >= '0' && str[i] <= '9')
      i++;
      else if (str[i] == '-')
	{
	  write(2, "exit: Badly formed number.\n", 27);
	  return (-1);
	}
      else
	{
	  write(2, "exit: Expression Syntax.\n", 25);
	  return (-1);
	}
    }
  return (0);
}

void	builtin_exit(t_envi *instuctions, char *s)
{
  int	nb_exit;
  int	i;

  i = 0;
  while (instuctions->cmd[i] != NULL)
    i++;
  if (i == 1)
    {
      free_all(instuctions, s);
      my_putstr("exit\n");
      exit(0);
    }
  else if (i == 2)
    {
      if (exit_check(instuctions->cmd[1]) == 0)
	{
	  nb_exit = my_getnbr(instuctions->cmd[1]);
	  free_all(instuctions, s);
	  my_putstr("exit\n");
	  exit(nb_exit);
	}
    }
  else if (i > 2)
    write(2, "exit: Expression Syntax.\n", 25);
}

int	test_builtin(t_envi *instuctions, char *s)
{
  int	nb_arg;

  nb_arg = 0;
  while (instuctions->cmd[nb_arg] != '\0')
    nb_arg++;
  if (my_strcmp(instuctions->cmd[0], "cd") == 0)
    {
      builtin_cd(instuctions, nb_arg);
      return (0);
    }
  else if (my_strcmp(instuctions->cmd[0], "env") == 0)
    {
      builtin_env(instuctions->env);
      return (0);
    }
  else if (my_strcmp(instuctions->cmd[0], "exit") == 0)
    {
      builtin_exit(instuctions, s);
      return (0);
    }
   else if ((my_strcmp(instuctions->cmd[0], "setenv") == 0)
	    || (my_strcmp(instuctions->cmd[0], "unsetenv") == 0))
    {
      setenv_unsetenv(instuctions);
      return (0);
    }
  return (-1);
}
