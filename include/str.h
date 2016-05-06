/*
** str.h for PSU_2015_minishell2 in /home/julien/PSU_2015_minishell2/include
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Fri May 06 14:40:57 2016 julien
** Last update Fri May 06 14:41:02 2016 julien
*/

#ifndef		STR_H_
# define	STR_H_

void	my_putstr(char *str);
void	my_putchar(char c);
int	my_getnbr(char *str);
int	my_strcmp(char *s1, char *s2);
int	my_strlen(char *str);
char	*my_strcat(char *path, char *cmd);
char	**my_str_to_wordtab(char *str, char elem);
char	*my_read();
int	my_test(t_envi *instuctions, char **cmd);
int	just_space(char *str, int i);
int	just_comma(char *str);
char	*del_space(char *str);
int	general_pars2(char *s, t_envi *instuctions);
char	*my_strcpy(char *dest, char *src);
void	my_put_error(char *str, char *command);
char	*get_path(char **path, char *s);
char	*my_malloc(size_t size);
char	**my_double_malloc(size_t size);

#endif /* !STR_H_ */
