/*
** execute.c for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/src
**
** Made by Julien
** Login   <julien@epitech.net>
**
** Started on  Thu May 26 18:35:11 2016 Julien
** Last update Fri May 27 10:53:22 2016 Julien Leleu
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	<sys/types.h>
#include	<sys/wait.h>
#include	"env.h"
#include	"str.h"

int		more_one_slash(char *str)
{
  int		i;
  int		j;

  i = 0;
  if (str == NULL)
    return (-1);
  while (str[i] != '\0')
    {
      if (str[i] == '/')
	{
	  j = 0;
	  while (str[i] == '/' && str[i] != '\0')
	    {
	      j++;
	      i++;
	    }
	  if (j > 1)
	    return (1);
	}
      i++;
    }
  return (0);
}

void		my_put_error(char *str, char *command)
{
  if (my_strcmp(str, "cd") == 0)
    {
      if (command != NULL)
	write(2, command, my_strlen(command));
      write(2, ": No such file or directory.\n", 29);
    }
  else
    {
      write(2, str, my_strlen(str));
      write(2, command, 21);
    }
}

void		execute(char *file, t_envi *instuctions, char **cmd)
{
  pid_t 	pid;
  int		status;

  pid = fork();
  if (pid > 0)
    waitpid(pid, &status, 0);
  else
    {
      execve(file, cmd, instuctions->env);
      exit(0);
    }
  if (WIFSIGNALED(status))
    {
      if (WTERMSIG(status) == 11)
	write(2, "Segmentation fault\n", 19);
    }
}

int		my_test(t_envi *instuctions, char **cmd)
{
  int		i;
  char		*test;

  i = 0;
  if (access(cmd[0], F_OK) == 0)
    execute(cmd[0], instuctions, cmd);
  else if (instuctions->path != NULL)
    {
      while (instuctions->path[i] != '\0')
	{
	  test = my_strcat(instuctions->path[i], cmd[0]);
	  if ((access(test, F_OK) == 0) && (more_one_slash(test) == 0))
	    {
	      execute(test, instuctions, cmd);
	      free(test);
	      return (0);
	    }
	  else
	    free(test);
	  i++;
	}
      my_put_error(cmd[0], ": Command not found.\n");
    }
  return (0);
}
