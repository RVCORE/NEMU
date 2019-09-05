#include "cpu/exec.h"

make_EHelper(ld) {
  rtl_lm(&s0, &id_src->addr, decinfo.width);

#ifdef ISA64
  if (decinfo.width == 4) {  // for lw
    rtl_li(&s1, 32);
    rtl_shl(&s0, &s0, &s1);
    rtl_sar64(&s0, &s0, &s1);
  }
#endif

  rtl_sr(id_dest->reg, &s0, 4);

  switch (decinfo.width) {
    case 8: print_asm_template2(ld); break;
    case 4: print_asm_template2(lw); break;
    case 2: print_asm_template2(lhu); break;
    case 1: print_asm_template2(lbu); break;
    default: assert(0);
  }
}

// load sign value
make_EHelper(lds) {
  rtl_lm(&s0, &id_src->addr, decinfo.width);
  rtl_sext(&s0, &s0, decinfo.width);
  rtl_sr(id_dest->reg, &s0, 4);

  switch (decinfo.width) {
    case 2: print_asm_template2(lh); break;
    case 1: print_asm_template2(lb); break;
    default: assert(0);
  }
}

make_EHelper(st) {
  rtl_sm(&id_src->addr, &id_dest->val, decinfo.width);

  switch (decinfo.width) {
    case 8: print_asm_template2(sd); break;
    case 4: print_asm_template2(sw); break;
    case 2: print_asm_template2(sh); break;
    case 1: print_asm_template2(sb); break;
    default: assert(0);
  }
}
