#include "flash_ctrl.h"
#include "utils.h"

void flash_erase_mass(flash_ctrl_num_t flash_ctrl_no)
{

  typedef uintptr_t (*fn_ptr)(void);

  static volatile uint16_t code[] = {
    0x40b2, // MOV  #0xA540, &0x0XX4   ; switch to MB mass erase
    0xa540, FLASH_CTRL + ADDR_FLASH_CTRL_MODE,
    0x43b2, // MOV  #0xFFFF, &addr     ; start mass erase
    0xFFFE,
    // erase_busy:
    0xb392, // BIT  #0x0001, &0x0XX6   ; check busy bit
    FLASH_CTRL + ADDR_FLASH_CTRL_STATUS,
    0x23fd, // JNZ  erase_busy         ; loop while busy
    0x40b2, // MOV  #0xA501, &0x0XX4   ; switch to MB read
    0xa501, FLASH_CTRL + ADDR_FLASH_CTRL_MODE,
    0x3FFF, // JMP $+0                 ; stay in endless loop
    0x4303, // NOP                     ; prevent uninitialized RAM
    0x4303  // NOP                     ; prevent uninitialized RAM
  };

  // TODO  /* allow FLASH MB erase (FLASH control module) */
  // TODO  flash_unprotect_area(flash_ctrl_no, FLASH_MB_ALL);

  /* call code in RAM ... mass erase WILL NOT RETURN !!! */
  ((fn_ptr)code)();
}

int flash_erase_pages(flash_ctrl_num_t flash_ctrl_no, uintptr_t *dptr, int pages, bool info)
{

  typedef uintptr_t (*fn_ptr)(void);

  static volatile uint16_t code[] = {
    0x40b2, // MOV  #0xA510, &0x0XX4   ; switch to MB/IB page erase
    0xa510, FLASH_CTRL + ADDR_FLASH_CTRL_MODE,
    0x43b2, // MOV  #0xFFFF, &addr     ; start page erase
    0x0000, //                         ; code + 0x08
            // erase_busy:
    0xb392, // BIT  #0x0001, &0x0XX6   ; check busy bit
    FLASH_CTRL + ADDR_FLASH_CTRL_STATUS,
    0x23fd, // JNZ  erase_busy         ; loop while busy
    0x40b2, // MOV  #0xA501, &0x0XX4   ; switch to MB read
    0xa501, FLASH_CTRL + ADDR_FLASH_CTRL_MODE,
    0x4130, // RET                     ; return to C program
    0x4303, // NOP                     ; prevent uninitialized RAM
    0x4303  // NOP                     ; prevent uninitialized RAM
  };

  // TODO  uint16_t  prot_config;
  int p;

  /* check destination pointer
     - check if valid
     - check word alignment
     - check if value fits FLASH area
     - check page alignment
  */
  /* Eliminate warning,  21.07.30 by yhd */
  #pragma diag_remark=Pa084
  bool isInsideFlash = false;
  isInsideFlash = isInsideFLASH((uintptr_t)dptr);

  if ((dptr == NULL) || ((uintptr_t)dptr & 0x1) || !isInsideFlash || ((uintptr_t)dptr & (FLASH_PAGE_SIZE - 1)))
  {
    return -1;
  }

  /* check pages
     - check number of pages
  */
  if (pages == 0)
  {
    return -1;
  }

  // TODO  /* allow FLASH MB erase (FLASH control module) */
  // TODO  prot_config = flash_unprotect_area(flash_ctrl_no, (flash_areas)0xFFFF);

  if (info)
  {
    code[0x02 / 2] = 0xa520;
  }

  for (p = 0; p < pages; p++)
  {

    /* fix page start address */
    code[0x08 / 2] = (uintptr_t)dptr;
    /* call code in RAM ... erase one page */
    ((fn_ptr)code)();

    /* increment dest pointer one page */
    dptr = dptr + FLASH_PAGE_SIZE / 2; // dptr is word pointer
  }

  // TODO  /* restore FLASH protection config (FLASH control module) */
  // TODO  flash_protect_area(flash_ctrl_no, (flash_areas)prot_config);

  return pages;
}

