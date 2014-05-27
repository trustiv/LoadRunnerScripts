/*=================================================================
	HP LoadRunner provides support for capturing and processing
	arrays of parameters.
	
	Capture is performed using the web_reg_save_... functions by
	specifying that All instances should be captured. Each instance
	is saved in a parameter prefixed with the name specified in the
	call and suffixed with an ordinal value _n, e.g. CustNo_3. A
	summary parameter is created with the suffix _count.
	
	An array can also be manually constructed (see below).
	
	Once captured these parameters can be operated on using a suite
	of built-in functions prefixed lr_paramarr as follows (see help
	text for details).
	
	Capturing multiple values from a single parameter can now also
	be performed using lr_save_param_regexp.
	
	In this example we will save the entries from a captured HTML
	bulleted list. Saving only list elements, <li>...</li>, may
	well capture values from other lists and will be complicated by
	embedded attributes.
	
	Further details on the structure of Regular Expressions can be
	found at http://en.wikipedia.org/wiki/Regular_expression.
	
=================================================================*/
Action()
{
	// Save the string (this would be the result of a web_reg_save...)
	lr_save_string("<ul>"
		"<li><a href=\"/wiki/Portal:Arts\" title=\"Portal:Arts\">Arts</a></li>"
		"<li><a href=\"/wiki/Portal:Biography\" title=\"Portal:Biography\">Biography</a></li>"
		"<li><a href=\"/wiki/Portal:Geography\" title=\"Portal:Geography\">Geography</a></li>"
		"</ul>", "pArray");
	
	// Capture array of values matching a regular expression
	lr_save_param_regexp(lr_eval_string("{pArray}"),
	    strlen(lr_eval_string("{pArray}")),
	    "RegExp=<li><a.*?>(.+?)</a></li>",
	    "Ordinal=All", // <-- This forces the array creation
	    "ResultParam=Element",
	    LAST);
	
	/*
		Process the array
	*/
	{
		int i;
		
		lr_output_message("=================");
		lr_output_message("Enumerate entire array");
		
		for (i=1; i<=lr_paramarr_len("Element"); i++) {
			lr_output_message("Instance %d = '%s'",
			     i, lr_paramarr_idx("Element", i));
		}
		
		lr_output_message("-----------------");
		lr_output_message("Six random samples");
		
		for (i=1; i<=6; i++) {
			lr_output_message("Random instance '%s'",
			     lr_paramarr_random("Element"));
		}
		lr_output_message("=================");
	}
	
	/*
		Manually construct another array
	*/
	{
		int i, arrsize = 10;
		
		for (i=1; i<=arrsize; i++) {
			char name[256], buf[256];
			
			sprintf(name, "Manual_%d", i);
			sprintf(buf, "Value is %d", i);
			
			lr_save_string(buf, name);
		}
		
		lr_save_int(arrsize, "Manual_count");
	}
	
	/*
		Process constructed array
	*/
	{
		int i;

		lr_output_message("=================");
		lr_output_message("Enumerate manual array");
		
		for (i=1; i<=lr_paramarr_len("Manual"); i++) {
			lr_output_message("Instance %d = '%s'",
			     i, lr_paramarr_idx("Manual", i));
		}
		
		lr_output_message("-----------------");
		lr_output_message("Six random samples");
		
		for (i=1; i<=6; i++) {
			lr_output_message("Random instance '%s'",
			     lr_paramarr_random("Manual"));
		}
		lr_output_message("=================");
	}
	
	return 0;
}