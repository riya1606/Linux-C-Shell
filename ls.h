#ifndef __LS_H
#define __LS_H

int ls_basic (char **list, int i, char *home_dir);
int ls_a (char **list, int i, char *home_dir);
int ls_l (char **list, int i, char *home_dir);
int ls_al (char **list, int i, char *home_dir);
void ls_call(char **list, int cnt, char* home_dir);
#endif
