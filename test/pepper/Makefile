# Copyright 2010, The Native Client SDK Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can
# be found in the LICENSE file.

NACLPORTS_ROOT	= ~/dev/naclports/src
NACL_SDK_ROOT	= ~/dev/nacl_sdk
CRML_ROOT		= ../../

CCFILES =	main.cc game.cc square.cc

OBJECTS_X86_32 = $(CCFILES:%.cc=%_x86_32.o)

CFLAGS =	-Wall \
			-enable-static \
			-Wno-long-long \
			-pthread \
			-std=c++0x \
			-DXP_UNIX # -Werror #-std=c++0

INCLUDES =	-I $(NACL_SDK_ROOT) \
			-I $(CRML_ROOT)/include

LDFLAGS =	-L $(CRML_ROOT)/build \
			-l crml-win \
			-l crml-core \
			-l crml-sys \
			-l crml-evt \
			-l google_nacl_imc \
			-l google_nacl_npruntime \
			-l google_nacl_pgl \
			-l google_nacl_gpu \
			-l pthread \
			-l srpc \
			-l osg \

OPT_FLAGS = -O2

# The check_variables target is in nacl_build.mk.
all: check_variables pplugin_x86_32.nexe 

# nacl_build.mk has rules to build .o files from .cc files.

-include $(NACLPORTS_ROOT)/common_build_scripts/nacl_build.mk

pplugin_x86_32.nexe: $(OBJECTS_X86_32)
	$(CPP) $^ $(LDFLAGS) -m32 -o $@

clean:
	-$(RM) $(OBJECTS_X86_32) pplugin_x86_32.nexe 