# CMSC-125-Project
Hangman for ICS-OS
--------------------------------
1. Clone this repository or download the files.
   * Move the hangman folder to /ics-os/contrib
   * Inside /ics-os/contrib/hangman : 
     ```
     $make
     $make install
     ```

2. Copy scores.txt, movies.txt, and uplb.txt from /other to /ics-os/apps.

3. Perform the steps to install ics-os.
   ```
   $cd ../..
   $make clean
   $make vmdex
   $make floppy
   #make boot-floppy
   ```

4. Run hangman.exe inside ics-os
