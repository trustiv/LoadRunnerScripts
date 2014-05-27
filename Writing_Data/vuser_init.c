/*-------------------------------------------------------------------------
	Sometimes it is desirable (or even necessary) to save data captured
	during script execution to a text file for later analysis or re-use.
	This script example explores two techniques.
-----------------------------------------------------------------------*/

void appendlog (char * filename, char * value)
{
	// Holds the file handle
	long f;

	// Attempt to open the file for appending, assigning the file handle
	if ((f = fopen(filename, "a")) == NULL )
	{
		// If the handle is null, the open failed. Generate an error message
		lr_error_message("Unable to open file >%s< to append value >%s<",
			filename,
			value);
		return;
	}

	// write the value to the file handle, appending a newline
	fprintf(f, "%s\n", value);

	// Flush the buffer and close the file
	fclose(f);
}

void tidy_up() {
	char command [1024];
	
	sprintf(command, "del %s /Q", file1);
	system(command);
	
	sprintf(command, "del %s /Q", file2);
	system(command);
	
	sprintf(command, "del %s /Q", file3);
	system(command);
}

vuser_init()
{
	// Tidy up any previous files
	tidy_up(); // Defined in vuser_init.c
	
	// Attempt to open logfiles 2 & 3 for appending, assigning the file handle
	if ((handle2 = fopen(file2, "a")) == NULL )
	{
		// If the handle is null, the open failed. Generate an error message
		lr_error_message("Unable to open file >%s<\n",
			file2);
		return -1;
	}

	if ((handle3 = fopen(file3, "a")) == NULL )
	{
		// If the handle is null, the open failed. Generate an error message
		lr_error_message("Unable to open file >%s<\n",
			file3);
		return -1;
	}

	return 0;
}
