 void fVerifyScreen(){
	int iDebug;
	
	// Lets first check if the standard err cErr has a value

	if(strcmp(lr_eval_string("{cErr}"),"") != 0){
		// OK We have an error - standard thing to do is close off the current transaction
		lr_end_transaction(lr_eval_string("{pTransactionName}"), LR_FAIL);
		// That done the amount of wasted time we have in the transaction is minimised.
		// Now we need to log the error.

		lr_error_message("TIVErr: Error found Server:%s, Page:%s, Error: %s, Version:%s", lr_eval_string("{cServerName}"), lr_eval_string("{cPageTitle}"),lr_eval_string("{cErr}"), lr_eval_string("{cVersion}"));

		// If we have a VTS server collecting errors lets use that. We'll use another function, from below

	// Log Levels:
	// LR_MSG_CLASS_DISABLE_LOG
	// LR_MSG_CLASS_BRIEF_LOG
	// LR_MSG_CLASS_EXTENDED_LOG
	// LR_MSG_CLASS_RESULT_DATA
	// LR_MSG_CLASS_PARAMETERS
	// LR_MSG_CLASS_FULL_TRACE
		iDebug = lr_get_debug_message();
	
		lr_set_debug_message(LR_MSG_CLASS_EXTENDED_LOG, LR_SWITCH_ON);
		
		lr_debug_message(LR_MSG_CLASS_EXTENDED_LOG | LR_MSG_CLASS_RESULT_DATA,"TIVMsg: %s loaded via server: %s", lr_eval_string("{pTransactionName}"), lr_eval_string("{cServerName}"));
		
		lr_set_debug_message(iDebug, LR_SWITCH_ON);		
		
		fLogErrorToVTS();

	}else{
		// OK looks like we passed.
	
		lr_end_transaction(lr_eval_string("{pTransactionName}"), LR_AUTO);

	}

}

vuser_init()
{	 
	char* sBuf;
	int iid, isid;
	char* sGroupname;
	
	lr_whoami(&iid, &sGroupname, &isid);

	if((sBuf = (char *)malloc(strlen(sGroupname)*sizeof(char)) + (sizeof(char)*7))==NULL){
		lr_error_message("TIVMsg: Out of memory");
		lr_exit(LR_EXIT_VUSER, LR_FAIL);
	}
	sprintf(sBuf,"%s:%d",sGroupname, iid);
	lr_save_string(sBuf,"pVUID");

	return 0;
}
