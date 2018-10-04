IMPORTANT: To verify proper execution: ensure that the test_int.txt file
is properly formatted by opening it in vim via "vim test_in.txt" and executing
":set ff=unix", save with ":w", and quit with ":q". This is necessary because of 
warnings being generated while committing to git.

This project will generate an executable called Project1.exe.

Upon running this executable, a welcome message will be displayed 
along with directions to invoke the help and quit commands. The help
command will print a string that corresponds to each of the commands 
that will be supported by the end of the project (not all are supported now).
The quit command will cause the program to print an exit message and
terminate.

Most commands have a standard version and a "smart" version. For applicable
commands, "smart" versions use offsets from an already allocated block of memory,
while the standard version uses absolute addresses.

The "test" make target will demonstrate the basic functionality including
warning messages, failed pattern verification with time of calculation measurement,
and more of the "smart" versions of the command. "Standard" versions of the
commands were not included as directed because the results will not be 
reproducible in different environments.





