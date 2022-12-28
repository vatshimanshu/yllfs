#include <stdio.h>
#include <string.h>
#include "fs_ds.h"

struct super_block superBlock;

struct super_block __init_super_block()
{
    struct super_block sb;
    sb.block_size = BLOCK_SIZE;
    sb.num_blocks = NUM_BLOCKS;
    sb.num_inode_blocks = NUM_INODE_BLOCKS;
    sb.num_inodes = (int)(BLOCK_SIZE * NUM_INODE_BLOCKS) / sizeof(struct inode);

    return sb;
}

// create blocks for file system and write the blocks to a file: vdisk
void create_fs(char *vdisk)
{
    FILE *fptr;

    fptr = fopen(vdisk, "wb");

    // write super block to vdisk
    struct super_block sb = __init_super_block();
    fwrite(&sb, sizeof(struct super_block), 1, fptr);
    
    // TODO: ADD bitmap for inodes and blocks
    // TODO: write inode entry for root directory along with directory content

    // write inode blocks to vdisk
    struct inode inode = {0};
    for (int i = 0; i < sb.num_inodes; i++) {
        fwrite(&inode, sizeof(struct inode), 1, fptr);
    }

    // write data blocks
    char data[sb.block_size];
    data[0] = 'B';
    for (int i = 0; i < sb.num_blocks; i++)
    {
        fwrite(&data, sizeof(data), 1, fptr);
    }

    fclose(fptr);
}

// mount the file system from simulated vdisk
// read super_block into memory
void mount_fs(char* vdisk) {
    FILE *fptr;
    fptr = fopen(vdisk, "rb");

    fread(&superBlock, sizeof(struct super_block), 1, fptr);

    fclose(fptr);
}

void print_super_block() {
    printf("contents of super block\n");

    printf("block size: %d\n", superBlock.block_size);
    printf("number of blocks: %d\n", superBlock.num_blocks);
    printf("number of inodes: %d\n", superBlock.num_inodes);
    printf("number of inode blocks: %d\n", superBlock.num_inode_blocks);
}

void read_first_byte_blocks(char *vdisk)
{
    FILE *fptr;
    struct block b;

    // open vdisk
    fptr = fopen(vdisk, "rb");

    // move the cursor to first block
    fseek(fptr, sizeof(struct super_block), SEEK_CUR);
    fseek(fptr, superBlock.num_inodes * sizeof(struct inode), SEEK_CUR);

    // read the blocks
    for (int i = 0; i < superBlock.num_blocks; i++) {
        fread(&b, sizeof(struct block), 1, fptr);
        printf("first byte of block %d: %c\n", i, b.data[0]);
    }

    fclose(fptr);
}