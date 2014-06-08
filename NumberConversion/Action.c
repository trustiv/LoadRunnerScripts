Action()
{	float nValue;
	double nResult;
	char sValue[124];
	
	// Save a floating point vaue (with decimal)
	nValue = 13.21;
	
	// Save the value to a string
	sprintf(sValue, "%0.2f", nValue);
	
	// Save the string to a parameter
	lr_save_string(sValue, "pValue");
	
	lr_output_message("TIVMsg: String value: %s", sValue);
	lr_output_message("TIVMsg: Parameter value: %s", lr_eval_string("{pValue}"));
	
	//Convert a string float usinf atoi
	nResult = atoi(sValue);
	
	// Perform some calculation
	nResult = nResult / 3;
	lr_output_message("TIVMsg: Value divided by 3");
	                  
	// save the value
	sprintf(sValue, "%0.4f", nResult);
	
	// save the string value to a parameter
	lr_save_string(sValue, "pValue");
	
	lr_output_message("TIVMsg: String value: %s", sValue);
	
	lr_output_message("TIVMsg: Parameter value: %s", lr_eval_string("{pValue}"));
	
	// Saving the value directly using save in t function loses the decimals
	lr_save_int(nResult, "pIntValue");
	
	lr_output_message("TIVMsg: Int value: %s", lr_eval_string("{pIntValue}"));
	
	// Converting number formats
	lr_save_string("6.0504331456E7","pScientific");
	lr_convert_double_to_double("pScientific","%.2f","pDecimalConverted");
	
	lr_output_message("TIVMsg: Scientific Notation: %s to decimal: %s", lr_eval_string("{pScientific}"), lr_eval_string("{pDecimalConverted}"));
	
	return 0;
}
