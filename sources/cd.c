/*
** cd.c for cd in /home/gastal_r/rendu/42sh/NE_PAS_TOUCHER/sources
** 
** Made by 
** Login   <gastal_r@epitech.net>
** 
** Started on  Sun May 29 00:14:10 2016 
** Last update Thu Jun  2 00:08:33 2016 
*/

#include		"42sh.h"

void			cd_prec(t_plist *plist, char *path)
{
  int			length;

  length = my_strlen(path);
  while (path[length] != '/')
    length--;
  path[length] = '\0';
  chdir(path);
  if (get_oldpwd(plist) != NULL)
    act_oldpwd(plist, get_pwd(plist));
  if (get_pwd(plist) != NULL)
    act_pwd(plist, path);
  free(path);
}

int			cd_home(t_plist *plist)
{
  t_list		*list;

  list = plist->begin;
  while (my_strcmp("HOME", list->name) != 0)
    {
      list = list->next;
      if (list->next == NULL)
	return (0);
    }
  if (chdir(list->data) != 0)
    {
      my_putstr("cd: Can't change to home directory\n");
      return (0);
    }
  if (get_oldpwd(plist) != NULL)
    act_oldpwd(plist, get_pwd(plist));
  if (get_pwd(plist) != NULL)
    act_pwd(plist, list->data);
  return (0);
}

int			cd_dir(t_plist *plist, char *dir)
{
  char			*newpath;
  t_list		*list;
  struct stat folder;

  list = plist->begin;
  if (dir[0] == '~')
    return (cd_tile(plist, dir));
  while (my_strcmp("PWD", list->name) != 0)
    {
      list = list->next;
      if (list == NULL)
	return (0);
    }
  (list->data ? newpath = my_strdup(list->data) : 0);
  newpath = my_strcat(newpath, "/", -1, -1);
  newpath = my_strcat(newpath, dir, -1, -1);
  if (stat(dir, &folder) == 0 && S_ISDIR(folder.st_mode))
    if (folder.st_mode & S_IRGRP)
      {
	if (get_oldpwd(plist) != NULL)
	  act_oldpwd(plist, get_pwd(plist));
	act_pwd(plist, newpath);
      }
    else
      {
	my_putstr(dir);
	my_putstr(": Permission denied.\n");
	return (1);
      }
  else
    return (return_chdir(dir, newpath));
  free(newpath);
  return (0);
}

int			cd_tile(t_plist *plist, char *dir)
{
  char			*newpath;
  t_list		*list;

  list = plist->begin;
  while (my_strcmp("HOME", list->name) != 0)
    {
      list = list->next;
      if (list->next == NULL)
	return (0);
    }
  dir++;
  newpath = my_strdup(list->data);
  newpath = my_strcat(newpath, dir, -1, -1);
  if (chdir(newpath) != 0)
    {
      dir++;
      return (return_chdir(dir, newpath));
    }
  if (get_oldpwd(plist) != NULL)
    act_oldpwd(plist, get_pwd(plist));
  if (get_pwd(plist) != NULL)
    act_pwd(plist, newpath);
  free(newpath);
  return (0);
}

int			cd_old(t_plist *plist)
{
  char			*buff;

  if (get_oldpwd(plist) == NULL)
    return (0);
  buff = my_strdup(get_oldpwd(plist));
  if (get_oldpwd(plist) != NULL)
    act_oldpwd(plist, get_pwd(plist));
  if (get_pwd(plist) != NULL)
    act_pwd(plist, buff);
  chdir(buff);
  free(buff);
  return (0);
}
