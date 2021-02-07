#ifndef __USER_H__
#define __USER_H__

#include <memory/vaddr.h>
#include <sys/mman.h>

typedef struct {
  word_t entry;
  word_t brk;
  word_t brk_page;
  word_t program_brk;
  word_t phdr;
  int phent;
  int phnum;
  int std_fd[3];
} user_state_t;

extern user_state_t user_state;

void *user_mmap(void *addr, size_t length, int prot,
    int flags, int fd, off_t offset);
int user_munmap(void *addr, size_t length);

static inline void* user_to_host(word_t uaddr) {
  return (void *)(uintptr_t)uaddr;
}

static inline word_t host_to_user(void *haddr) {
  return (word_t)(uintptr_t)haddr;
}

#endif