/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus - memory.h                                                *
 *   Mupen64Plus homepage: http://code.google.com/p/mupen64plus/           *
 *   Copyright (C) 2002 Hacktarux                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include "osal/preproc.h"

#define AI_STATUS_FIFO_FULL	0x80000000		/* Bit 31: full */
#define AI_STATUS_DMA_BUSY	   0x40000000		/* Bit 30: busy */
#define MI_INTR_AI			   0x04			   /* Bit 2: AI intr */

extern uint32_t VI_REFRESH;

#define read_word_in_memory() readmem[address>>16]()
#define read_byte_in_memory() readmemb[address>>16]()
#define read_hword_in_memory() readmemh[address>>16]()
#define read_dword_in_memory() readmemd[address>>16]()
#define write_word_in_memory() writemem[address>>16]()
#define write_byte_in_memory() writememb[address >>16]()
#define write_hword_in_memory() writememh[address >>16]()
#define write_dword_in_memory() writememd[address >>16]()

enum { SP_MEM_SIZE = 0x2000 };

extern uint32_t g_sp_mem[SP_MEM_SIZE/4];

extern uint32_t PIF_RAM[0x40/4];
extern uint8_t *PIF_RAMb;

typedef struct _save_memory_data
{
    uint8_t eeprom[0x200];
    uint8_t mempack[4][0x8000];
    uint8_t sram[0x8000];
    uint8_t flashram[0x20000];

    /* Some games use 16Kbit (2048 bytes) eeprom saves, the initial
     * libretro-mupen64plus save file implementation failed to account
     * for these. The missing bytes are stored here to avoid breaking
     * saves of games unaffected by the issue. */
    uint8_t eeprom2[0x600];
} save_memory_data;
extern save_memory_data saved_memory;
void format_saved_memory(void);

enum { RDRAM_MAX_SIZE = 0x800000 };

extern ALIGN(16, uint32_t g_rdram[RDRAM_MAX_SIZE/4]);

enum rdram_registers
{
   RDRAM_CONFIG_REG,
   RDRAM_DEVICE_ID_REG,
   RDRAM_DELAY_REG,
   RDRAM_MODE_REG,
   RDRAM_REF_INTERVAL_REG,
   RDRAM_REF_ROW_REG,
   RDRAM_RAS_INTERVAL_REG,
   RDRAM_MIN_INTERVAL_REG,
   RDRAM_ADDR_SELECT_REG,
   RDRAM_DEVICE_MANUF_REG,
   RDRAM_REGS_COUNT
};

extern uint32_t g_rdram_regs[RDRAM_REGS_COUNT];

extern uint32_t address, word;
extern uint8_t cpu_byte;
extern uint16_t hword;
extern uint64_t dword, *rdword;

extern void (*readmem[0x10000])(void);
extern void (*readmemb[0x10000])(void);
extern void (*readmemh[0x10000])(void);
extern void (*readmemd[0x10000])(void);
extern void (*writemem[0x10000])(void);
extern void (*writememb[0x10000])(void);
extern void (*writememh[0x10000])(void);
extern void (*writememd[0x10000])(void);

enum sp_registers
{
   SP_MEM_ADDR_REG,
   SP_DRAM_ADDR_REG,
   SP_RD_LEN_REG,
   SP_WR_LEN_REG,
   SP_STATUS_REG,
   SP_DMA_FULL_REG,
   SP_DMA_BUSY_REG,
   SP_SEMAPHORE_REG,
   SP_REGS_COUNT
};

extern uint32_t g_sp_regs[SP_REGS_COUNT];

extern uint32_t *readrsp[0x10000];
extern uint32_t *readmi[0x10000];
extern uint32_t *readvi[0x10000];
extern uint32_t *readai[0x10000];
extern uint32_t *readpi[0x10000];
extern uint32_t *readri[0x10000];
extern uint32_t *readsi[0x10000];
extern uint32_t *readdp[0x10000];
extern uint32_t *readdps[0x10000];

typedef struct _RSP_register
{
   uint32_t rsp_pc;
   uint32_t rsp_ibist;
} RSP_register;

typedef struct _DPC_register
{
   uint32_t dpc_start;
   uint32_t dpc_end;
   uint32_t dpc_current;
   uint32_t w_dpc_status;
   uint32_t dpc_status;
   uint32_t dpc_clock;
   uint32_t dpc_bufbusy;
   uint32_t dpc_pipebusy;
   uint32_t dpc_tmem;
} DPC_register;