int16_t flash_program_rows(flash_ctrl_num_t flash_ctrl_no, uintptr_t *sptr, uintptr_t *dptr, uint16_t words, bool info)
{

  typedef uintptr_t (*fn_ptr)(void);
  uintptr_t *data;

  static volatile uint16_t code[] = {0x1204, // PUSH R4
                                     0x1205, // PUSH R5
                                     0x1206, // PUSH R6
                                     0x40b2, // MOV  #0xA504, &0x0XX4   ; switch to MB/IB prog
                                     0xa504, //                         ; code + 0x08
                                     FLASH_CTRL + ADDR_FLASH_CTRL_MODE,
                                     0x4034, // MOV  #0x40, R4          ; data length
                                     0x0040,

                                     0x4035, // MOV  #data, R5          ; source pointer
                                     0x0000, //                         ; code + 0x12
                                     0x4036, // MOV  #dptr, R6          ; destination pointer
                                     0x0000, //                         ; code + 0x16
                                             // write_loop:
                                     0x9304, // CMP  #0, R4             ; check word counter
                                     0x2408, // JEQ  write_end
                                     0x8314, // DEC  R4                 ; decrement word counter
                                     0x45b6, // MOV  @R5+, 0(R6)        ; write data word to flash
                                     0x0000,
                                     0x5326, // INCD R6                 ; advance destination pointer
                                             // write_busy:
                                     0xb392, // BIT  #0x0001, &0x0XX6   ; check busy bit
                                     FLASH_CTRL + ADDR_FLASH_CTRL_STATUS,
                                     0x23fd, // JNZ  write_busy         ; loop while busy
                                     0x3ff6, // JMP  write_loop
                                             // write_end:
                                     0x40b2, // MOV  #0xA501, &0x0XX4   ; switch to MB read
                                     0xa501, FLASH_CTRL + ADDR_FLASH_CTRL_MODE,
                                     0x4136,                         // POP  R6
                                     0x4135,                         // POP  R5
                                     0x4134,                         // POP  R4
                                     0x4130,                         // RET                     ; return to C program
                                                                     // data:                   ; code + 0x3A
                                     0xffff, 0xffff, 0xffff, 0xffff, // ; space for 64 words to program
                                     0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
                                     0xffff, 0xffff,

                                     0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
                                     0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,

                                     0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
                                     0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,

                                     0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
                                     0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff};

  // TODO  uint16_t  prot_config;
  uint16_t w, n, r;

  /* check source pointer
     - check if valid
     - check word alignment
     - check if value fits RAM area
  */
  if ((sptr == NULL) || ((uintptr_t)sptr & 0x1) || !isInsideRAM((uintptr_t)sptr) ||
      !isInsideRAM((uintptr_t)sptr + words * 2 - 1))
  {
    return -1;
  }
  /* check destination pointer
     - check if valid
     - check word alignment
     - check if value fits FLASH area
  */
  /* Eliminate warning,  21.07.30 by yhd */
  bool isInsideFlash = false;
  isInsideFlash = isInsideFLASH((uintptr_t)dptr);
  bool isInsideFlash2 = false;
  isInsideFlash2 = isInsideFLASH((uintptr_t)dptr + words * 2 - 1);

  if ((dptr == NULL) || ((uintptr_t)dptr & 0x1) || !isInsideFlash || !isInsideFlash2)
  {
    return -1;
  }

  /* check words
     - check number of words
  */
  if (words == 0)
  {
    return -1;
  }

  // TODO  /* allow FLASH MB program (FLASH control module) */
  // TODO  prot_config = flash_unprotect_area(flash_ctrl_no, (flash_areas)0xFFFF);

  if (info)
  {
    code[0x08 / 2] = 0xa508;
  }

  w = 0;
  r = 0;
  while (w < words)
  {

    /* fix source data and destination address */
    data = (uintptr_t *)(code + (0x3A / 2));
    code[0x12 / 2] = (uintptr_t)data;
    code[0x16 / 2] = (uintptr_t)dptr;

    /* copy source data into RAM data area */
    n = 0;
    while ((n < (FLASH_ROW_SIZE / 2)) && (w < words))
    {
      *data++ = *sptr++;
      n++;
      w++;
    }

    /* call code in RAM ... program one row */
    ((fn_ptr)code)();

    /* verify programed FLASH area */
    data = (uintptr_t *)(code + (0x3A / 2));
    n = 0;
    while ((n < (FLASH_ROW_SIZE / 2)) && (r < words))
    {
      if (info)
      {
        if (flash_read_info_word(flash_ctrl_no, (uintptr_t)dptr++) != *data++)
        {
          return (int16_t)r; /* when program verify error */
        }
      }
      else
      {
        if (*dptr++ != *data++)
        {
          // TODO        /* restore FLASH protection config (FLASH control module) */
          // TODO        flash_protect_area(flash_ctrl_no, (flash_areas)prot_config);

          return (int16_t)r; /* when program verify error */
        }
      }
      n++;
      r++;
    }
  }

  // TODO  /* restore FLASH protection config (FLASH control module) */
  // TODO  flash_protect_area(flash_ctrl_no, (flash_areas)prot_config);

  return (int16_t)words;
}

int16_t flash_from_ram(flash_ctrl_num_t flash_ctrl_no, uintptr_t *sptr, uintptr_t *dptr, uint16_t words, bool info)
{

  uint16_t pages;
  int16_t ret;
  uintptr_t dst_base;
  uintptr_t dst_max;

  /* nothing to copy */
  if (words == 0)
  {
    return 0;
  }

  dst_base = (uintptr_t)dptr & ~((uintptr_t)(FLASH_PAGE_SIZE - 1)); /* page aligned dst address */
  dst_max = (uintptr_t)dptr + (words * 2) - 1;                      /* dst data area max address */

  pages = 1 + ((dst_max - dst_base) / FLASH_PAGE_SIZE); /* number of pages to erase to cover dst data area */

  /* erase FLASH pages and verify erased area */
  ret = flash_erase_pages(flash_ctrl_no, (uintptr_t *)dst_base, pages, info);
  if (ret != (int16_t)pages)
  {
    return -1; /* erase failed */
  }

  /* program FLASH rows and verify programmed area */
  ret = flash_program_rows(flash_ctrl_no, sptr, dptr, words, info);
  if (ret < 0)
  {
    return -1;
  }
  return ret;
}

