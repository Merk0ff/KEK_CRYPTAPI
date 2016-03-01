/***************************************************************
* Copyright (C) 2016
*    Philip Dukshtau.
***************************************************************/

/* FILE NAME   : CRYPTER.C
* PURPOSE     : Xor text crypter header file.
* PROGRAMMERS  :
*               Mitish Konstantin,
*               Dukshtau Philip.
* LAST UPDATE : 01.03.2016.
* NOTE        : None.
*
* No part of this file may be changed without agreement by
* Philip Dukshtau.
*/
typedef struct
{
  char key[255];
  int keylen;
} KEY;

KEY KeyGen(char *Key);
char *LoadFile(char *FileName, int *len);
int SaveFile(char *FileName, char *str, int len);
KEY LoadKey(char *FileName);
int SaveKey(char *FileName, KEY Key);
char *Crypt(char *input, KEY Key, int len);