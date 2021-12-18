#include <sys/syscall.h>
long syscall(long number, ...);

void _start() {
  long buf = 1024;
  long curr_adr = 0;
  char* p = (char*)syscall(SYS_brk, 0);
  syscall(SYS_brk, p + buf);
  long lenght = syscall(SYS_read, 0, p, buf);
  long new_adr = lenght;
  while (lenght > 0) {
    if (curr_adr + buf - new_adr == 0) {
        curr_adr += buf;
        syscall(SYS_brk, p + curr_adr + buf);
    }
    lenght = syscall(SYS_read, 0, p + new_adr, buf + curr_adr - new_adr);
    if (lenght < 0){
      break;
    }
    new_adr += lenght;
  }
  char eol[1] = { '\n' };
  if (new_adr < 0){
    goto end;
  }
  if (new_adr == 0){
    syscall(SYS_write, 1, eol, 1);
    goto end;
  }
  if (p[new_adr - 1] != '\n') {
    p[new_adr] = '\n';
    new_adr++;
  }
  new_adr -= 2;
  while (new_adr > 0) {
    int lenght = 0;
    while (new_adr > 0 && p[new_adr] != '\n') {
      lenght++;
      new_adr--;
    }
    if (new_adr == 0){
      syscall(SYS_write, 1, p, lenght + 1);
      syscall(SYS_write, 1, eol, 1);
      break;
    }
    syscall(SYS_write, 1, p + new_adr + 1, lenght);
    syscall(SYS_write, 1, eol, 1);
    new_adr--;
  }
end:
  syscall(SYS_brk, p);
  syscall(SYS_exit);
}
