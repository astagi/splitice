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

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "main.h"
#include "splitice.h"


int main(int argc, char* argv[])
{
    int n_parts = 0;
    char *filename =  NULL;
    char *dest_directory = NULL;

    n_parts = atoi(argv[4]);
    filename = argv[2];
    dest_directory = argv[3];

    char password[300];

    if(strcmp(argv[1], CMD_SPLIT) == 0)
    {
        scanf("%s", &password);
        split(filename, dest_directory, n_parts, password);
    }

    else if(strcmp(argv[1], CMD_SPLICE) == 0)
    {
        //TODO: implement the splice function
        scanf("%s", &password);
        splice(filename, password);
    }

    return 0;
}
