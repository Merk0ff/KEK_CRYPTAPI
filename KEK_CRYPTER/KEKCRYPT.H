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

/* Generate key function */
KEY KeyGen(char *Key);

/* Load key function */
KEY LoadKey(char *FileName);

/* Save key function */
int SaveKey(char *FileName, KEY Key);

/* Cript function */
char * Crypt(char *input, KEY Key, int len);


/* Load file function */
char * LoadFile(char *FileName, int *len);

/* Save file function */
int SaveFile(char *FileName, char *str, int len);
