#! /bin/bash

./mkimage mm/1.jpg 1image
./mkimage mm/1.jpg end
./mkimage mm/2.jpg 2image
./mkimage mm/3.jpg 3image
./mkimage mm/4.jpg 4image
./mkimage mm/5.jpg 5image

cat 2image >> 1image
cat 3image >> 1image
cat 4image >> 1image
cat 5image >> 1image
cat end >> 1image
cat 3 >> 1image

mv 1image /tftpboot/image

rm -f [0-9]image





