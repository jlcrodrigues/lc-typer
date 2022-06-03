#include "proj.h"

static State state = MENU;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  //lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

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

  mouse_sprite mouse;
  mouse_sprite_create(&mouse);


  while (loop == CONTINUE || loop == EVENT) {
    loop = interrupt_handler();

    if (loop == ERROR) return 1;
    if (loop != EVENT) continue;

    Event event = get_event();

    mouse_sprite_step(&mouse, event);
    if (event.type == KEYBOARD) {
      if (event.info.keyboard.character == 'q') break;
    }

    switch (state) {
      case MENU:
        //handle event with menu function
        break;
      case GAME:
        //handle event with game function
        break;
      default:
        return 1;
    }

    if (event.type == TIMER) {
        vg_refresh(); //TODO make refresh dependant of timer
    }
  }

  int exit = unsubscribe_interrupts();
  if (vg_exit() || exit) return 1;

  return 0;
}
