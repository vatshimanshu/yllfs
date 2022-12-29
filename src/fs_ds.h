#include <stdio.h>
#include <time.h>

#define BLOCK_SIZE 512
//TODO: generalise number of blocks and number of inodes
#define NUM_BLOCKS 100
#define NUM_INODE_BLOCKS 5

struct super_block {
    int block_size;
    int num_blocks;
    int num_inodes;
    int num_inode_blocks;
};

struct inode {
    int mode;
    int size;
    int blocks;
    int direct[4];
    int indirect;
};

#define NUM_INODES (int)(BLOCK_SIZE * NUM_INODE_BLOCKS) / sizeof(struct inode)

struct inode_bitmap {
    char bitmap[NUM_INODES];
};

struct data_bitmap {
    char bitmap[NUM_BLOCKS];
};

struct block {
    char data[BLOCK_SIZE];
};

void create_fs(char* vdisk);
void mount_fs(char *vdisk);
void read_first_byte_blocks(char *vdisk);
void print_super_block();