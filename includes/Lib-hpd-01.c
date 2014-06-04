//#This library is an example of an include file
// Author: Gordon Appleby
// Purpose - HP discovery Deep Dive

#ifndef _LIB_HPD_H
#define _LIB_HPD_H

void fRegisterChecks(char* sTitleLeftBound, char* sTitleRightBound, char* sNewTransactionName){
	// PARAMS
	// sTitleRightBound = text to check for the apps standard title RB=
	// sTitleLeftBound = text to check for the apps standard title LB=
	// sNewTransactionName - Save this a pCurrentTransaction and start the transaction

	web_reg_save_param("cPageTitle",
		sTitleLeftBound,
		sTitleRightBound,
		"Notfound=warning",
		LAST);

	web_reg_save_param("cVersion",
		"LB=version\">",
		"RB=<",
		"Notfound=warning",
		LAST);

	web_reg_save_param("cServerName",
	    "LB=Set-Cookie: ROUTEID=.",
	    "RB=;",
	    "Notfound=warning",
	    LAST);

	web_reg_save_param("cErr",
	    "LB=class='err'>",
	    "RB=<",
	    "Notfound=warning",
	    LAST);

	lr_save_string(sNewTransactionName, "pTransactionName");

	lr_start_transaction(lr_eval_string("{pTransactionName}"));

}

void fLogErrorToVTS(){
	//Details for specific VTS server (used for source data)
	char  *VtsErrServer = "127.0.0.1";
	int   nPortErr = 9000;
	int ret;
	unsigned short status = 0;

	PVCI2 pvci = 0;

	//Connect to Err VTS server
	pvci = vtc_connect(VtsErrServer,nPortErr,VTOPT_KEEP_ALIVE);
	if(pvci<0){
		//VTS Error occured
		lr_error_message("TIVMsg: Error logging failed to contact VTS server on %s:%s",VtsErrServer,nPortErr);
		return;
	}
    ret = vtc_send_row1(pvci, "VUID;Transaction;Server;PageTitle;Err",
	        "{pVUID};{pTransactionName};{cServerName};{cPageTitle};{cErr}", ";",
	        VTSEND_SAME_ROW,
       	&status);

	ret = vtc_disconnect(pvci);
}

void fVerifyScreen(){
	int iDebug;
	char sBuf[126] = "";
	int bIsErr = 0; // false

	// Lets first check if the standard err cErr has a value

	if(strcmp(lr_eval_string("{cErr}"),"") != 0){
		// OK We have an error - standard thing to do is close off the current transaction

		lr_stop_transaction(lr_eval_string("{pTransactionName}"));

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

		bIsErr = 1; // true

	}

	if(strcmp(lr_eval_string("{cVersion}"),sAppVersion) != 0){
		lr_stop_transaction(lr_eval_string("{pTransactionName}"));

		sprintf(sBuf, "TIVMsg: Application version incorrect, expected %s, found %s", sAppVersion, lr_eval_string("{cVersion}"));

		lr_save_string(sBuf, "cErr");

		fLogErrorToVTS();

		bIsErr  = 1; //true

	}

	if (bIsErr){
		lr_resume_transaction(lr_eval_string("{pTransactionName}"));
		lr_end_transaction(lr_eval_string("{pTransactionName}"), LR_FAIL);
		lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_FAIL);
	}else {
		// OK looks like we passed.

		lr_end_transaction(lr_eval_string("{pTransactionName}"), LR_AUTO);
	}

}

#endif //_LIB_HPH_H