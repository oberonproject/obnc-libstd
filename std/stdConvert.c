/*Copyright 2017 Karl Landstrom <karl@miasap.se>

This file is part of obnc-libstd.

obnc-libstd is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

obnc-libstd is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with obnc-libstd.  If not, see <http://www.gnu.org/licenses/>.*/

#include ".obnc/stdConvert.h"
#include <obnc/OBNC.h>
#include <float.h>
#include <stdlib.h>
#include <string.h>

static int Length(int i)
{
	int n;
	
	if (i == 0) {
		n = 1;
	} else {
		n = 0;
		if (i < 0) {
			n++;
		}
		while (i != 0) {
			i = i / 10;
			n++;
		}
	}
	return n;
}


void stdConvert_IntToString_(OBNC_LONGI int i, char s[], OBNC_LONGI int sLen, int *done)
{
	int strLen, n;
	
	strLen = Length(i);
	if (strLen < sLen) {
		n = sprintf(s, "%" OBNC_INT_MOD "d", i);
		*done = n == strLen;
	} else {
		*done = 0;
	}
}


void stdConvert_RealToString_(OBNC_LONGR double x, char s[], OBNC_LONGI int sLen, int *done)
{
	char buffer[LDBL_DIG + 9]; /*LDBL_DIG + strlen("-") + strlen(".") + strlen("e+9999") + 1*/
	int n;
	
	*done = 0;
	n = sprintf(buffer, "%" OBNC_REAL_MOD_W "E", x);
	if (n < sLen) {
		strcpy(s, buffer);
		*done = 1;
	}	
}


static void CheckTermination(const char s[], OBNC_LONGI int sLen)
{
	OBNC_LONGI int i;
	
	i = 0;
	while ((i < sLen) && (s[i] != '\0')) {
		i++;
	}
	OBNC_IT(i, sLen);
}


void stdConvert_StringToInt_(const char s[], OBNC_LONGI int sLen, OBNC_LONGI int *i, int *done)
{
	OBNC_LONGI unsigned j;
	int n;
	char ch;
	
	CheckTermination(s, sLen);
	
	/*TODO: check for overflow by using strtol*/
	n = sscanf(s, " %" OBNC_INT_MOD "x%c", &j, &ch);
    if ((n == 2) && (ch == 'H')) {
    		*i = j;
		*done = 1;
	} else {
		n = sscanf(s, " %" OBNC_INT_MOD "d", i);
		*done = n == 1;
	}
}


void stdConvert_StringToReal_(const char s[], OBNC_LONGI int sLen, OBNC_LONGR double *x, int *done)
{
	int n;
	
	CheckTermination(s, sLen);

	n = sscanf(s, " %" OBNC_REAL_MOD_R "f", x);
	*done = n == 1;
}


void stdConvert_Init(void)
{
}