typedef struct _DPS_register
{
   uint32_t dps_tbist;
   uint32_t dps_test_mode;
   uint32_t dps_buftest_addr;
   uint32_t dps_buftest_data;
} DPS_register;

typedef struct _mips_register
{
   uint32_t w_mi_init_mode_reg;
   uint32_t mi_init_mode_reg;
   uint32_t mi_version_reg;
   uint32_t mi_intr_reg;
   uint32_t mi_intr_mask_reg;
   uint32_t w_mi_intr_mask_reg;
} mips_register;

typedef struct _VI_register
{
   uint32_t vi_status;
   uint32_t vi_origin;
   uint32_t vi_width;
   uint32_t vi_v_intr;
   uint32_t vi_current;
   uint32_t vi_burst;
   uint32_t vi_v_sync;
   uint32_t vi_h_sync;
   uint32_t vi_leap;
   uint32_t vi_h_start;
   uint32_t vi_v_start;
   uint32_t vi_v_burst;
   uint32_t vi_x_scale;
   uint32_t vi_y_scale;
   uint32_t vi_delay;
} VI_register;

typedef struct _AI_register
{
   uint32_t ai_dram_addr;
   uint32_t ai_len;
   uint32_t ai_control;
   uint32_t ai_status;
   uint32_t ai_dacrate;
   uint32_t ai_bitrate;
   uint32_t next_delay;
   uint32_t next_len;
   uint32_t current_delay;
   uint32_t current_len;
} AI_register;

typedef struct _PI_register
{
   uint32_t pi_dram_addr_reg;
   uint32_t pi_cart_addr_reg;
   uint32_t pi_rd_len_reg;
   uint32_t pi_wr_len_reg;
   uint32_t read_pi_status_reg;
   uint32_t pi_bsd_dom1_lat_reg;
   uint32_t pi_bsd_dom1_pwd_reg;
   uint32_t pi_bsd_dom1_pgs_reg;
   uint32_t pi_bsd_dom1_rls_reg;
   uint32_t pi_bsd_dom2_lat_reg;
   uint32_t pi_bsd_dom2_pwd_reg;
   uint32_t pi_bsd_dom2_pgs_reg;
   uint32_t pi_bsd_dom2_rls_reg;
} PI_register;

typedef struct _RI_register
{
   uint32_t ri_mode;
   uint32_t ri_config;
   uint32_t ri_current_load;
   uint32_t ri_select;
   uint32_t ri_refresh;
   uint32_t ri_latency;
   uint32_t ri_error;
   uint32_t ri_werror;
} RI_register;

typedef struct _SI_register
{
   uint32_t si_dram_addr;
   uint32_t si_pif_addr_rd64b;
   uint32_t si_pif_addr_wr64b;
   uint32_t si_stat;
} SI_register;

extern PI_register pi_register;
extern mips_register MI_register;
extern SI_register si_register;
extern VI_register vi_register;
extern RSP_register rsp_register;
extern RI_register ri_register;
extern AI_register ai_register;
extern DPC_register dpc_register;
extern DPS_register dps_register;

enum cic_type
{
   CIC_X101,
   CIC_X102,
   CIC_X103,
   CIC_X105,
   CIC_X106
};

extern enum cic_type g_cic_type;


#ifndef M64P_BIG_ENDIAN
#if defined(__GNUC__) && (__GNUC__ > 4  || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2))
#define sl(x) __builtin_bswap32(x)
#else
#define sl(mot) \
( \
((mot & 0x000000FF) << 24) | \
((mot & 0x0000FF00) <<  8) | \
((mot & 0x00FF0000) >>  8) | \
((mot & 0xFF000000) >> 24) \
)
#endif

#define S8 3
#define S16 2
#define Sh16 1

#else

#define sl(mot) mot
#define S8 0
#define S16 0
#define Sh16 0

#endif

int init_memory(void);

