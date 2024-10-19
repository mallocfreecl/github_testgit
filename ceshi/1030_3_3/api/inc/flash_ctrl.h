#ifndef HAVE_FLASH_CTRL_H
#define HAVE_FLASH_CTRL_H

#include "base.h"
#include "core_base.h"

#include "flash_ctrl_bf.h"

#include "vic.h"

typedef enum
{
  FLASH_MB_NO = 0x0000,
  FLASH_MB_ALL = 0xFFFF,
  FLASH_MB_AREA_00 = 0x0001, /* offset : 0x0000 - 0x07FF */
  FLASH_MB_AREA_01 = 0x0002, /* offset : 0x0800 - 0x0FFF */
  FLASH_MB_AREA_02 = 0x0004, /* offset : 0x1000 - 0x17FF */
  FLASH_MB_AREA_03 = 0x0008, /* offset : 0x1800 - 0x1FFF */
  FLASH_MB_AREA_04 = 0x0010, /* offset : 0x2000 - 0x27FF */
  FLASH_MB_AREA_05 = 0x0020, /* offset : 0x2800 - 0x2FFF */
  FLASH_MB_AREA_06 = 0x0040, /* offset : 0x3000 - 0x37FF */
  FLASH_MB_AREA_07 = 0x0080, /* offset : 0x3800 - 0x3FFF */
  FLASH_MB_AREA_08 = 0x0100, /* offset : 0x4000 - 0x47FF */
  FLASH_MB_AREA_09 = 0x0200, /* offset : 0x4800 - 0x4FFF */
  FLASH_MB_AREA_10 = 0x0400, /* offset : 0x5000 - 0x57FF */
  FLASH_MB_AREA_11 = 0x0800, /* offset : 0x5800 - 0x5FFF */
  FLASH_MB_AREA_12 = 0x1000, /* offset : 0x6000 - 0x67FF */
  FLASH_MB_AREA_13 = 0x2000, /* offset : 0x6800 - 0x6FFF */
  FLASH_MB_AREA_14 = 0x4000, /* offset : 0x7000 - 0x77FF */
  FLASH_MB_AREA_15 = 0x8000  /* offset : 0x7800 - 0x7FFF */
} flash_main_area_t;

typedef enum
{
  FLASH_IB_NO = 0x0000,
  FLASH_IB_ALL = 0xFFFF,
  FLASH_IB_AREA_00 = 0x0001, /* offset : 0xFC00 - 0xFDFF */
  FLASH_IB_AREA_01 = 0x0002  /* offset : 0xFE00 - 0xFFFF */
} flash_info_area_t;

typedef enum
{
  FLASH_BUSY = 0x0,
  FLASH_INCOMPLETE = 0x1,
  FLASH_WRITE_ERROR = 0x2
} flash_status_t;

typedef enum
{
  FLASH_MODE_MAIN_READ = 0x01,
  FLASH_MODE_INFO_READ = 0x02,
  FLASH_MODE_MAIN_PROG = 0x04,
  FLASH_MODE_INFO_PROG = 0x08,
  FLASH_MODE_MAIN_PAGE_ER = 0x10,
  FLASH_MODE_INFO_PAGE_ER = 0x20,
  FLASH_MODE_MAIN_MASS_ER = 0x40,
  FLASH_MODE_MAIN_INFO_MASS_ER = 0x80
} flash_mode_t;

#define FLASH_NUM_MAIN_PAGES (64)
#define FLASH_NUM_INFO_PAGES (2)
#define FLASH_ROW_SIZE (0x0080)
#define FLASH_PAGE_SIZE (0x0200)

#define isInsideRAM(addr)                                                                                              \
  (NON_ZERO_TO_ONE(((addr) >= (uintptr_t)BASE_ADDR_DMEM) &&                                                            \
                   ((addr) <= (uintptr_t)(BASE_ADDR_DMEM + INST_SIZE_DMEM - 1))))
#define isInsideFLASH(addr)                                                                                            \
  (NON_ZERO_TO_ONE(((addr) >= (uintptr_t)BASE_ADDR_IMEM) &&                                                            \
                   ((addr) <= (uintptr_t)(BASE_ADDR_IMEM + INST_SIZE_IMEM - 1))))

/* ======================================================================= */
/* MODULE HANDLING                                                         */
/* ======================================================================= */

void flash_erase_mass(flash_ctrl_num_t flash_ctrl_no);

int flash_erase_pages(flash_ctrl_num_t flash_ctrl_no, uintptr_t *dptr, int pages, bool info);

int16_t flash_program_rows(flash_ctrl_num_t flash_ctrl_no, uintptr_t *sptr, uintptr_t *dptr, uint16_t words, bool info);

int16_t flash_from_ram(flash_ctrl_num_t flash_ctrl_no, uintptr_t *sptr, uintptr_t *dptr, uint16_t words, bool info);

uint16_t flash_read_info_word(flash_ctrl_num_t flash_ctrl_no, uintptr_t addr);

uint16_t flash_get_page_base_addr(flash_ctrl_num_t flash_ctrl_no, uint16_t page, bool info);
uint16_t flash_get_row_base_addr(flash_ctrl_num_t flash_ctrl_no, uint16_t page, uint16_t row_in_page, bool info);

void flash_protect_main_area(flash_ctrl_num_t flash_ctrl_no, flash_main_area_t areas);
void flash_protect_info_area(flash_ctrl_num_t flash_ctrl_no, flash_info_area_t areas);

uint16_t flash_status(flash_ctrl_num_t flash_ctrl_no);
uint16_t flash_ecc_failure_addr(flash_ctrl_num_t flash_ctrl_no);
uint16_t get_flash_mode(flash_ctrl_num_t flash_ctrl_no);

void flash_set_area_lock(flash_ctrl_num_t flash_ctrl_no, flash_main_area_t areas);
uint16_t flash_get_area_lock(flash_ctrl_num_t flash_ctrl_no);

#endif /* HAVE_FLASH_CTRL_H */
