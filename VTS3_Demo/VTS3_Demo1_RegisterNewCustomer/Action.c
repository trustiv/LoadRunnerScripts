//Arrays used to hold rows of data returned from VTS as well as to store variable names based on column headings
char **colnames = NULL;
char **rowdata = NULL;

//Return code, used to check whether VTS command was successful
int ret;
unsigned short status = 0;

int inx = 0;
//N.B. this sample script removes a row each time from the first VTS table and places that row of data with an additional
//column of data (mimicking a new user ID / timestamp / unique identifier) that can be used by subsequent scripts.
//This is ideal for data destructive scripts.

GetSourceDataRegister()  
{
	//Connect to first VTS server (may prefer to do this in vuser_init)
	pvci = vtc_connect(VtsServer1,nPort1,VTOPT_KEEP_ALIVE);
    //lr_output_message("pvci=%d\n", pvci);
	
    lr_start_transaction("BP1_RegisterNew_GetData");
    
	//Retrieve the topmost row, removes the row from the table.
	//To take data from the table non destructively, use the lrvtc_query_row function.	
	ret = vtc_retrieve_row(pvci, &colnames, &rowdata);
	//lr_output_message("Row retrieval ret=%d\n", ret);
	
	// Because the vtc_retrieve_row function returns an array, not a populated list
	// We have to check the content and save the parameters ourselves
	// If we stick to lrvtc_retrieve_row this step is unneeded

	if (!colnames){
	//	lr_output_message("No data found");
		lr_save_string("","first_name");
	}else
		for (inx=0; colnames[inx]; inx++){
			lr_save_string(rowdata[inx],colnames[inx]);
		}
	
    lr_end_transaction("BP1_RegisterNew_GetData", LR_AUTO);
    
    //Can refer to the variables returned from VTS using the parameter names.
    //lr_output_message("First name was  : %s . Last name was : %s", 
    //                  lr_eval_string("{first_name}"),
    //                  lr_eval_string("{last_name}"));
    
    //Deallocate the buffers containing arrays of returned strings
    vtc_free_list(colnames);
	vtc_free_list(rowdata);    

	//Disconnect from VTS (may prefer to do this in vuser_end)
    vtc_disconnect(pvci);  

	return 0;    
}

OutputUsedDataRegister()
{
	//Connect to second VTS server
	pvci = vtc_connect(VtsServer2,nPort2,VTOPT_KEEP_ALIVE);
    //lr_output_message("pvci=%d\n", pvci);   
    
    lr_start_transaction("BP2_RegisterNew_WriteData");
    
    //Append rows of "used" data as well as unique identifier {_VTS_ID}
    ret = vtc_send_row1(pvci, 
                        "_VTS_ID;first_name;last_name;company_name;address;city;county;postal;phone1;phone2;email;web",
        				"{pVuserID}_{pTimeStamp};{first_name};{last_name};{company_name};{address};{city};{county};{postal};{phone1};{phone2};{email};{web}",
        				";",
        				VTSEND_SAME_ROW,
        				&status);
    
    lr_end_transaction("BP2_RegisterNew_WriteData", LR_AUTO);
    
	//lr_output_message("Row submission ret=%d\n", ret);
        
	//Disconnect from VTS
    vtc_disconnect(pvci);  
    
    return 0;
}

Action()
{
    GetSourceDataRegister();
    
    if( strcmp( lr_eval_string("{first_name}"), "") != 0)
	{
    // {first_name} is not null
     lr_output_message("%s %s Registered as a new customer", 
                      lr_eval_string("{first_name}"),
                      lr_eval_string("{last_name}"));
    
    lr_think_time(5);
    
    OutputUsedDataRegister();
    lr_output_message("New Customer %s %s is now awaiting approval", 
                      lr_eval_string("{first_name}"),
                      lr_eval_string("{last_name}"));
    
    lr_think_time(5);
	}
    
else
	{
    // {first_name} is null, wait for more data
    lr_output_message("No data for user login...waiting for 50 seconds.");
    lr_think_time(50);
    	
    lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_PASS);
	}   


    
    return 0;
}