/*
** parsing.c for parsing in /home/gastal_r/rendu/42sh/NE_PAS_TOUCHER/sources
** 
** Made by 
** Login   <gastal_r@epitech.net>
** 
** Started on  Fri May 27 15:55:40 2016 
** Last update Fri May 27 23:51:54 2016 
*/

#include		"42sh.h"


#include <stdio.h>

char			*pre_parsing(char *prompt, int i, int j)
{
  char			*buff;
  int			check;
  int			space;

  space = 0;
  check = 0;
  buff = malloc(sizeof(char) * (my_strlen(prompt) + 1));
  while (prompt[++i])
    {
      while (prompt[i] == '\t' || (check == 1 ? prompt[i] == ';' : 0)
	     || (space == 1 ? prompt[i] == ' ' : 0))
	i++;
      buff[++j] = prompt[i];
      if (prompt[i] != '\0' && prompt[i] == ';')
	check = 1;
      else
	check = 0;
      if (prompt[i] != '\0' && prompt[i] == ' ')
	space = 1;
      else
	space = 0;
    }
  buff[j + 1] = '\0';
  return (buff);
}

int			test_separator(char c)
{
  int			i;

  i = -1;
  while (SEPARATOR[++i])
    if (c == SEPARATOR[i])
      return (1);
  return (0);
}

int			calc_length(char *str, int i)
{
  if (test_separator(str[i]))
    {
      while (str[i] && test_separator(str[i]))
	i++;
      return (i);
    }
  else
    {
      while (str[i] && str[i] != ' ' && test_separator(str[i]) == 0)
	i++;
      return (i);
    }
  return (0);
}

int			fill_list(char *str, t_pcmd *pcmd, t_psep *psep, int i)
{
  int			j;
  char buff[10][10];
  int k;
  
  k = 0;
  j = 0;
  while (str[i])
    {
      if (str[i] == ' ')
	i++;
      i = (calc_length(str, i) - i) + i;
      /* MISE EN LISTE */
      while (j < i)
	{
	  if (str[j] == ' ')
	    j++;
	  printf("%c", str[j]);
	  j++;
	}
      puts (" ");
      k++;
    }
}

char			*pars_prompt(t_plist *list, char **env, char *st)
{
  t_pcmd		pcmd;
  t_psep		psep;
  t_cmd			*cmd;
  t_sep			*sep;

  if (init_prompt_list(&pcmd, &cmd, &psep, &sep) == -1)
    return (NULL);
  printf("%s\n", st);
  st = pre_parsing(st, -1, -1);
  printf("%s\n", st);
  fill_list(st, &pcmd, &psep, 0);
  free(st);
  free_prompt_list(&pcmd, cmd, &psep, sep);
  return ("0");
}
