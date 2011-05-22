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

/***
 * 
 * Module name: defs.h
 * Notes: a file containing all definitions of structs
 * Date: 01/05/11
 * Author: Andrea Stagi <stagi.andrea(at)gmail.com>
 *
 ***/

#ifndef __DEFS_H__
#define __DEFS_H__

#include <sys/stat.h>

typedef struct
{
    off_t dimention;
    off_t start;
    const char* name;
    const char* filepath;

}FilePart;

typedef struct
{
    int n_parts;
    const char* filepath;

}FileDescriptor;

typedef struct
{
    FilePart* parts;
    int parts_start;
    int parts_n;
    const char* filepath;

}SplitParameters;

#endif
