################################################################################
################################################################################
##
## Makefile -- makefile for 8407
##
## Mandatory settings:
##
## o TOPDIR      = the toplevel directory (using slashes as path separator)
## o TARGET      = the machine qualifier to generate code for
##
################################################################################
################################################################################

TOPDIR = ../..
SUBDIR = applications/8407

include $(TOPDIR)/env/make/Makefile.config

################################################################################
# source files
################################################################################

SOURCES += startup_stm32f10x_hd.s
SOURCES += main.c

SOURCES += misc.c
SOURCES += system_stm32f10x.c
SOURCES += stm32f10x_fsmc.c
SOURCES += stm32f10x_gpio.c
SOURCES += stm32f10x_pwr.c
SOURCES += stm32f10x_rcc.c
SOURCES += stm32f10x_usart.c

################################################################################
# define define user cc flags
################################################################################



################################################################################
# define define user ld flags
################################################################################



################################################################################
# define library used
################################################################################

#LIBRARIES  = adi image

################################################################################
# define target name
################################################################################

PROGRAM = 8407

################################################################################
# define user targets
################################################################################

default: install

clean: clean-objects clean-program

build:  build-objects build-program build-elfdump-program build-intelhex-program

install: build install-program install-intelhex-program

headers:

all: clean build install


include $(TOPDIR)/env/make/Makefile.rules


