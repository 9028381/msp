#ifndef __FLASH_H_
#define __FLASH_H_

#include "stdint.h"

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

#define BASE_ADDR 0x00008000

uint8_t erase_flash(uint8_t sector);
uint8_t ram2flash(uint8_t sector, uint32_t* buf, uint8_t len);
uint8_t flash2ram(uint8_t sector, uint32_t* buf, uint8_t len);

#endif
