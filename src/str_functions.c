/*
** str_functions.c for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/src
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 10:55:20 2016 julien
** Last update Fri May 06 10:55:21 2016 julien
*/

#include	<stdlib.h>
#include	<unistd.h>
#include	"env.h"
#include	"str.h"

char	*my_strcpy(char *dest, char *src)
{
  int i;

  i = 0;
  while (src[i] != 0)
    {
      dest[i] = src[i];
      i++;
    }
  dest[i] = '\0';
  return (dest);
}

void	my_putstr(char *str)
{
  write(1, str, my_strlen(str));
}

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    i++;
  return (i);
}

int	my_strcmp(char *s1, char *s2)
{
  int 	i;

  i = 0;
  while (s2[i] != '\0')
    {
      if (s1[i] == s2[i])
	i++;
      else
	return (-1);
    }
  return (0);
}

char	*my_strcat(char *path, char *cmd)
{
  int	i;
  int	j;
  char	*str;

  i = 0;
  j = 0;
  str = my_malloc(sizeof(char) * (my_strlen(path) + my_strlen(cmd) + 2));
  if (str == NULL)
    return (NULL);
  while (path[i] != '\0')
    {
      str[i] = path[i];
      i++;
    }
  str[i] = '/';
  i++;
  while (cmd[j] != '\0')
    {
      str[i] = cmd[j];
      i++;
      j++;
    }
  str[i] = '\0';
  return (str);
}
