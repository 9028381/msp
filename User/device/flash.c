#include "flash.h"
#include "ti/driverlib/dl_flashctl.h"

volatile uint8_t gErrorType = NO_ERROR;
volatile DL_FLASHCTL_COMMAND_STATUS gCmdStatus;

uint8_t erase_flash(uint8_t sector)
{
    sector--;
    if(sector > 15)
    {
        return 0;
    }
    DL_FlashCTL_unprotectSector(FLASHCTL, (BASE_ADDR + 0x400 * sector), DL_FLASHCTL_REGION_SELECT_MAIN);
    gCmdStatus = DL_FlashCTL_eraseMemoryFromRAM(FLASHCTL, (BASE_ADDR + 0x400 * sector), DL_FLASHCTL_COMMAND_SIZE_SECTOR);
    if (gCmdStatus == DL_FLASHCTL_COMMAND_STATUS_FAILED) {
        gErrorType = ERROR_ERASE;
        return 0;
    }
    return 1;
}

uint8_t ram2flash(uint8_t sector, uint32_t* buf, uint8_t len)
{
    sector--;
    if(sector > 15)
    {
        return 0;
    }
    for(int i = 0; i < len; i++)
    {
        DL_FlashCTL_unprotectSector(FLASHCTL, (BASE_ADDR + 0x400 * sector + i * 8), DL_FLASHCTL_REGION_SELECT_MAIN);
        gCmdStatus = DL_FlashCTL_programMemoryFromRAM64WithECCGenerated(FLASHCTL, (BASE_ADDR + 0x400 * sector + i * 8), (buf + 2*i));
        if (gCmdStatus == DL_FLASHCTL_COMMAND_STATUS_FAILED) {
            gErrorType = ERROR_64BIT_W;
            return 0;
        }
    }
    return 1;
}

uint8_t flash2ram(uint8_t sector, uint32_t* buf, uint8_t len)
{
    sector--;
    if(sector > 15)
    {
        return 0;
    }
    for(int i = 0; i < len; i++)
    {
        DL_FlashCTL_unprotectSector(FLASHCTL, (BASE_ADDR + 0x400 * sector + i * 8), DL_FLASHCTL_REGION_SELECT_MAIN);
        gCmdStatus = DL_FlashCTL_readVerifyFromRAM64WithECCGenerated(FLASHCTL, (BASE_ADDR + 0x400 * sector + i * 8), (buf + 2*i));
        if (gCmdStatus == DL_FLASHCTL_COMMAND_STATUS_PASSED) {
            gErrorType = ERROR_READ_64_BIT;
            return 0;
        }
    }
    return 1;
}

