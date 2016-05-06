/*
** malloc.c for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/src
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 10:54:31 2016 julien
** Last update Fri May 06 10:54:33 2016 julien
*/

#include	<stdlib.h>
#include	<unistd.h>

char	*my_malloc(size_t size)
{
  char	*str;

  str = malloc(size);
  if (str == NULL)
    {
      write(2, "Malloc failed, exit...\n", 22);
      exit(84);
    }
  return (str);
}

char	**my_double_malloc(size_t size)
{
  char	**str;

  str = malloc(size);
  if (str == NULL)
    {
      write(2, "Malloc failed, exit...\n", 22);
      exit(84);
    }
  return (str);
}
