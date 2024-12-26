/* ioapi.c -- IO base function header for compress/uncompress .zip
   part of the MiniZip project

   Copyright (C) 2012-2017 Nathan Moinvaziri
     https://github.com/nmoinvaz/minizip
   Modifications for Zip64 support
     Copyright (C) 2009-2010 Mathias Svensson
     http://result42.com
   Copyright (C) 1998-2010 Gilles Vollant
     http://www.winimage.com/zLibDll/minizip.html

   This program is distributed under the terms of the same license as zlib.
   See the accompanying LICENSE file for the full text of the license.
*/

#include <stdlib.h>
#include <string.h>

#if defined unix || defined __APPLE__
#include <sys/types.h>
#include <unistd.h>
#endif

#include "ioapi.h"

#if defined(_WIN32)
#  define snprintf _snprintf
#endif

voidpf call_zopendisk64(const zlib_filefunc64_32_def *pfilefunc, voidpf filestream, uint32_t number_disk, int mode)
{
    if (pfilefunc->zfile_func64.zopendisk64_file != NULL)
        return (*(pfilefunc->zfile_func64.zopendisk64_file)) (pfilefunc->zfile_func64.opaque, filestream, number_disk, mode);
    return (*(pfilefunc->zopendisk32_file))(pfilefunc->zfile_func64.opaque, filestream, number_disk, mode);
}

static voidpf   ZCALLBACK fopen_file_func(ZIP_UNUSED voidpf opaque, const char *filename, int mode);
static uint32_t ZCALLBACK fread_file_func(voidpf opaque, voidpf stream, void* buf, uint32_t size);
static uint32_t ZCALLBACK fwrite_file_func(voidpf opaque, voidpf stream, const void *buf, uint32_t size);
static uint64_t ZCALLBACK ftell64_file_func(voidpf opaque, voidpf stream);
static long     ZCALLBACK fseek64_file_func(voidpf opaque, voidpf stream, uint64_t offset, int origin);
static int      ZCALLBACK fclose_file_func(voidpf opaque, voidpf stream);
static int      ZCALLBACK ferror_file_func(voidpf opaque, voidpf stream);

typedef struct 
{
    FILE *file;
    int filenameLength;
    void *filename;
} FILE_IOPOSIX;

static voidpf file_build_ioposix(FILE *file, const char *filename)
{
    FILE_IOPOSIX *ioposix = NULL;
    if (file == NULL)
        return NULL;
    ioposix = (FILE_IOPOSIX*)malloc(sizeof(FILE_IOPOSIX));
    ioposix->file = file;
    ioposix->filenameLength = (int)strlen(filename) + 1;
    ioposix->filename = (char*)malloc(ioposix->filenameLength * sizeof(char));
    strncpy((char*)ioposix->filename, filename, ioposix->filenameLength);
    return (voidpf)ioposix;
}

static voidpf ZCALLBACK fopen_file_func(ZIP_UNUSED voidpf opaque, const char *filename, int mode)
{
    FILE* file = NULL;
    const char *mode_fopen = NULL;
    if ((mode & ZLIB_FILEFUNC_MODE_READWRITEFILTER) == ZLIB_FILEFUNC_MODE_READ)
        mode_fopen = "rb";
    else if (mode & ZLIB_FILEFUNC_MODE_EXISTING)
        mode_fopen = "r+b";
    else if (mode & ZLIB_FILEFUNC_MODE_CREATE)
        mode_fopen = "wb";

    if ((filename != NULL) && (mode_fopen != NULL))
    {
        file = fopen(filename, mode_fopen);
        return file_build_ioposix(file, filename);
    }
    return file;
}

static voidpf ZCALLBACK fopen64_file_func(ZIP_UNUSED voidpf opaque, const void *filename, int mode)
{
    FILE* file = NULL;
    const char *mode_fopen = NULL;
    if ((mode & ZLIB_FILEFUNC_MODE_READWRITEFILTER) == ZLIB_FILEFUNC_MODE_READ)
        mode_fopen = "rb";
    else if (mode & ZLIB_FILEFUNC_MODE_EXISTING)
        mode_fopen = "r+b";
    else if (mode & ZLIB_FILEFUNC_MODE_CREATE)
        mode_fopen = "wb";

    if ((filename != NULL) && (mode_fopen != NULL))
    {
        file = fopen64((const char*)filename, mode_fopen);
        return file_build_ioposix(file, (const char*)filename);
    }
    return file;
}

static voidpf ZCALLBACK fopendisk64_file_func(voidpf opaque, voidpf stream, uint32_t number_disk, int mode)
{
    FILE_IOPOSIX *ioposix = NULL;
    char *diskFilename = NULL;
    voidpf ret = NULL;
    int i = 0;

    if (stream == NULL)
        return NULL;
    ioposix = (FILE_IOPOSIX*)stream;
    diskFilename = (char*)malloc(ioposix->filenameLength * sizeof(char));
    strncpy(diskFilename, (const char*)ioposix->filename, ioposix->filenameLength);
    for (i = ioposix->filenameLength - 1; i >= 0; i -= 1)
    {
        if (diskFilename[i] != '.')
            continue;
        snprintf(&diskFilename[i], ioposix->filenameLength - i, ".z%02u", number_disk + 1);
        break;
    }
    if (i >= 0)
        ret = fopen64_file_func(opaque, diskFilename, mode);
    free(diskFilename);
    return ret;
}

