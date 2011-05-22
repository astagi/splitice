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
 * Module name: splitice.h
 * Notes: the main library
 * Date: 01/05/11
 * Author: Andrea Stagi <stagi.andrea(at)gmail.com>
 *
 ***/

#ifndef __SPLITICE_H__
#define __SPLITICE_H__

#define N_PROCESSES    2

#define DEST_NOT_FOUND 1
#define FILE_NOT_FOUND 2
#define PARTS_ERROR    3

int split(const char* filepath, const char*  dest_directory, int n_parts, const char* password);
int splice(const char* filepath);

#endif
