#ifndef __UTILS_H__
#define __UTILS_H__

#include <common.h>

// ----------- state -----------

enum { NEMU_STOP, NEMU_RUNNING, NEMU_END, NEMU_ABORT, NEMU_QUIT };

typedef struct {
  int state;
  vaddr_t halt_pc;
  uint32_t halt_ret;
} NEMUState;

extern NEMUState nemu_state;

// ----------- statistic -----------

extern uint64_t g_timer;
extern uint64_t g_nr_guest_instr;

uint64_t get_time();
void monitor_statistic();

// ----------- log -----------

#define log_write(...) IFDEF(CONFIG_DEBUG, \
  do { \
    extern FILE* log_fp; \
    extern bool log_enable(); \
    if (log_fp != NULL && log_enable()) { \
      fprintf(log_fp, __VA_ARGS__); \
      fflush(log_fp); \
    } \
  } while (0) \
)

#define _Log(...) \
  do { \
    printf(__VA_ARGS__); \
    log_write(__VA_ARGS__); \
  } while (0)

void strcatf(char *buf, const char *fmt, ...);

// ----------- expr -----------

word_t expr(char *e, bool *success);

#endif