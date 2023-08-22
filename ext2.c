/****************************************
	interviewer : daniel
	date:  jan 16
	status: approved
	quote of the day :"Every great developer you know got there by solving problems they were unqualified to solve until they actually did it." 
	quoter : Patrick McKenzie
****************************************/


#include <stddef.h>    /*size_t*/
#include <fcntl.h>     /*open,read*/
#include <unistd.h>    /*SEEK_SET*/
#include <stdio.h>     /* printf*/
#include <asm/types.h> /*__u32,16*/
#include <assert.h>
#include <stdlib.h> /*exit*/
#include <string.h> /*strcmp*/

#include "ext2.h"

#define EXT2_SUPER_MAGIC 0xEF53
#define BASE_OFFSET 1024
#define BLOCK_OFFSET(block) (block * block_size)
#define OPTIMIZ1 ((block * (super->s_blocks_per_group * block_size)) + (block_size * desc->bg_inode_table) + (super->s_inode_size * index))
#define OPTIMIZ2 ((block * (super->s_blocks_per_group * block_size)) + (block_size * 2) + (super->s_inode_size * index))
#define OCTAL_BASE (8)
#define DECIMAL_BASE (10)
#define BITS_PER_PERMIT (3)
#define DIGIT3 (3)
#define DIGIT4 (4)
#define HIGHEST_PERMIT (777)
__u32 block_size = 0;
__u16 inode_size = 0;
__u32 inode_table = 0;

