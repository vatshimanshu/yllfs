#include<stdlib.h>
#include <string.h>

#include "fs_ds.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("This program expects atleast one argument. Please"
               " specify the name of the vdisk\n");
        return 0;
    }

    char* disk = argv[1];
    char path[100] = "../vdisk/";
    strcat(path, disk);

    create_fs(path);
    mount_fs(path);
    print_super_block();
    read_first_byte_blocks(path);
}
