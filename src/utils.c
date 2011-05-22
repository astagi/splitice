/*
        Developed by Andrea Stagi <stagi.andrea@gmail.com>

        Splitice: split and splice your files
        Copyright (C) 2010 Andrea Stagi <stagi.andrea@gmail.com>

        This program is free software: you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation, either version 3 of the License, or
        (at your option) any later version.

        This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "utils.h"
#include "md5.h"

char* md5(const char* string)
{
    MD5_CTX mdContext;
    unsigned int len = strlen (string);
    const char* md5_string;
    char* flnm;

    MD5Init (&mdContext);
    MD5Update (&mdContext, string, len);
    MD5Final (&mdContext);

    md5_string = (char *)malloc(35 * sizeof(char));

    int i;

    for (i = 0; i < 16; i++)
        sprintf (md5_string, "%s%02x", md5_string, mdContext.digest[i]);
   
    return md5_string;

}

