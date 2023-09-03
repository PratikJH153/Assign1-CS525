#include "storage_mgr.h"
#include "dberror.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


FILE *file;

/* Initializing the storage manager */
/*
fseek
fopen
fread
malloc
memset
fclose
free
destroy
*/

void initStorageManager(void)
{
    file = NULL;
    char *fileName = "stgr";

    createPageFile(fileName);
}

RC createPageFile(char *fileName)
{
    // check to open file if not exists:
    // malloc to allocate memory
    // memset fill the blocks with \0
    // SMFILE HANDLE file append

    RC return_code = RC_OK;

    FILE *file = fopen(fileName, "rb");
   
    if (file != NULL)
    {
        printf("FILE ALREADY EXISTS");
        return return_code; 
    }
    else
    {
        FILE *file = fopen(fileName, "wb");
        char *buffer = (char *)malloc(PAGE_SIZE * sizeof(char));

        if (buffer == NULL)
        {
            printf("Memory allocation failed.\n");
            return_code = RC_FILE_HANDLE_NOT_INIT;

            return return_code;
        }

        memset(buffer, '\0', 1);

        free(buffer);
        fclose(file);

        return return_code;
    }
}

RC openPageFile(char *fileName, SM_FileHandle *fHandle)
{
    File *file = fopen(fileName, fHandle);

    if (file == NULL){
        return RC_FILE_NOT_FOUND;
    }
    else{
        return RC_OK;
    }

}

RC closePageFile(SM_FileHandle *fHandle)
{
    RC return_code;
    bool closeFile = fclose(fHandle);

    if (closeFile == true){
        printf("File is closed!");
        return_code = RC_OK;
    } else{
        printf("Problem occured while closing file!");
        return_code = RC_FILE_NOT_FOUND;
    }

    return return_code;
}

RC destroyPageFile(char *fileName)
{
    RC return_code;
    bool removeFile = remove(fileName);

    if (removeFile == true){
        printf("File is removed!");
        return_code = RC_OK;
    } else{
        printf("Problem occured while destroying file!");
        return_code = RC_FILE_NOT_FOUND;
    }

    return return_code;
}

/* Reading functions to read from the block */

RC readBlock(int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage)
{
    return RC_OK;
}

int getBlockPos(SM_FileHandle *fHandle)
{
    return 1;
}

RC readFirstBlock(SM_FileHandle *fHandle, SM_PageHandle memPage)
{
    return RC_OK;
}

RC readPreviousBlock(SM_FileHandle *fHandle, SM_PageHandle memPage)
{
    return RC_OK;
}

RC readCurrentBlock(SM_FileHandle *fHandle, SM_PageHandle memPage)
{
    return RC_OK;
}

RC readNextBlock(SM_FileHandle *fHandle, SM_PageHandle memPage)
{
    return RC_OK;
}

RC readLastBlock(SM_FileHandle *fHandle, SM_PageHandle memPage)
{
    return RC_OK;
}

/* Writing functions to read from the block */

RC writeBlock(int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage)
{
    return RC_OK;
}

RC writeCurrentBlock(SM_FileHandle *fHandle, SM_PageHandle memPage)
{
    return RC_OK;
}

RC appendEmptyBlock(SM_FileHandle *fHandle)
{
    return RC_OK;
}

RC ensureCapacity(int numberOfPages, SM_FileHandle *fHandle)
{
    return RC_OK;
}