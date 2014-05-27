vuser_end()
{
	// Close the log files if they were opened
	if (handle2) {
		fclose(handle2);
	}
	
	if (handle3) {
		fclose(handle3);
	}
	
	// Clean up the test files
	//tidy_up(); // Defined in vuser_init.c
	
	return 0;
}
