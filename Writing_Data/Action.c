Action()
{
	int i, iteration_count = 100;
	
	merc_timer_handle_t timer;
	double time_elapsed;
	
	/*---------------------------------------------------------------------------------
		Using appendlog
		===============
		This function (defined in vuser_init.c) is the simplest of the three
		techniques shown here. It is entirely self-contained, and takes a file name
		and string as parameters. It opens the file, appends the line plus a newline
		character and closes it.

		Pros:
		- Simple to use
		- Encapsulated (no references to external objects, such as variables
		Cons:
		- Open, write, flush and close every time is "expensive"
		Summary:
		- Use this for occasional writes, such as logging errors
	---------------------------------------------------------------------------------*/
	lr_output_message("Starting appendlog() test with %d iterations", iteration_count);
	timer = lr_start_timer();
	for (i = 0; i < iteration_count; i++) {
		char buffer[1024];
		sprintf(buffer, "Iteration %d", i); // Newline is appended by the function
		appendlog(file1, buffer);
	}
	time_elapsed = lr_end_timer(timer);
	lr_output_message("appendlog() took %f seconds", time_elapsed);
	
	/*---------------------------------------------------------------------------------
		Using buffered and unbuffered output
		====================================
		This technique requires code in three places:
		- vuser_init.c - Open the file and save the file handle in a global variable
		- action.c - Write output to the file handle using fprintf()
		- vuser_end.c - Close the file, finally flushing the buffer
		
		The C compiler automatically buffers file-writes to improve overall performance.
		This can be a problem if you want to user external tools, such as a "tail"
		utility, to externally track progress. You can overcomne this by using
		fflush() after the fprintf(), however this does slow execution time, but not
		as much as appendlog(), which opens and closes the file every time.

		Pros:
		- Faster (no open and close processing for each cycle)
		- Optional "flush" ensures up to date file
		Cons:
		- More complex to code and use
		- Optional "flush" operation slows overall performance
		Summary:
		- Use this for frequents writes, such as data capture and generation
	---------------------------------------------------------------------------------*/
	// Using buffered output
	lr_output_message("Starting buffered test with %d iterations", iteration_count);
	timer = lr_start_timer();
	for (i = 0; i < iteration_count; i++) {
		char buffer[1024];
		fprintf(handle2, "Iteration %d\n", i);
	}
	time_elapsed = lr_end_timer(timer);
	lr_output_message("buffered took %f seconds", time_elapsed);
	
	// Using unbuffered output
	lr_output_message("Starting unbuffered test with %d iterations", iteration_count);
	timer = lr_start_timer();
	for (i = 0; i < iteration_count; i++) {
		char buffer[1024];
		fprintf(handle3, "Iteration %d\n", i);
		fflush(handle3);
	}
	time_elapsed = lr_end_timer(timer);
	lr_output_message("unbuffered took %f seconds", time_elapsed);
	
	return 0;
}
