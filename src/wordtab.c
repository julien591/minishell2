/*
** wordtab.c for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/src
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 10:55:33 2016 julien
** Last update Fri May 27 11:46:00 2016 Julien Leleu
*/

#include	<stdlib.h>
#include	"env.h"
#include	"str.h"

int		count_word(char *str, char elem)
{
  int 		i;
  int		word;

  i = 0;
  word = 0;
  while (i != my_strlen(str))
    {
      if (str[i] == elem)
	word++;
      i++;
    }
  return (word + 1);
}

char		**my_str_to_wordtab(char *str, char elem)
{
  char		**ret;
  int		words;
  int		i;
  int		j;
  int		k;

  i = 0;
  k = 0;
  if (str == NULL)
    return (NULL);
  words = count_word(str, elem) + 1;
  ret = my_double_malloc(sizeof(char *) * (words));
  while (i <= my_strlen(str))
    {
      ret[k] = my_malloc(sizeof(char) * (my_strlen(str) + 1));
      j = 0;
      while (str[i] != elem && str[i] != '\0')
	  ret[k][j++] = str[i++];
      ret[k++][j] = '\0';
      i++;
    }
  ret[k] = NULL;
  return (ret);
}
