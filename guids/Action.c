void save_GUID(char * paramName) {
	
	// Temporary storage to hold the GUID
	char guid[37];
	
	// Initialise the rand function (could do this once in vuser_init.c)
	srand(time(NULL));
	
	// Generate the GUID
	// - Formatting achieved by using blocks of %04x separated by hyphens
	//   %04x is a hex representation of an integer value, zero padded to
	//   four digits
	sprintf(guid, "%04x%04x-%04x-%04x-%04x-%04x%04x%04x",
	        rand(),
	        rand(),
	        rand(),
	        rand(),
	        rand(),
	        rand(),
	        rand(),
	        rand());

	// Save the parameter using the name passed into the function
	lr_save_string(guid, paramName);
	
	return;
}

Action()
{
	// Generate the GUID
	save_GUID("myGUID");
	
	// Print it out to prove a point
	lr_message("myGUID = %s", lr_eval_string("{myGUID}"));

	return 0;
}
