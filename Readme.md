## Table of Contents

1. Introduction
2. Initialization
3. File Creation
4. File Opening
5. File Closing
6. File Destroy
7. Reading Blocks
8. Writing Blocks

**Running the script**
Step 1-  $ make 
Step 2-  $ ./test_assign1

**Contributions**
Priyanka Karan: (initStorageManager(), destroyPageFile(), ensureCapacity()): 20%
Shikha Sharma: (openPageFile(), closePageFile(), readPreviousBlock()): 20%
Pratik Jadhav: (createPageFile(), readBlock(), readLastBlock()): 20%
Vedashree Shinde: (writeBlock(), writeCurrentBlock(), readCurrentBlock()): 20%
Vedant Landge: (appendEmptyBlock(), readNextBlock(), readFirstBlock()): 20%

---Introduction---
The Storage Manager code provides a simple interface for managing file operations, including creating, opening, closing, deleting, reading, and writing files. It uses the C programming language and standard file I/O functions to achieve these operations.

---Initialization---
**initStorageManager()**
- Initializes the storage manager by setting the global `file` pointer to `NULL`.
- Prints a message indicating successful initialization of the storage manager.

---File Creation---
**createPageFile(char *fileName)**
- Attempts to create a new page file with the given `fileName`.
- Checks if the file exists by attempting to open it in "read" mode. If the file is present, it returns a message. Otherwise, it opens the file using `fopen` in "write" mode, allocating memory to initialize the page content. Typically, `num_blocks` equals the page size, and `block_size` represents 1-byte character elements.
- Initializes a buffer to represent a page and writes it to the new file.
- Prints a success message upon successful file creation.
- Checks whether write is possible to the file using `fwrite` and whether fwrite returning the same number of pages

---File Opening---
**openPageFile(char *fileName, SM_FileHandle *fHandle)**
- Opens an existing page file specified by `fileName` and associates it with the provided file handle `fHandle`.
- Checks if the file exists by attempting to open it using `fopen` in "read binary" mode. If the file is present, it returns a message.
- Initializes the file handle's attributes such as `fileName`, `curPagePos`, `totalNumPages`, and `mgmtInfo`.
- Calculates the total number of pages in the file by seeking to the end of the file using `fseek` and then dividing the file size using `ftell` by the page size (PAGE_SIZE).
- Positions the file pointer at the beginning of the file using `rewind`.

---File closing---
**closePageFile(SM_FileHandle *fHandle)**
- Closes the file associated with the provided file handle.
- Checks if the file handle is valid and the file exists; if not, returns a message.
- Closes the file using the `fclose` function which take file as an input and prints a success message upon successful closure; if not, returns a failure message.

---File Destroy---
**destroyPageFile(char *fileName)**
- Destroys (removes) the page file specified by `fileName`.
- Closes the file if it's open.
- Uses the `remove` function to delete the file from the file system.
- Prints a success message upon successful file removal; if not, returns a failure message.

---Reading Blocks---
**readBlock(int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage)**<a name="reading-blocks"></a>
- Checks if the file handle is valid and the file exists; if not, returns a file does not exists message.
- Reads a block from the page file specified by `fHandle` at the given `pageNum` and stores it in `memPage`.
- Positions the file pointer to the appropriate location in the file.
- The function employs `fread` to read the contents of the page from the file into a memory buffer (memPage). It specifies the size of each element `size`, the count of elements to read `count`, and the file to read from (file).
- Reads the block into the `memPage` buffer.
- Validates if the read operation was successful and returns an error if it failed.

**getBlockPos(SM_FileHandle *fHandle)**
- Retrieves the current block position `block_pos` from the provided file handle `fHandle`.
- Checks if the file handle is valid; if not, returns a message.
- Returns the current block position.

**readFirstBlock(SM_FileHandle *fHandle, SM_PageHandle memPage)**
- Reads the first block of the page file associated with the given file handle `fHandle` and stores it in `memPage`.
- Calls `readBlock()` with the block position set to 0.

**readPreviousBlock(SM_FileHandle *fHandle, SM_PageHandle memPage)**
- Reads the block immediately before the current block in the page file associated with `fHandle` and stores it in `memPage`.
- Checks whether the position is not less than 0; if it is, it signifies that the page does not exist.
- Calls `readBlock()` with the block position decremented by 1.

**readCurrentBlock(SM_FileHandle *fHandle, SM_PageHandle memPage)**
- Reads the current block pointed to by the file handle `fHandle` and stores it in `memPage`.
- Calls `readBlock()` with the current block position.

**readNextBlock(SM_FileHandle *fHandle, SM_PageHandle memPage)**
- Reads the block immediately after the current block in the page file associated with `fHandle` and stores it in `memPage`.
- Checks whether the position does not exceed the total number of pages; if it does, it indicates the absence of the page.
- Calls `readBlock()` with the block position incremented by 1.

**readLastBlock(SM_FileHandle *fHandle, SM_PageHandle memPage)**
- Reads the last block of the page file associated with the given file handle `fHandle` and stores it in `memPage`.
- Calls `readBlock()` with the block position set to the total number of pages decremented by one.

---Writing Blocks---
**writeBlock(int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage)**
- Writes a block specified by `pageNum` from the provided `memPage` to the page file associated with `fHandle`.
- Checks if the file handle is valid, the file exists, and the page number is within bounds; if not, returns an error.
- Positions the file pointer to the appropriate location in the file using `fseek`.
- It then uses `fwrite` to write the contents of memPage to the file, effectively updating the specified block with new data.
- After writing, it updates the current page position `curPagePos` in the file handle and determines the new page count using `ftell` and page size and then recalculates the total number of pages `totalNumPages` by seeking to the end of the file.
- The function returns an appropriate return code based on the success or failure of these operations.

**writeCurrentBlock(SM_FileHandle *fHandle, SM_PageHandle memPage)**
- Writes the current block pointed to by the file handle `fHandle` using `getBlockPos`.
- Calls `writeBlock()` with the current block position with the data from `memPage`; else returns failure message.

**appendEmptyBlock(SM_FileHandle *fHandle)**
- It first checks if the file handle's associated file (file) exists. If it doesn't, it returns an error indicating that the file does not exist.
- Then uses `fseek` to move the file pointer to the end of the file, preparing it for appending an empty block.
- It then initializes an empty page by allocating memory for it using `calloc`. The size of the empty page is PAGE_SIZE bytes.
- The empty page is filled with zeros using `memset`.
- Using `fwrite`, it writes the contents of the empty page to the end of the file. It calculates the size, count, and the number of elements written to ensure a successful write operation.
- If the write operation is successful (i.e., the number of elements written matches the count), it increments the totalNumPages attribute in the file handle, indicating that an empty block has been added.
- Finally, it frees the memory allocated for the empty page using free.

**ensureCapacity(int numberOfPages, SM_FileHandle *fHandle)**
- Ensures that the page file associated with `fHandle` has at least `numberOfPages`.
- Checks if the file handle is valid; if not, returns a file handle not initialized message.
- Compares the current total number of pages in the file with `numberOfPages`.
- If the current total is less, uses `appendemptyblock` until the capacity is met, or returns an error message if write fails.