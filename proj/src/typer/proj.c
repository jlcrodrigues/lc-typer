#include "proj.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int (proj_main_loop)(int argc, char* argv[]) {
  LoopState loop = CONTINUE;
  vg_init(VIDEO_MODE);
  if (subscribe_interrupts()) return 1;

  vg_draw_rectangle(300, 500, 50, 60, 0x1f3f1f);
  vg_refresh();

  while (loop == CONTINUE) {
    loop = interrupt_handler();
    if (loop == ERROR) return 1;
  }

  int unsub = unsubscribe_interrupts();
  if (vg_exit() || unsub) return 1;

  return 0;
}
