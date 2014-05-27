Action()
{
	int iDebug;
	
	web_cleanup_cookies( );
	
	lr_start_transaction("_TIVApp_001_My_Test");
	
	lr_save_string("TIVApp_001_001_Homepage", "pTansactionName");
	
	web_reg_find("Fail=NotFound",
		"Search=Body",
		"Text=Test site.",
		LAST);

	web_reg_save_param("cServerName",
	    "LB=Set-Cookie: ROUTEID=.",
	    "RB=;",
	    "Notfound=warning",
	    LAST);
	
	web_reg_save_param("cVersion",
	    "LB=version\">",
	    "RB=<",
	    "Notfound=warning",
	    LAST);
	
	lr_start_transaction(lr_eval_string("{pTansactionName}"));
	
	web_url("Homepage", 
		"URL=http://{pURL}/", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);
	// Log Levels:
	// LR_MSG_CLASS_DISABLE_LOG
	// LR_MSG_CLASS_BRIEF_LOG
	// LR_MSG_CLASS_EXTENDED_LOG
	// LR_MSG_CLASS_RESULT_DATA
	// LR_MSG_CLASS_PARAMETERS
	// LR_MSG_CLASS_FULL_TRACE
	iDebug = lr_get_debug_message();

	lr_output_message("TIVMsg: Msg Level was: %d", iDebug);
	
	lr_set_debug_message(LR_MSG_CLASS_EXTENDED_LOG, LR_SWITCH_ON);
	
	lr_debug_message(LR_MSG_CLASS_EXTENDED_LOG | LR_MSG_CLASS_RESULT_DATA,"TIVMsg: %s loaded via server: %s", lr_eval_string("{pTansactionName}"), lr_eval_string("{cServerName}"));
	
	lr_set_debug_message(iDebug, LR_SWITCH_ON);
	
	lr_end_transaction(lr_eval_string("{pTansactionName}"), LR_AUTO);
	
	lr_end_transaction("_TIVApp_001_My_Test", LR_AUTO);
	
	return 0;
}