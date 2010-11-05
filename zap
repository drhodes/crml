cd /home/derek/dev/crml/crml/test/pi_generator_crml
make clean

cd /home/derek/dev/crml/crml
make clean

rm -rf /tmp/latex
mv /home/derek/dev/crml/crml/docs/doxy/latex /tmp
rm -vrf /tmp/latex

rm -rf /tmp/html
mv /home/derek/dev/crml/crml/docs/doxy/html /tmp
rm -vrf /tmp/html


