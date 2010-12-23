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
	+ make space_hash
	+ make utility
	+ make rect
	+ make vector
	+ make matrix

space_hash:
	nacl-g++ $(OPTFLAG) space_hash-test.cc $(LDFLAGS) -o space_hash-testbin
	@sel_ldr ./space_hash-testbin

utility:
	nacl-g++ $(OPTFLAG) utility-test.cc $(LDFLAGS) -o utility-testbin
	@sel_ldr ./utility-testbin

rect:
	nacl-g++ $(OPTFLAG) rect-test.cc $(LDFLAGS) -o rect-testbin
	@sel_ldr ./rect-testbin

vector:
	nacl-g++ $(OPTFLAG) vector-test.cc $(LDFLAGS) -o vector-testbin
	@sel_ldr ./vector-testbin	

matrix:
	nacl-g++ $(OPTFLAG) $(CFLAGS) matrix-test.cc $(LDFLAGS) -o matrix-testbin
	@sel_ldr ./matrix-testbin	

clean:
	@rm -f ./*testbin