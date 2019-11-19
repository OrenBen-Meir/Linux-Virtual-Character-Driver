# Linux Virtual Character Driver

This repository is for a virtual character driver.

## Compiling and Setting Up the driver

To compile the driver and insert it, you must do the following:

1. Move to driver directory in the terminal, expected output:

		/path/to/repo/Linux-Virtual-Character-Driver/Driver$

2. Write the following command to compile your module:

		make

3. Write the following command to insert your module:
		
		make insert

You will need super user privilages to use "make insert"

4. Look at your syslog to see any additional instruction the driver has.

To look at it write the command: 

	dmesg
	
or:

	cat /var/log/syslog
	
It will give you instructions on how to insert your device

5. Once you are done doing the instructions, and following any in
the syslog, you can test your module.

## Testing your module

To test your driver, you could use either gcc or python.
You need to be in the Test directory in your terminal with the expected output:
		/path/to/repo/Linux-Virtual-Character-Driver/Test$

#### Using python

Just type:

	python test.py

#### Using c/gcc

To compile, type:

	gcc -o test test.c

To run your executable, type:

	./test

If you want to remove your executable you compiled, write:

	rm test

## Removing and cleaning your driver

To remove your driver and clean your Driver directory, do the following:

1. Move to driver directory in the terminal, expected output:

		/path/to/repo/Linux-Virtual-Character-Driver/Driver$
		
2. Remove your module by writing:

		make remove
		
You need to have super user privilages

3. Clean your Driver directory by doing the following:

		make clean