int main(int argc, char **argv)
{
    int ext2_fd = 0;
    char *virtual_disk = NULL;
    char *file_path = NULL;
    char *job = NULL;
    char *permission = NULL;
    struct ext2_super_block *super = (struct ext2_super_block *)malloc(sizeof(struct ext2_super_block));
    struct ext2_group_desc *desc = (struct ext2_group_desc *)malloc(sizeof(struct ext2_group_desc));
    struct ext2_inode *inode = (struct ext2_inode *)malloc(sizeof(struct ext2_inode));
    struct ext2_dir_entry_2 *dir = (struct ext2_dir_entry_2 *)malloc(sizeof(struct ext2_dir_entry_2));

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <virtual_disk> <file_path>\n", argv[0]);
        exit(1);
    }

    virtual_disk = argv[1];
    file_path = argv[2];
    job = argv[3];
    permission = argv[4];

    FindSuperBlock(ext2_fd, virtual_disk, super);
    FindGroupDescripor(ext2_fd, virtual_disk, desc);

    FindInode(ext2_fd, file_path, virtual_disk, super, desc, inode, dir, permission, job);

    close(ext2_fd);
    free( super);
    free( desc);
    free( inode);
    free( dir);
    return 0;
}
int FindSuperBlock(int fd, char *virtual_disk, struct ext2_super_block *super)
{
    assert(virtual_disk);
    assert(super);

    if ((fd = open(virtual_disk, O_RDONLY)) < 0)
    {
        return -1;
    }

    if (lseek(fd, BASE_OFFSET, SEEK_SET) < 0) /*boot block*/
    {
        return -1;
    }
    read(fd, super, sizeof(struct ext2_super_block));

    assert(super->s_magic == EXT2_SUPER_MAGIC); /* finding if we are in ext2*/

    block_size = BASE_OFFSET << super->s_log_block_size;
    inode_size = super->s_inode_size;

    return 0;
}
int FindGroupDescripor(int fd, char *virtual_disk, struct ext2_group_desc *desc)
{
    assert(virtual_disk);
    assert(desc);

    if ((fd = open(virtual_disk, O_RDONLY)) < 0)
    {
        return -1;
    }
    if (lseek(fd, block_size, SEEK_SET) < 0) /*superblock*/
    {
        return -1;
    }
    read(fd, desc, sizeof(struct ext2_group_desc));
    inode_table = desc->bg_inode_table;
    return 0;
}
void PrintSuperblock(struct ext2_super_block *super, char *devic_name)
{
    assert(devic_name);
    assert(super);
    printf("Reading super-block from device : %s\n"
           "Inodes count            : %u\n"
           "Blocks count            : %u\n"
           "Reserved blocks count   : %u\n"
           "Free blocks count       : %u\n"
           "Free inodes count       : %u\n"
           "First data block        : %u\n"
           "Block size              : %u\n"
           "Blocks per group        : %u\n"
           "Inodes per group        : %u\n"
           "Creator OS              : %u\n"
           "First non-reserved inode: %u\n"
           "Size of inode structure : %hu\n"
           "\n",
           devic_name,
           super->s_inodes_count,
           super->s_blocks_count,
           super->s_r_blocks_count, /* reserved blocks count */
           super->s_free_blocks_count,
           super->s_free_inodes_count,
           super->s_first_data_block,
           block_size,
           super->s_blocks_per_group,
           super->s_inodes_per_group,
           super->s_creator_os,
           super->s_first_ino, /* first non-reserved inode */
           super->s_inode_size);
}
void PrintGroupDescripor(struct ext2_group_desc *desc, char *devic_name)
{
    assert(devic_name);
    assert(desc);
    printf("Reading first group-descriptor from device :%s\n"
           "Blocks bitmap block: %u\n"
           "Inodes bitmap block: %u\n"
           "Inodes table block : %u\n"
           "Free blocks count  : %u\n"
           "Free inodes count  : %u\n"
           "Directories count  : %u\n"
           "\n",
           devic_name,
           desc->bg_block_bitmap,
           desc->bg_inode_bitmap,
           desc->bg_inode_table,
           desc->bg_free_blocks_count,
           desc->bg_free_inodes_count,
           desc->bg_used_dirs_count);
}
void PrintInode(struct ext2_inode *inode)
{
    assert(inode);
    printf("file mode :%d\n"
           "file uid :%d\n"
           "file size :%d\n",
           inode->i_mode,
           inode->i_uid,
           inode->i_size);
}
void PrintDir(struct ext2_dir_entry_2 *dir)
{
    assert(dir);

    printf("inode : %d\n "
           "rec_len : %d\n"
           "name_len :%d \n"
           "file_type : %d\n"
           "name : %s\n",
           dir->inode,
           dir->rec_len,
           dir->name_len,
           dir->file_type,
           dir->name);
}
void Printfile(int fd, struct ext2_inode *inode)
{
    char *buffer = (char *)malloc(inode->i_size);

    assert(inode);

    lseek(fd, (block_size * inode->i_block[0]), SEEK_SET);
    read(fd, buffer, inode->i_size);
    puts(buffer);
    free(buffer);
}
int optimizion(int fd, struct ext2_group_desc *desc, struct ext2_super_block *super, struct ext2_dir_entry_2 *dir)
{
    int block = (dir->inode - 1) / super->s_inodes_per_group; 
    int index = (dir->inode - 1) % super->s_inodes_per_group;

    assert(desc);
    assert(super);
    assert(dir);

    if (block % 3 == 0 || block % 5 == 0 || block % 7 == 0 || block < 2) /*find offset with optimizion*/
    {
        if (lseek(fd, OPTIMIZ1, SEEK_SET) < 0)
        {
            return -1;
        }
    }
    else
    {
        if (lseek(fd, OPTIMIZ2, SEEK_SET) < 0)
        {
            return -1;
        }
    }
    return 0;
}
int FindInode(int fd, char *file_path, char *virtual_disk, struct ext2_super_block *super, struct ext2_group_desc *desc, struct ext2_inode *inode, struct ext2_dir_entry_2 *dir, char *permission, char *job)
{
    __u32 dir_sum = 0;
    char *token = NULL;

    assert(file_path);
    assert(super);
    assert(desc);
    assert(inode);
    assert(dir);

    if ((fd = open(virtual_disk, O_RDWR)) < 0)
    {
        return -1;
    }

    if (lseek(fd, block_size * inode_table + sizeof(struct ext2_inode) * 2, SEEK_SET) < 0) /*find inode*/
    {
        return -1;
    }
    read(fd, inode, sizeof(struct ext2_inode));

    if (lseek(fd, block_size * inode->i_block[0], SEEK_SET) < 0) /*dir entery*/
    {
        return -1;
    }

    token = strtok(file_path, "/");
    while (NULL != token)
    {
        dir_sum = 0;

        lseek(fd, (block_size * inode->i_block[0]), SEEK_SET);
        while (0 != strcmp(dir->name, token) && dir_sum < block_size)
        {
            read(fd, dir, sizeof(struct ext2_dir_entry_2));
            dir_sum += dir->rec_len;
            if (lseek(fd, block_size * inode->i_block[0] + dir_sum, SEEK_SET) < 0) /*find dir entry for specific name*/
            {
                return -1;
            }
        }

        /*optimizion for dir entry*/
        if (optimizion(fd, desc, super, dir) < 0)
        {
            return -1;
        }

        read(fd, inode, sizeof(struct ext2_inode)); /*specific file inode*/

        token = strtok(NULL, "/");
    }

    if (0 != job && !strcmp(job, "chmod"))
    {
        if (optimizion(fd, desc, super, dir) < 0) /*when the inod starts*/
        {
            return -1;
        }
        Chmod(fd, inode, permission);
    }
    else
    {
        PrintSuperblock(super, virtual_disk);
        PrintGroupDescripor(desc, virtual_disk);
        Printfile(fd, inode);
    }
    return 0;
}
int Chmod(int fd, struct ext2_inode *inode, char *permission)
{
    int number = atoi(permission);
    unsigned short int mode = inode->i_mode;
    int countnum = number <= HIGHEST_PERMIT ? DIGIT3 : DIGIT4;  /* finding how many digit we have*/

    assert(inode);
    assert(permission);

    if (IsInrange(permission))
    {
        fprintf(stderr, "wrong permission\n");
        exit(1);;
    }

    number = octal_to_decimal(number);

    mode >>= countnum * BITS_PER_PERMIT; 
    mode <<= countnum * BITS_PER_PERMIT; /*clear permission bits */
    mode += number; /*adding new premisision*/

    write(fd, &mode, sizeof(unsigned short int));
    fsync(fd);

    return 0;
}
int IsInrange(char *permission)
{
    int count = 0;

    assert(permission);

    while ('\0' != *permission && '0' <= *permission && '7' >= *permission)  /* premison is octal and 4 digit long*/
    {
        ++permission;
        ++count;
    }

    if (0 != *permission && (DIGIT3 >= count || DIGIT4 <= count))
    {
        return -1;
    }

    return 0;
}
int octal_to_decimal(int octal)
{
    int decimal = 0;
    int i = 1;
    while (octal != 0)
    {
        decimal += (octal % DECIMAL_BASE) * i;
        i *= OCTAL_BASE;
        octal /= DECIMAL_BASE;
    }
    return decimal;
}