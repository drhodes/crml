# Copyright 2010, The Native Client SDK Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can
# be found in the LICENSE file.

# Makefile for the PI Generator example.

# /home/derek/dev/naclports/src/build_tools/native_client_sdk_0_1_589_0/toolchain/linux_x86/nacl64/include

.PHONY: all clean

CCFILES =	npp_gate.cc	\
			pi_generator.cc \
			pi_generator_module.cc \

#npn_bridge.cc \
#scripting_bridge.cc

OBJECTS_X86_32 = $(CCFILES:%.cc=%_x86_32.o)

NACL_SDK_ROOT = ../..

CFLAGS = -Wall -Wno-long-long -pthread -DXP_UNIX -Werror
INCLUDES =	-I $(NACL_SDK_ROOT) \
			-I $(NACL_SDK_ROOT)src/toolchain/linux_x86/nacl64/include \
			-I ../../include \
			-I /home/derek/dev/crml/crml/src

LDFLAGS =	-L /home/derek/dev/crml/crml/build \
			-l google_nacl_imc \
			-l google_nacl_npruntime \
			-l pthread \
			-l srpc \
			-l crml-core

OPT_FLAGS = -O2

all: check_variables pi_generator_x86_32.nexe

# common.mk has rules to build .o files from .cc files.
-include ../common.mk

pi_generator_x86_32.nexe: $(OBJECTS_X86_32)
	$(CPP) $^ $(LDFLAGS) -m32 -o $@

clean:
	-$(RM) $(OBJECTS_X86_32) \
		pi_generator_x86_32.nexe

# This target is used by the SDK build system to produce a pre-built version
# of the .nexe.  You do not need to call this target.
install_prebuilt: pi_generator_x86_32.nexe
	-$(RM) $(OBJECTS_X86_32)
