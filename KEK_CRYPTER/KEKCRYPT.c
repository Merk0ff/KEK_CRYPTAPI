/***************************************************************
* Copyright (C) 2016
*    Philip Dukshtau.
***************************************************************/

/* FILE NAME   : CRYPTER.C
* PURPOSE     : Xor text crypter declaration file.
* PROGRAMMERS  :
*               Mitish Konstantin,
*               Dukshtau Philip.
* LAST UPDATE : 01.03.2016.
* NOTE        : None.
*
* No part of this file may be changed without agreement by
* Philip Dukshtau.
*/

#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "KEKCRYPT.H"

/* Generate key function */
KEY KeyGen( char *Key )
{
  int i = 0, j = 0,
      time[20],
      keylen = 0,
      keylen_mem;

  int settime,
      settime_mem,
      systeminfo,
      systeminfo_mas[20];
  POINT Cursor_pos;
  KEY OutKey;

  settime = clock();
  settime_mem = settime;

  while (i < 20 && settime != 0)
    time[i++] = settime % 10, settime /= 10;

  GetCursorPos(&Cursor_pos);

  if (Cursor_pos.x == 0 || Cursor_pos.y == 0)
    systeminfo = settime_mem * GetSystemMetrics(SM_CXCURSOR) * GetSystemMetrics(SM_CXICON);
  else
    systeminfo = Cursor_pos.x * Cursor_pos.y * settime_mem;

  while (Key[keylen] != 0)
    keylen++;

  while (j < 20 && systeminfo != 0)
    systeminfo_mas[j++] = systeminfo % 10, systeminfo /= 10;

  keylen_mem = keylen + j;

  while (j > 0)
    Key[keylen++] = systeminfo_mas[j--];

  i = 0;
  OutKey.keylen = keylen_mem;
  while (keylen_mem > 0)
  {
    if (time[i] == 0)
      i = 0;
    OutKey.key[keylen_mem] = Key[keylen_mem--] ^ time[i++];
  }
  return OutKey;
} /* End of 'KeyGen' function */

/* Load file function */
char * LoadFile( char *FileName, int *len )
{
  int ch;
  FILE *F;
  char *str;

  *len = 0;
  if ((F = fopen(FileName, "rb")) == NULL)
  {
    printf("File Loading error\n");
    return NULL;
  }
  while ((ch = fgetc(F)) != EOF)
    (*len)++;
  str = malloc((*len) + 1);
  if (str == NULL)
  {
    printf("File Loading error\n");
    fclose(F);
    return 0;
  }
  rewind(F);
  fread(str, 1, *len, F);
  str[*len] = 0;
  fclose(F);
  return str;
} /* End of 'LoadFile' function */

/* Save file function */
int SaveFile( char *FileName, char *str, int len )
{
  int i = 0;
  FILE *F;

  if ((F = fopen(FileName, "wb")) == NULL)
  {
    printf("Error creating file\n");
    return 0;
  }
  if (str == NULL)
  {
    printf("File Loading error\n");
    fclose(F);
    return 0;
  }
  fwrite(str, sizeof(char), len, F);
  fclose(F);
  return 1;
} /* End of 'SaveFile' function */

/* Load key function */
KEY LoadKey( char *FileName )
{
  int ch;
  FILE *F;
  KEY Key;

  if ((F = fopen(FileName, "rb")) == NULL)
  {
    printf("File Loading error\n");
    exit(0);
  }

  Key.keylen = 0;
  while ((ch = fgetc(F)) != EOF)
    Key.keylen++;

  rewind(F);
  fread(Key.key, 1, Key.keylen, F);
  Key.key[Key.keylen + 1] = 0;
  fclose(F);
  return Key;
} /* End of 'LoadKey' function */

/* Save key function */
int SaveKey( char *FileName, KEY Key )
{
  int i = 0;
  FILE *F;

  if ((F = fopen(FileName, "wb")) == NULL)
  {
    printf("Error creating file\n");
    return 0;
  }

  fwrite(Key.key, sizeof(char), Key.keylen, F);
  fclose(F);
  return 1;
} /* End of 'SaveKey' function */

/* Cript function */
char * Crypt( char *input, KEY Key, int len )
{
  int j, i;
  char *output = NULL;

  output = malloc(len);
  for (i = 0, j = 0; i < len; i++, j++)
  {
    if (j > Key.keylen)
      j = 0;
    output[i] = input[i] ^ Key.key[j];
  }
  return output;
} /* End of 'Crypt' function */
