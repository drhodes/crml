# Copyright 2010, The Native Client SDK Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can
# be found in the LICENSE file.

# Makefile for the Life example.

NACLPORTS_ROOT = /home/derek/dev/naclports/src
NACL_SDK_ROOT = ~/dev/nacl_sdk

CCFILES =	main.cc \
			event_handler.cc \
			gles2_demo_cc.cc \
			main.cc \
			md5.cc \
			plugin_object.cc \
			test_object.cc

OBJECTS_X86_32 = $(CCFILES:%.cc=%_x86_32.o)
OBJECTS_X86_64 = $(CCFILES:%.cc=%_x86_64.o)

CFLAGS =	-Wall \
			-enable-static \
			-Wno-long-long \
			-pthread \
			-DXP_UNIX # -Werror #-std=c++0

INCLUDES =	-I$(NACLPORTS_ROOT) \
			-I$(NACL_SDK_ROOT)

LDFLAGS =	-lgoogle_nacl_imc \
			-lgoogle_nacl_npruntime \
			-lgoogle_nacl_pgl \
			-lgoogle_nacl_gpu \
			-lpthread \
			-lsrpc

OPT_FLAGS = -O2

# The check_variables target is in nacl_build.mk.
all: check_variables pplugin_x86_32.nexe # life_x86_64.nexe

# nacl_build.mk has rules to build .o files from .cc files.
-include $(NACLPORTS_ROOT)/common_build_scripts/nacl_build.mk

pplugin_x86_32.nexe: $(OBJECTS_X86_32)
	$(CPP) $^ $(LDFLAGS) -m32 -o $@

pplugin_x86_64.nexe: $(OBJECTS_X86_64)
	$(CPP) $^ $(LDFLAGS) -m64 -o $@

clean:
	-$(RM) $(OBJECTS_X86_32) $(OBJECTS_X86_64) \
		pplugin_x86_32.nexe pplugin_x86_64.nexe