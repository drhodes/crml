#CCFILES = 

CRML_ROOT = ../../../

CFLAGS =	-Wall \
			-enable-static \
			-Wno-long-long \
			-pthread \
			-std=c++0x \
			-DXP_UNIX # -Werror #-std=c++0

INCLUDES =	-I $(CRML_ROOT)/include \

LDFLAGS =	-L $(CRML_ROOT)/build \
			-L $(CRML_ROOT)/third-party \
			-l crml-core \
			-l crml-gfx \

OPT_FLAGS = -O2

all:
	nacl-g++ -O3 space_hash-test.cc $(LDFLAGS) -o space_hash-test
	@sel_ldr *test$
