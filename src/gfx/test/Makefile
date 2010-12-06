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

OPTFLAG = -O3

all:
	nacl-g++ $(OPTFLAG) space_hash-test.cc $(LDFLAGS) -o space_hash-testbin
	nacl-g++ $(OPTFLAG) utility-test.cc $(LDFLAGS) -o utility-testbin

	@sel_ldr ./space_hash-testbin
	@sel_ldr ./utility-testbin

clean:
	@rm -f ./*testbin