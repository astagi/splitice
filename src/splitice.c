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
#include "splitice.h"
#include "defs.h"
#include "utils.h"


FilePart* __preparePartsFromFile(const char* filepath, const char* relative_filepath, const char* dest_folder, int n, char* password);
void* __splitProcess(void* args);
int __startSplitProcess(FilePart* parts, const char* filepath, int parts_start, int parts_n);
int __startSpliceProcess(const char* filepath);


int split(const char* filepath, const char* dest_directory, int n_parts, const char* password)
{

    int i = 0;
    int op = 0;
    int pos = 0;

    char* mainfile = NULL;

    char*  relative_filepath = NULL;

    FILE* mf = NULL;

    if((mf = fopen(filepath, "rb")) == NULL)
        return FILE_NOT_FOUND;

    relative_filepath = filename_from_path(filepath);

    mainfile = (char*)malloc((strlen(dest_directory) + strlen(relative_filepath)) * sizeof(char));

    sprintf(mainfile, "%s%s", dest_directory, relative_filepath);

    if(fopen(mainfile, "r"))
        return FILE_EXISTS;

    if(fopen(mainfile, "w") == NULL)
        return DEST_NOT_FOUND;

    FilePart* parts = __preparePartsFromFile(filepath, relative_filepath, dest_directory, n_parts, password);

    if(parts == NULL)
        return PARTS_ERROR;

    for(i = 0; i < n_parts; i++)
    {
        printf("\nDimension[%d] = %u", i, parts[i].dimention);
        printf("\nStart[%d] = %jd", i, parts[i].start);
        printf("\nName[%d] = %s", i, parts[i].name);
    }

    int parts_per_process = n_parts / N_PROCESSES;
    int last_parts = n_parts % N_PROCESSES;

    fclose(mf);

    for(i = 0; i < N_PROCESSES; i++)
    {
        if(i == N_PROCESSES - 1)
            __startSplitProcess(parts, filepath, parts_per_process * i, parts_per_process + last_parts);
        else
            __startSplitProcess(parts, filepath, parts_per_process * i, parts_per_process);
    }

    pthread_exit (NULL);

}


FilePart* __preparePartsFromFile(const char* filepath, const char* relative_filepath, const char* dest_folder, int n, char* password)
{

    FilePart* parts = NULL;
    struct stat buf;
    int i = 0;

    char *part_filepath = NULL;
    char* flnm = NULL;

    parts = (FilePart*)malloc(n * sizeof(FilePart));

    stat(filepath, &buf);

    off_t file_dim = buf.st_size;

    printf("%jd", file_dim);

    printf("%s", relative_filepath);

    for(i = 0; i < n; i++)
    {

        if(i == (n - 1))
            parts[i].dimention = (file_dim / n) + (file_dim % n);
        else
            parts[i].dimention = (file_dim / n);

        if(i == 0)
            parts[i].start = 0;
        else
            parts[i].start = ((parts[i - 1].dimention) * i);

        part_filepath = (char*)malloc((strlen(relative_filepath) + strlen(password) + 10) * sizeof(char));

        sprintf (part_filepath, "%s%s%d", relative_filepath, password, i);

        parts[i].name = (char*)malloc((strlen(dest_folder) + strlen(part_filepath)) * sizeof(char));

        sprintf (parts[i].name, "%s%s", dest_folder, md5(part_filepath));

    }

    return parts;

};


void* __splitProcess(void* args)
{

    FilePart* parts;
    int parts_start;
    int parts_n;
    const char* filepath;

    SplitParameters* parm;

    parm = (SplitParameters*)args;

    parts = parm->parts;
    parts_start = parm->parts_start;
    parts_n = parm->parts_n;
    filepath = parm->filepath;

    int i = 0;
    u_char* data;
    FILE* mf = NULL;
    FILE* newfile = NULL;

    printf("\n%s", filepath);

    if((mf = fopen(filepath, "rb")) == NULL)
        return 1;

    for(i = parts_start; i < parts_start + parts_n; i++)
    {
        data = (u_char*)malloc(parts[i].dimention * sizeof(u_char));
        fseeko(mf, parts[i].start , SEEK_SET);
        fread(data, sizeof(u_char), parts[i].dimention, mf);

        newfile = fopen(parts[i].name, "wb");
        fwrite (data , parts[i].dimention , sizeof(u_char) , newfile );
        fclose(newfile);
        free(data);
    }

    fclose(mf);
};


int __startSplitProcess(FilePart* parts, const char* filepath, int parts_start, int parts_n)
{
    pthread_t thread;

    SplitParameters* parm = (SplitParameters*)malloc(sizeof(SplitParameters));

    parm->parts = parts;
    parm->parts_start = parts_start;
    parm->parts_n = parts_n;
    parm->filepath = filepath;

    pthread_create (&thread, NULL, __splitProcess, (void *)parm);

};

int splice(const char* filepath, const char* password)
{

    int i = 0;

    char*  relative_filepath = NULL;
    char*  folder_filepath = NULL;

    char*  file_to_fetch = NULL;
    char*  md5_relative_filepath = NULL;

    off_t size;

    FILE* mf = NULL;
    FILE* newfile = NULL;

    u_char* data;

    struct stat buf;

    if((mf = fopen(filepath, "rb")) == NULL)
        return FILE_NOT_FOUND;
    else
        fclose(mf);

    relative_filepath = filename_from_path(filepath);
    folder_filepath = folder_from_path(filepath);

    file_to_fetch = (char*)malloc(sizeof(char) * 200);
    md5_relative_filepath = (char*)malloc(sizeof(char) * 50);

    newfile = fopen(filepath, "ab");
    
    do{
        sprintf (md5_relative_filepath, "%s%s%d", relative_filepath, password, i);
        md5_relative_filepath = md5(md5_relative_filepath);
        sprintf (file_to_fetch, "%s%s", folder_filepath, md5_relative_filepath);
        
        if(mf = fopen(file_to_fetch, "rb"))
        {

            stat(file_to_fetch, &buf);

            size = buf.st_size;

            data = (u_char*)malloc(size * sizeof(u_char));

            fread(data, sizeof(u_char), size, mf);

            fwrite (data , size, sizeof(u_char) , newfile );

            free(data);

            fclose(mf);
        }

        i++;

    }while(mf);

    fclose(newfile);

}




