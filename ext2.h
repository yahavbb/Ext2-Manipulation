#ifndef __EXT2_H__ILRD__CR3_
#define __EXT2_H__ILRD__CR3_

#include "ext2_structs.h"

int FindSuperBlock(int super_fd, char *virtual_disk, struct ext2_super_block *super);
void PrintSuperblock(struct ext2_super_block *super, char *devic_name);
void PrintGroupDescripor(struct ext2_group_desc *desc, char *devic_name);
void Printfile(int fd, struct ext2_inode *inode);
void PrintInode(struct ext2_inode *inode);
void PrintDir(struct ext2_dir_entry_2 *dir);
int optimizion(int fd, struct ext2_group_desc *desc, struct ext2_super_block *super, struct ext2_dir_entry_2 *dir);
int FindInode(int fd, char *file_path, char *virtual_disk, struct ext2_super_block *super, struct ext2_group_desc *desc, struct ext2_inode *inode, struct ext2_dir_entry_2 *dir, char *permission, char *job);
int FindGroupDescripor(int fd, char *virtual_disk, struct ext2_group_desc *desc);
int Chmod(int fd, struct ext2_inode *inode, char *permission);
int IsInrange(char *permission);
int octal_to_decimal(int octal);

#endif /*__EXT2_H__ILRD__CR3_*/
