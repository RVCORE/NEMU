#include <cpu/decode.h>
#include "../local-include/rtl.h"

#ifdef CONFIG_DEBUG
#define AMO_INSTR_BINARY(f) \
  f(lr_w) f(lr_d)
#define AMO_INSTR_TERNARY(f) \
  f(sc_w) f(sc_d) \
  f(amoadd_w) f(amoswap_w) f(amoxor_w) f(amoor_w) f(amoand_w) \
  f(amomin_w) f(amomax_w) f(amominu_w) f(amomaxu_w) \
  f(amoadd_d) f(amoswap_d) f(amoxor_d) f(amoor_d) f(amoand_d) \
  f(amomin_d) f(amomax_d) f(amominu_d) f(amomaxu_d)
#define SYS_INSTR_NULLARY(f) \
  f(ecall) f(mret) f(sret) f(sfence_vma) f(wfi)
#define SYS_INSTR_TERNARY(f) \
  f(csrrw) f(csrrs) f(csrrc) f(csrrwi) f(csrrsi) f(csrrci)
#else
#define AMO_INSTR_BINARY(f)
#define AMO_INSTR_TERNARY(f) f(atomic)
#define SYS_INSTR_NULLARY(f)
#define SYS_INSTR_TERNARY(f) f(system)
#endif

#define FLOAT_INSTR_TERNARY(f) \
  f(fadds) f(fsubs) f(fmuls) f(fdivs) f(faddd) f(fsubd) f(fmuld) f(fdivd)

#define INSTR_NULLARY(f) \
  f(inv) f(rt_inv) f(nemu_trap) \
  f(fence_i) f(fence) \
  SYS_INSTR_NULLARY(f) \
  f(p_ret)

#define INSTR_UNARY(f) \
  f(p_li_0) f(p_li_1)

#define INSTR_BINARY(f) \
  f(lui) f(auipc) f(jal) \
  f(ld) f(lw) f(lh) f(lb) f(lwu) f(lhu) f(lbu) f(sd) f(sw) f(sh) f(sb) \
  f(c_j) f(p_jal) f(c_jr) f(c_jalr) \
  f(c_beqz) f(c_bnez) f(c_mv) f(p_sext_w) \
  AMO_INSTR_BINARY(f) \
  f(ld_mmu) f(lw_mmu) f(lh_mmu) f(lb_mmu) f(lwu_mmu) f(lhu_mmu) f(lbu_mmu) \
  f(sd_mmu) f(sw_mmu) f(sh_mmu) f(sb_mmu) \
  f(flw) f(fsw) f(fsqrts) f(fles) f(flts) f(feqs) \
  f(fcvt_s_w) f(fcvt_s_wu) f(fcvt_s_l) f(fcvt_s_lu) \
  f(fcvt_w_s) f(fcvt_wu_s) f(fcvt_l_s) f(fcvt_lu_s) \
  f(fmv_x_w) f(fmv_w_x) \
  f(fld) f(fsd) f(fsqrtd) f(fled) f(fltd) f(feqd) \
  f(fcvt_d_w) f(fcvt_d_wu) f(fcvt_d_l) f(fcvt_d_lu) \
  f(fcvt_w_d) f(fcvt_wu_d) f(fcvt_l_d) f(fcvt_lu_d) \
  f(fsgnjd) f(fsgnjxd) \
  f(fmv_x_d) f(fmv_d_x) \
  f(fcvt_d_s) f(fcvt_s_d)

#define INSTR_TERNARY(f) \
  f(add) f(sll) f(srl) f(slt) f(sltu) f(xor) f(or) f(sub) f(sra) f(and) \
  f(addi) f(slli) f(srli) f(slti) f(sltui) f(xori) f(ori) f(srai) f(andi) \
  f(addw) f(sllw) f(srlw) f(subw) f(sraw) \
  f(addiw) f(slliw) f(srliw) f(sraiw) \
  f(jalr) f(beq) f(bne) f(blt) f(bge) f(bltu) f(bgeu) \
  f(mul) f(mulh) f(mulhu) f(mulhsu) f(div) f(divu) f(rem) f(remu) \
  f(mulw) f(divw) f(divuw) f(remw) f(remuw) \
  f(c_li) f(c_addi) f(c_slli) f(c_srli) f(c_srai) f(c_andi) f(c_addiw) \
  f(c_add) f(c_and) f(c_or) f(c_xor) f(c_sub) f(c_addw) f(c_subw) \
  f(p_blez) f(p_bgez) f(p_bltz) f(p_bgtz) \
  f(p_inc) f(p_dec) \
  AMO_INSTR_TERNARY(f) \
  SYS_INSTR_TERNARY(f) \
  FLOAT_INSTR_TERNARY(f)

def_all_EXEC_ID();