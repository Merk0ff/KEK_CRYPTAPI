/***************************************************************
* Copyright (C) 2016
*    Philip Dukshtau.
***************************************************************/

/* FILE NAME   : CRYPTER.C
* PURPOSE     : main file.
* PROGRAMMERS  :
*               Mitish Konstantin,
*               Dukshtau Philip.
* LAST UPDATE : 01.03.2016.
* NOTE        : None.
*
* No part of this file may be changed without agreement by
* Philip Dukshtau.
*/

#include <conio.h>
#include <string.h>
#include <stdio.h>

#include "KEKCRYPT.H"

int main(int Argc, char *Argv[])
{
  char *i = NULL, *o = NULL;
  char key[256], Fname[256];
  KEY GenKey;
  int l;

  if (Argc != 4 || !(strcmp(Argv[1], "c") == 0 ||
    strcmp(Argv[1], "d") == 0))
  {
    printf("Usage:\n%s {c|d} InFile OutFile\n", Argv[0]);
    return 1;
  }

  if (Argv[1][0] == 'c')
  {
    printf("Insert key word(MAX - 256): ");

    scanf("%s", key);
    GenKey = KeyGen(key);

    if ((i = LoadFile(Argv[2], &l)) == NULL)
    {
      _getch();
      return 0;
    }
    o = Crypt(i, GenKey, l);
    if (SaveFile(Argv[3], o, l) == 0)
    {
      _getch();
      return 0;
    }

    printf("Enter file name to save key ");
    scanf("%s", Fname);
    if (SaveKey(Fname, GenKey) == 0)
    {
      printf("Cant save key");
      _getch();
      return 0;
    }
  }

  if (Argv[1][0] == 'd')
  {
    if ((i = LoadFile(Argv[2], &l)) == NULL)
    {
      _getch();
      return 0;
    }

    printf("Enter file name to save key ");
    scanf("%s", Fname);
    GenKey = LoadKey(Fname);

    o = Crypt(i, GenKey, l);
    if (SaveFile(Argv[3], o, l) == 0)
    {
      _getch();
      return 0;
    }
  }

  printf("\nSuccess\n");
  _getch();
}