uint16_t flash_read_info_word(flash_ctrl_num_t flash_ctrl_no, uintptr_t addr)
{

  uint16_t data;

  typedef uintptr_t (*fn_ptr)(void);

  static volatile uint16_t code[] = {
    0x1204, // PUSH R4
    0x40b2, // MOV  #0xA540, &0x0XX4   ; switch to IB read mode
    0xa502, FLASH_CTRL + ADDR_FLASH_CTRL_MODE,

    0x4034, // MOV  #addr, R4
    0x0000, // addr                    ; code + 0x0A
    0x44a2, // MOV  @R4, &data
    0x0000, // data                    ; code + 0x0E

    0x40b2, // MOV  #0xA501, &0x0XX4   ; switch to MB read
    0xa501, FLASH_CTRL + ADDR_FLASH_CTRL_MODE,
    0x4134, // POP  R4
    0x4130, // RET                     ; return to C program
    0x4303, // NOP                     ; prevent uninitialized RAM
    0x4303  // NOP                     ; prevent uninitialized RAM
  };

  code[0x0A / 2] = (uint16_t)addr;
  code[0x0E / 2] = (uint16_t)(unsigned int)&data;

  /* call code in RAM */
  ((fn_ptr)code)();

  return data;
}

uint16_t flash_get_page_base_addr(flash_ctrl_num_t flash_ctrl_no, uint16_t page, bool info)
{

  uint16_t base;

  if (info)
  {
    if (page >= FLASH_NUM_INFO_PAGES)
      return 0;
  }
  else
  {
    if (page >= FLASH_NUM_MAIN_PAGES)
      return 0;
  }

  base = info ? 0xFC00 : BASE_ADDR_IMEM;
  return base + (page * FLASH_PAGE_SIZE);
}

uint16_t flash_get_row_base_addr(flash_ctrl_num_t flash_ctrl_no, uint16_t page, uint16_t row_in_page, bool info)
{

  uint16_t addr;

  if (row_in_page >= (FLASH_PAGE_SIZE / FLASH_ROW_SIZE))
    return 0;

  addr = flash_get_page_base_addr(flash_ctrl_no, page, info);
  addr += (row_in_page * FLASH_ROW_SIZE);
  return addr;
}

void flash_protect_main_area(flash_ctrl_num_t flash_ctrl_no, flash_main_area_t areas)
{

  uint16_t prot;

  prot = areas & 0xFF;
  WRITE_REG_16(flash_ctrl_no + ADDR_FLASH_CTRL_AREA_MAIN_L, (0xA500 | prot));
  prot = (areas >> 8) & 0xFF;
  WRITE_REG_16(flash_ctrl_no + ADDR_FLASH_CTRL_AREA_MAIN_H, (0xA500 | prot));
}

void flash_protect_info_area(flash_ctrl_num_t flash_ctrl_no, flash_info_area_t areas)
{

  uint16_t prot;

  prot = areas & 0xFF;
  WRITE_REG_16(flash_ctrl_no + ADDR_FLASH_CTRL_AREA_INFO, (0xA500 | prot));
}

void flash_set_area_lock(flash_ctrl_num_t flash_ctrl_no, flash_main_area_t areas)
{

  uint16_t prot;

  prot = ((areas >> 0) & 0x00FF);
  WRITE_REG_16(flash_ctrl_no + ADDR_FLASH_CTRL_AREA_MAIN_L_LOCK, (0xA500 | prot));

  prot = ((areas >> 8) & 0x00FF);
  WRITE_REG_16(flash_ctrl_no + ADDR_FLASH_CTRL_AREA_MAIN_H_LOCK, (0xA500 | prot));
}

uint16_t flash_get_area_lock(flash_ctrl_num_t flash_ctrl_no)
{

  uint16_t lock = 0;

  lock += (READ_REG_U16(flash_ctrl_no + ADDR_FLASH_CTRL_AREA_MAIN_L_LOCK) & 0x00FF) << 0;
  lock += (READ_REG_U16(flash_ctrl_no + ADDR_FLASH_CTRL_AREA_MAIN_H_LOCK) & 0x00FF) << 8;

  return lock;
}

uint16_t flash_status(flash_ctrl_num_t flash_ctrl_no)
{

  return READ_REG_U16(flash_ctrl_no + ADDR_FLASH_CTRL_STATUS);
}

uint16_t flash_ecc_failure_addr(flash_ctrl_num_t flash_ctrl_no)
{

  return READ_REG_U16(flash_ctrl_no + ADDR_FLASH_CTRL_BIT_ERROR_ADDR);
}

uint16_t get_flash_mode(flash_ctrl_num_t flash_ctrl_no)
{

  return READ_REG_U16(flash_ctrl_no + ADDR_FLASH_CTRL_MODE);
}