static voidpf ZCALLBACK fopendisk_file_func(voidpf opaque, voidpf stream, uint32_t number_disk, int mode)
{
    FILE_IOPOSIX *ioposix = NULL;
    char *diskFilename = NULL;
    voidpf ret = NULL;
    int i = 0;

    if (stream == NULL)
        return NULL;
    ioposix = (FILE_IOPOSIX*)stream;
    diskFilename = (char*)malloc(ioposix->filenameLength * sizeof(char));
    strncpy(diskFilename, (const char*)ioposix->filename, ioposix->filenameLength);
    for (i = ioposix->filenameLength - 1; i >= 0; i -= 1)
    {
        if (diskFilename[i] != '.')
            continue;
        snprintf(&diskFilename[i], ioposix->filenameLength - i, ".z%02u", number_disk + 1);
        break;
    }
    if (i >= 0)
        ret = fopen_file_func(opaque, diskFilename, mode);
    free(diskFilename);
    return ret;
}

static uint32_t ZCALLBACK fread_file_func(ZIP_UNUSED voidpf opaque, voidpf stream, void* buf, uint32_t size)
{
    FILE_IOPOSIX *ioposix = NULL;
    uint32_t read = (uint32_t)-1;
    if (stream == NULL)
        return read;
    ioposix = (FILE_IOPOSIX*)stream;
    read = (uint32_t)fread(buf, 1, (size_t)size, ioposix->file);
    return read;
}

static uint32_t ZCALLBACK fwrite_file_func(ZIP_UNUSED voidpf opaque, voidpf stream, const void *buf, uint32_t size)
{
    FILE_IOPOSIX *ioposix = NULL;
    uint32_t written = (uint32_t)-1;
    if (stream == NULL)
        return written;
    ioposix = (FILE_IOPOSIX*)stream;
    written = (uint32_t)fwrite(buf, 1, (size_t)size, ioposix->file);
    return written;
}

static long ZCALLBACK ftell_file_func(ZIP_UNUSED voidpf opaque, voidpf stream)
{
    FILE_IOPOSIX *ioposix = NULL;
    long ret = -1;
    if (stream == NULL)
        return ret;
    ioposix = (FILE_IOPOSIX*)stream;
    ret = ftell(ioposix->file);
    return ret;
}

static uint64_t ZCALLBACK ftell64_file_func(ZIP_UNUSED voidpf opaque, voidpf stream)
{
    FILE_IOPOSIX *ioposix = NULL;
    uint64_t ret = (uint64_t)-1;
    if (stream == NULL)
        return ret;
    ioposix = (FILE_IOPOSIX*)stream;
    ret = ftello64(ioposix->file);
    return ret;
}

static long ZCALLBACK fseek_file_func(ZIP_UNUSED voidpf opaque, voidpf stream, uint32_t offset, int origin)
{
    FILE_IOPOSIX *ioposix = NULL;
    int fseek_origin = 0;
    long ret = 0;

    if (stream == NULL)
        return -1;
    ioposix = (FILE_IOPOSIX*)stream;

    switch (origin)
    {
        case ZLIB_FILEFUNC_SEEK_CUR:
            fseek_origin = SEEK_CUR;
            break;
        case ZLIB_FILEFUNC_SEEK_END:
            fseek_origin = SEEK_END;
            break;
        case ZLIB_FILEFUNC_SEEK_SET:
            fseek_origin = SEEK_SET;
            break;
        default:
            return -1;
    }
    if (fseek(ioposix->file, offset, fseek_origin) != 0)
        ret = -1;
    return ret;
}

static long ZCALLBACK fseek64_file_func(ZIP_UNUSED voidpf opaque, voidpf stream, uint64_t offset, int origin)
{
    FILE_IOPOSIX *ioposix = NULL;
    int fseek_origin = 0;
    long ret = 0;

    if (stream == NULL)
        return -1;
    ioposix = (FILE_IOPOSIX*)stream;

    switch (origin)
    {
        case ZLIB_FILEFUNC_SEEK_CUR:
            fseek_origin = SEEK_CUR;
            break;
        case ZLIB_FILEFUNC_SEEK_END:
            fseek_origin = SEEK_END;
            break;
        case ZLIB_FILEFUNC_SEEK_SET:
            fseek_origin = SEEK_SET;
            break;
        default:
            return -1;
    }

    if (fseeko64(ioposix->file, offset, fseek_origin) != 0)
        ret = -1;

    return ret;
}

static int ZCALLBACK fclose_file_func(ZIP_UNUSED voidpf opaque, voidpf stream)
{
    FILE_IOPOSIX *ioposix = NULL;
    int ret = -1;
    if (stream == NULL)
        return ret;
    ioposix = (FILE_IOPOSIX*)stream;
    if (ioposix->filename != NULL)
        free(ioposix->filename);
    ret = fclose(ioposix->file);
    free(ioposix);
    return ret;
}

static int ZCALLBACK ferror_file_func(ZIP_UNUSED voidpf opaque, voidpf stream)
{
    FILE_IOPOSIX *ioposix = NULL;
    int ret = -1;
    if (stream == NULL)
        return ret;
    ioposix = (FILE_IOPOSIX*)stream;
    ret = ferror(ioposix->file);
    return ret;
}