void read_nothing(void);
void read_nothingh(void);
void read_nothingb(void);
void read_nothingd(void);
void read_nomem(void);
void read_nomemb(void);
void read_nomemh(void);
void read_nomemd(void);
void read_rdram(void);
void read_rdramb(void);
void read_rdramh(void);
void read_rdramd(void);
void read_rdramFB(void);
void read_rdramFBb(void);
void read_rdramFBh(void);
void read_rdramFBd(void);
void read_rdramreg(void);
void read_rdramregb(void);
void read_rdramregh(void);
void read_rdramregd(void);
void read_rsp_mem(void);
void read_rsp_memb(void);
void read_rsp_memh(void);
void read_rsp_memd(void);
void read_rsp_reg(void);
void read_rsp_regb(void);
void read_rsp_regh(void);
void read_rsp_regd(void);
void read_rsp(void);
void read_rspb(void);
void read_rsph(void);
void read_rspd(void);
void read_dp(void);
void read_dpb(void);
void read_dph(void);
void read_dpd(void);
void read_dps(void);
void read_dpsb(void);
void read_dpsh(void);
void read_dpsd(void);
void read_mi(void);
void read_mib(void);
void read_mih(void);
void read_mid(void);
void read_vi(void);
void read_vib(void);
void read_vih(void);
void read_vid(void);
void read_ai(void);
void read_aib(void);
void read_aih(void);
void read_aid(void);
void read_pi(void);
void read_pib(void);
void read_pih(void);
void read_pid(void);
void read_ri(void);
void read_rib(void);
void read_rih(void);
void read_rid(void);
void read_si(void);
void read_sib(void);
void read_sih(void);
void read_sid(void);
void read_flashram_status(void);
void read_flashram_statusb(void);
void read_flashram_statush(void);
void read_flashram_statusd(void);
void read_rom(void);
void read_romb(void);
void read_romh(void);
void read_romd(void);
void read_pif(void);
void read_pifb(void);
void read_pifh(void);
void read_pifd(void);

void write_nothing(void);
void write_nothingb(void);
void write_nothingh(void);
void write_nothingd(void);
void write_nomem(void);
void write_nomemb(void);
void write_nomemd(void);
void write_nomemh(void);
void write_rdram(void);
void write_rdramb(void);
void write_rdramh(void);
void write_rdramd(void);
void write_rdramFB(void);
void write_rdramFBb(void);
void write_rdramFBh(void);
void write_rdramFBd(void);
void write_rdramreg(void);
void write_rdramregb(void);
void write_rdramregh(void);
void write_rdramregd(void);
void write_rsp_mem(void);
void write_rsp_memb(void);
void write_rsp_memh(void);
void write_rsp_memd(void);
void write_rsp_reg(void);
void write_rsp_regb(void);
void write_rsp_regh(void);
void write_rsp_regd(void);
void write_rsp(void);
void write_rspb(void);
void write_rsph(void);
void write_rspd(void);
void write_dp(void);
void write_dpb(void);
void write_dph(void);
void write_dpd(void);
void write_dps(void);
void write_dpsb(void);
void write_dpsh(void);
void write_dpsd(void);
void write_mi(void);
void write_mib(void);
void write_mih(void);
void write_mid(void);
void write_vi(void);
void write_vib(void);
void write_vih(void);
void write_vid(void);
void write_ai(void);
void write_aib(void);
void write_aih(void);
void write_aid(void);
void write_pi(void);
void write_pib(void);
void write_pih(void);
void write_pid(void);
void write_ri(void);
void write_rib(void);
void write_rih(void);
void write_rid(void);
void write_si(void);
void write_sib(void);
void write_sih(void);
void write_sid(void);
void write_flashram_dummy(void);
void write_flashram_dummyb(void);
void write_flashram_dummyh(void);
void write_flashram_dummyd(void);
void write_flashram_command(void);
void write_flashram_commandb(void);
void write_flashram_commandh(void);
void write_flashram_commandd(void);
void write_rom(void);
void write_pif(void);
void write_pifb(void);
void write_pifh(void);
void write_pifd(void);

void make_w_dpc_status(void);
void make_w_mi_init_mode_reg(void);
void update_MI_intr_mode_reg(void);
void update_MI_init_mask_reg(void);
void make_w_mi_intr_mask_reg(void);
void update_ai_dacrate(uint32_t word);
void update_vi_status(uint32_t word);
void update_vi_width(uint32_t word);

/* Returns a pointer to a block of contiguous memory
 * Can access RDRAM, SP_DMEM, SP_IMEM and ROM, using TLB if necessary
 * Useful for getting fast access to a zone with executable code. */
uint32_t *fast_mem_access(uint32_t address);

#endif

