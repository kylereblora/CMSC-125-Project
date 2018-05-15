# CMSC-125-Project
Hangman for ICS-OS
--------------------------------
1. Extract from within ics-os source dir.

   $tar xzvf hangumanu.tar.gz
   $cd contrib/hangman
   $make
   $make install

2. Perform the steps to install ics-os.
   $cd ../..
   $make clean
   $make vmdex
   $make floppy
   #make boot-floppy

3. Copy scores.txt, movies.txt, and uplb.txt to /ics-os/apps.

4. Run lightsout.exe inside ics-os
