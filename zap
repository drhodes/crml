# -*- sh -*-

make clean

HOME=`pwd`
cd $HOME && cd ./test/pi_generator_crml && make clean
cd $HOME && cd ./test/custom_method && make clean
cd $HOME && cd ./test/pepper && make clean

cd $HOME && cd ./docs/doxy && rm -rf html latex



