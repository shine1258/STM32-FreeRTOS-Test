#include "lfs_port.h"
#include "spif.h"

extern SPIF_HandleTypeDef spif;
lfs_t lfs;

int read(const struct lfs_config* c, lfs_block_t block, lfs_off_t off, void* buffer, lfs_size_t size);
int prog(const struct lfs_config* c, lfs_block_t block, lfs_off_t off, const void* buffer, lfs_size_t size);
int erase(const struct lfs_config* c, lfs_block_t block);
int sync(const struct lfs_config* c);

// configuration of the filesystem is provided by this struct
const struct lfs_config cfg
    = {
          // block device operations
          .read = read,
          .prog = prog,
          .erase = erase,
          .sync = sync,

          // block device configuration
          .read_size = 16,
          .prog_size = 16,
          .block_size = 4096,
          .block_count = 128,
          .cache_size = 16,
          .lookahead_size = 16,
          .block_cycles = 500,
      };

int read(const struct lfs_config* c, lfs_block_t block, lfs_off_t off, void* buffer, lfs_size_t size)
{
    return !SPIF_ReadBlock(&spif, block, (uint8_t*)buffer, size, off);
}

int prog(const struct lfs_config* c, lfs_block_t block, lfs_off_t off, const void* buffer, lfs_size_t size)
{
    return !SPIF_WriteBlock(&spif, block, (uint8_t*)buffer, size, off);
}

int erase(const struct lfs_config* c, lfs_block_t block)
{
    return !SPIF_EraseBlock(&spif, block);
}

int sync(const struct lfs_config* c)
{
    return 0;
}