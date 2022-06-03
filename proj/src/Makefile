# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}/drivers/driver
.PATH: ${.CURDIR}/drivers/kbc
.PATH: ${.CURDIR}/drivers/timer
.PATH: ${.CURDIR}/drivers/utils
.PATH: ${.CURDIR}/drivers/video

.PATH: ${.CURDIR}/typer

# source code files to be compiled
DRIVERS = driver.c keyboard.c mouse.c timer.c utils.c video_gr.c sprite.c
TYPER = proj.c game.c mouse_sprite.c
SRCS = $(DRIVERS) $(TYPER)

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
INCLUDE_FLAGS = -I./drivers -I./drivers/driver -I./drivers/kbc -I./drivers/timer -I./drivers/utils -I./drivers/video -I./typer
ASSETS = -I./assets -I./assets/xpm
CFLAGS += -pedantic
CPPFLAGS += -pedantic $(INCLUDE_FLAGS) $(ASSETS) -D __LCOM_OPTIMIZED__ 

# list of library dependencies (only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
