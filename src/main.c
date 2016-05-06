/*
** main.c for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/src
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 10:54:22 2016 julien
** Last update Fri May 06 11:11:38 2016 julien
*/

#include	<signal.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	"env.h"
#include	"builtin.h"
#include	"free.h"
#include	"str.h"

int	prompt()
{
  char	dir[1024];

  if (getcwd(dir, sizeof(dir)) == NULL)
    return (0);
  write(2, dir, my_strlen(dir));
  write(2, " > ", 3);
  return (0);
}

void	handle_ctrl_c(int sig)
{
  signal(SIGINT, handle_ctrl_c);
  if (sig == SIGINT)
    {
      write(1, "\n", 1);
      prompt();
    }
}

char	*read_stdin()
{
  char	*s;

  s = NULL;
  while (s == NULL)
    {
      prompt();
      s = my_read();
      if (s != NULL && (s[0] == '\0'))
	{
	  free(s);
	  s = NULL;
	}
      if (s != NULL && ((just_comma(s) == 1) || (just_space(s, 0) == 1)))
	{
	  free(s);
	  s = NULL;
	}
    }
  s = del_space(s);
  return (s);
}

int		main(int ac, char **av, char **envp)
{
  char		*s;
  t_envi	*instuctions;

  (void)ac;
  (void)av;
  signal(SIGINT, handle_ctrl_c);
  if ((instuctions = malloc(sizeof(*instuctions))) == NULL)
    return (0);
  instuctions->env = copy_env(envp);
  while (1)
    {
      s = read_stdin();
      instuctions->envp = my_getenv(instuctions->env);
      instuctions->path = my_str_to_wordtab(instuctions->envp, ':');
      instuctions->cmd = my_str_to_wordtab(s, ' ');
      if (general_pars2(s, instuctions) == 0)
	{
	  if (test_builtin(instuctions, s) != 0)
	    my_test(instuctions, instuctions->cmd);
	}
      free_command(s, instuctions->cmd);
      free_path(instuctions->envp, instuctions->path);
    }
  return (0);
}
