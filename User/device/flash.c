#include "flash.h"
#include "User/config.h"
#include "User/utils/log.h"
#include "ti/driverlib/dl_flashctl.h"
#include <string.h>

#define NO_ERROR 0
#define ERROR_ERASE 1
#define ERROR_8BIT_W 2
#define ERROR_16BIT_W 3
#define ERROR_32BIT_W 4
#define ERROR_64BIT_W 5

#define ERROR_ERASE 1
#define ERROR_WRITE_8_BIT 2
#define ERROR_READ_8_BIT 3
#define ERROR_WRITE_16_BIT 4
#define ERROR_READ_16_BIT 5
#define ERROR_WRITE_32_BIT 6
#define ERROR_READ_32_BIT 7
#define ERROR_WRITE_64_BIT 8
#define ERROR_READ_64_BIT 9
#define ERROR_EXPECTED_FAIL 10
#define ERROR_UNEXPECTED 11
#define ERROR_WRITE_64_OVERRIDE 12
#define ERROR_READ_64_OVERRIDE 13
#define ERROR_EXPECTED_FAIL_OVERRIDE 14

void flash_erase(unsigned sector) {
  if (sector >= PAGE_NUM) {
    THROW_WARN("FLASH_ERROR: erase sector %u out of range [0, 15].", sector);
    return;
  }

  DL_FLASHCTL_COMMAND_STATUS cmd_status;
  uint32_t base = BASE_ADDR + PAGE_SIZE * sector;

  cmd_status = DL_FlashCTL_blankVerifyFromRAM(FLASHCTL, base);
  if (cmd_status == DL_FLASHCTL_COMMAND_STATUS_PASSED)
    return;

  DL_FlashCTL_unprotectSector(FLASHCTL, base, DL_FLASHCTL_REGION_SELECT_MAIN);

  cmd_status = DL_FlashCTL_eraseMemoryFromRAM(FLASHCTL, base,
                                              DL_FLASHCTL_COMMAND_SIZE_SECTOR);

  if (cmd_status == DL_FLASHCTL_COMMAND_STATUS_FAILED)
    THROW_WARN("FLASH_ERROR: sector %u erase failed.", sector);
}

void flash_write_u64(unsigned sector, unsigned index, uint32_t DA,
                     uint32_t TA) {
  if (sector >= PAGE_NUM) {
    THROW_WARN("FLASH_ERROR: write u64 sector %u out of range [0, 15].",
               sector);
    return;
  }

  if (index >= PAGE_SIZE / 8) {
    THROW_WARN("FLASH_ERROR: write u64 index %u out of range [0, %u].", index)
    return;
  }

  uint32_t buf[2] = {[0] = DA, [1] = TA};
  uint32_t base = BASE_ADDR + PAGE_SIZE * sector;
  DL_FLASHCTL_COMMAND_STATUS cmd_status;

  DL_FlashCTL_unprotectSector(FLASHCTL, base + index,
                              DL_FLASHCTL_REGION_SELECT_MAIN);

  cmd_status = DL_FlashCTL_programMemoryFromRAM64WithECCGenerated(
      FLASHCTL, base + index, buf);

  if (cmd_status == DL_FLASHCTL_COMMAND_STATUS_FAILED)
    THROW_WARN("FLASH_ERROR: sector %u word %u write failed.", sector, index);
}

void flash_write_to(unsigned sector, unsigned position, const void *src,
                    unsigned len) {
                        INFO("sector %u position %u src %x len %u", sector, position, src, len);
  if (sector >= PAGE_NUM) {
    THROW_WARN("FLASH_ERROR: write sector %u out of range [0, 15].", sector);
    return;
  }

  if (src == NULL) {
    THROW_WARN("FLASH_ERROR: write src is NULL.");
    return;
  }

  if (position + len > PAGE_SIZE) {
    THROW_WARN("FLASH_ERROR: write len > PAGE_SIZE.");
    return;
  }

  DL_FLASHCTL_COMMAND_STATUS cmd_status;
  uint32_t base = BASE_ADDR + PAGE_SIZE * sector + position;

  unsigned int ragged = len % 8;
  if (ragged != 0) {
    uint32_t skew = len / 8;
    uint32_t buf[2] = {0};
    memcpy(buf, src + len - ragged, ragged);

    DL_FlashCTL_unprotectSector(FLASHCTL, base + skew,
                                DL_FLASHCTL_REGION_SELECT_MAIN);

    cmd_status = DL_FlashCTL_programMemoryFromRAM64WithECCGenerated(
        FLASHCTL, base + skew, buf);

    if (cmd_status == DL_FLASHCTL_COMMAND_STATUS_FAILED) {
      THROW_WARN("FLASH_ERROR: sector %u write failed.", sector);
      return;
    }

    len -= ragged;
  }

  for (unsigned int i = 0; i < len; i += 8) {
    DL_FlashCTL_unprotectSector(FLASHCTL, base + i,
                                DL_FLASHCTL_REGION_SELECT_MAIN);

    cmd_status = DL_FlashCTL_programMemoryFromRAM64WithECCGenerated(
        FLASHCTL, base + i, src + i);

    if (cmd_status == DL_FLASHCTL_COMMAND_STATUS_FAILED) {
      THROW_WARN("FLASH_ERROR: sector %u write failed.", sector);
      return;
    }
  }
}

void flash_write(unsigned sector, const void *src, unsigned len) {
  flash_write_to(sector, 0, src, len);
}

void flash_read(unsigned sector, void *dest, unsigned len) {
  if (sector >= PAGE_NUM) {
    THROW_WARN("FLASH_ERROR: read sector %u out of range [0, 15].", sector);
    return;
  }

  if (dest == NULL) {
    THROW_WARN("FLASH_ERROR: read dest is NULL.");
    return;
  }

  if (len > PAGE_SIZE) {
    THROW_WARN("FLASH_ERROR: read len > PAGE_SIZE.");
    return;
  }

  uint32_t base = BASE_ADDR + PAGE_SIZE * sector;
  memcpy(dest, (void *)base, len);
}

const void *flash_use(unsigned sector) {
  if (sector >= PAGE_NUM) {
    THROW_WARN("FLASH_ERROR: read sector %u out of range [0, 15].", sector);
    return NULL;
  }

  uint32_t base = BASE_ADDR + PAGE_SIZE * sector;
  return (void *)base;
}
