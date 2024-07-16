#ifndef __FLASH_H__
#define __FLASH_H__

void flash_erase(unsigned sector);
void flash_write(unsigned sector, const void *src, unsigned len);
void flash_read(unsigned sector, void *dest, unsigned len);

#endif // !__FLASH_H__
