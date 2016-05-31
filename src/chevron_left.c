/*
** chevron_left.c for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/src
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 10:52:03 2016 julien
** Last update Fri May 27 11:18:51 2016 Julien Leleu
*/

#include	<fcntl.h>
#include	<stdlib.h>
#include	<sys/wait.h>
#include	<unistd.h>
#include	"env.h"
#include	"free.h"
#include	"str.h"

int		is_left_chevron(char *str)
{
  int		i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] == '<')
	{
	  if (str[i + 1] == '<')
	    return (2);
	  else
	    return (1);
	}
      i++;
    }
  return (0);
}

int		open_file(char *file)
{
  int		fd;

  fd = open(file, O_CREAT | O_RDWR);
  if (fd == -1)
    {
      write(2, "Error, cannot open ", 19);
      write(2, file, my_strlen(file));
      write(2, "\n", 1);
      return (-1);
    }
  return (fd);
}

int		left_redir(char *bin, char **cmd, char **env, char *file)
{
  int		fd;
  pid_t		pid;
  int		status;

  if ((fd = open_file(file)) == -1)
    return (-1);
  pid = fork();
  if (pid > 0)
    waitpid(pid, &status, 0);
  else
    {
      dup2(fd, 0);
      if (bin != NULL)
	execve(bin, cmd, env);
      exit(0);
    }
    if (WIFSIGNALED(status))
    {
      if (WTERMSIG(status) == 11)
	write(2, "Segmentation fault\n", 19);
    }
  close(fd);
  return (0);
}

void		left_chevron(char *s, t_envi *instuctions)
{
  char		**tmp;
  char		**cmd;
  char		*bin;
  int		i;

  i = 0;
  tmp = my_str_to_wordtab(s, '<');
  while (tmp[i] != NULL)
    {
      tmp[i] = del_space(tmp[i]);
      i++;
    }
  cmd = my_str_to_wordtab(tmp[0], ' ');
  bin = get_path(instuctions->path, cmd[0]);
  left_redir(bin, cmd, instuctions->env, tmp[i - 1]);
  free_cmd(cmd);
  free_cmd(tmp);
}
