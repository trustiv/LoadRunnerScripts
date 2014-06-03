//Arrays used to hold rows of data returned from VTS as well as to store variable names based on column headings
char **colnames = NULL;
char **rowdata = NULL;

//Return code, used to check whether VTS command was successful
int ret;
int inx=0;

//N.B. this sample script removes a row each time from the first VTS table and places that row of data with an additional
//column of data (mimicking a new user ID / timestamp / unique identifier) that can be used by subsequent scripts.
//This is ideal for data destructive scripts.

GetSourceDataLoginNewCustomer()  
{
	//Connect to third VTS server (may prefer to do this in vuser_init)
	pvci = vtc_connect(VtsServer3,nPort3,VTOPT_KEEP_ALIVE);
    //lr_output_message("pvci=%d\n", pvci);
    
    lr_start_transaction("BP5_LoginNew_GetData");
    
	//Retrieve the topmost row, removes the row from the table.
	//To take data from the table non destructively, use the lrvtc_query_row function.	
	ret = vtc_retrieve_row(pvci, &colnames, &rowdata);
	//lr_output_message("Row retrieval ret=%d\n", ret);
	
    lr_end_transaction("BP5_LoginNew_GetData", LR_AUTO);
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
	
    //Deallocate the buffers containing arrays of returned strings
    vtc_free_list(colnames);
	vtc_free_list(rowdata);    

	//Disconnect from VTS (may prefer to do this in vuser_end)
    vtc_disconnect(pvci);   
    
    return 0;
}


Action()
{
	lr_save_string("","first_name");
	
    GetSourceDataLoginNewCustomer();

	if( strcmp( lr_eval_string("{first_name}"), "") != 0)
		{
		// {first_name} is not null
	    lr_output_message("%s %s Logged in using username [%s] and password [%s]", 
                      lr_eval_string("{first_name}"),
                      lr_eval_string("{last_name}"),
                      lr_eval_string("{username}"),
                      lr_eval_string("{password}"));
	    lr_vuser_status_message("%s %s Logged in using username [%s] and password [%s]", 
                      lr_eval_string("{first_name}"),
                      lr_eval_string("{last_name}"),
                      lr_eval_string("{username}"),
                      lr_eval_string("{password}"));
		
    	lr_think_time(5);
	}

else
	{
    // {first_name} is null, wait for more data
    lr_output_message("No data for user login...waiting for 50 seconds.");
    lr_vuser_status_message("No data for user login...waiting for 50 seconds.");
    
    lr_think_time(50);
    	
    lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_PASS);
	}
    
   return 0;
}