#ifndef __EXT2_STRUCTS_H__ILRD__CR3_
#define __EXT2_STRUCTS_H__ILRD__CR3_

#include <asm/types.h>
#include <sys/stat.h>

#define EXT2_NDIR_BLOCKS (12)
#define EXT2_IND_BLOCK EXT2_NDIR_BLOCKS
#define EXT2_DIND_BLOCK (EXT2_IND_BLOCK + 1)
#define EXT2_TIND_BLOCK (EXT2_DIND_BLOCK + 1)
#define EXT2_N_BLOCKS (EXT2_TIND_BLOCK + 1)
#define EXT2_NAME_LEN (255)
struct ext2_super_block
{
    __u32 s_inodes_count;      /* Inodes count */
    __u32 s_blocks_count;      /* Blocks count */
    __u32 s_r_blocks_count;    /* Reserved blocks count */
    __u32 s_free_blocks_count; /* Free blocks count */
    __u32 s_free_inodes_count; /* Free inodes count */
    __u32 s_first_data_block;  /* First Data Block */
    __u32 s_log_block_size;    /* Block size */
    __s32 s_log_frag_size;     /* Fragment size */
    __u32 s_blocks_per_group;  /* # Blocks per group */
    __u32 s_frags_per_group;   /* # Fragments per group */
    __u32 s_inodes_per_group;  /* # Inodes per group */
    __u32 s_mtime;             /* Mount time */
    __u32 s_wtime;             /* Write time */
    __u16 s_mnt_count;
    __s16 s_max_mnt_count;
    __u16 s_magic;
    __u16 s_state;
    __u16 s_errors;
    __u16 s_minor_rev_level;
    __u32 s_lastcheck;
    __u32 s_checkinterval;
    __u32 s_creator_os;
    __u32 s_rev_level;
    __u16 s_def_resuid;
    __u16 s_def_resgid;
    __u32 s_first_ino;
    __u16 s_inode_size;
    __u16 s_block_group_nr;
    __u32 s_feature_compat;
    __u32 s_feature_incompat;
    __u32 s_feature_ro_compat;
    __u8 s_uuid[16];
    char s_volume_name[16];
    char s_last_mounted[64];
    __u32 s_algorithm_usage_bitmap;
    __u8 s_prealloc_blocks;
    __u8 s_prealloc_dir_blocks;
    __u16 s_padding1;
    __u32 s_reserved[204];
};

struct ext2_group_desc
{
    __u32 bg_block_bitmap;      /* Blocks bitmap block */
    __u32 bg_inode_bitmap;      /* Inodes bitmap block */
    __u32 bg_inode_table;       /* Inodes table block */
    __u16 bg_free_blocks_count; /* Free blocks count */
    __u16 bg_free_inodes_count; /* Free inodes count */
    __u16 bg_used_dirs_count;   /* Directories count */
    __u16 bg_pad;
    __u32 bg_reserved[3];
};

struct ext2_inode
{
    __u16 i_mode;        /* File mode */
    __u16 i_uid;         /* Low 16 bits of Owner Uid */
    __u32 i_size;        /* Size in bytes */
    __u32 i_atime;       /* Access time */
    __u32 i_ctime;       /* Creation time */
    __u32 i_mtime;       /* Modification time */
    __u32 i_dtime;       /* Deletion Time */
    __u16 i_gid;         /* Low 16 bits of Group Id */
    __u16 i_links_count; /* Links count */
    __u32 i_blocks;      /* Blocks count */
    __u32 i_flags;       /* File flags */
    union
    {
        struct
        {
            __u32 l_i_reserved1;
        } linux1;
        struct
        {
            __u32 h_i_translator;
        } hurd1;
        struct
        {
            __u32 m_i_reserved1;
        } masix1;
    } osd1;                       /* OS dependent 1 */
    __u32 i_block[EXT2_N_BLOCKS]; /* Pointers to blocks */
    __u32 i_generation;           /* File version (for NFS) */
    __u32 i_file_acl;             /* File ACL */
    __u32 i_dir_acl;              /* Directory ACL */
    __u32 i_faddr;                /* Fragment address */
    union
    {
        struct
        {
            __u8 l_i_frag;  /* Fragment number */
            __u8 l_i_fsize; /* Fragment size */
            __u16 i_pad1;
            __u16 l_i_uid_high; /* these 2 fields    */
            __u16 l_i_gid_high; /* were reserved2[0] */
            __u32 l_i_reserved2;
        } linux2;
        struct
        {
            __u8 h_i_frag;  /* Fragment number */
            __u8 h_i_fsize; /* Fragment size */
            __u16 h_i_mode_high;
            __u16 h_i_uid_high;
            __u16 h_i_gid_high;
            __u32 h_i_author;
        } hurd2;
        struct
        {
            __u8 m_i_frag;  /* Fragment number */
            __u8 m_i_fsize; /* Fragment size */
            __u16 m_pad1;
            __u32 m_i_reserved2[2];
        } masix2;
    } osd2; /* OS dependent 2 */
};

struct ext2_dir_entry_2
{
    __u32 inode;   /* Inode number */
    __u16 rec_len; /* Directory entry length */
    __u8 name_len; /* Name length */
    __u8 file_type;
    char name[EXT2_NAME_LEN]; /* File name */
};

#endif /* __EXT2_STRUCTS_H__ILRD__CR3_ */