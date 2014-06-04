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

	char * sLB;
	char * sRB;
	// Lets use parameters to build a standard set of checks and starts

	if((sRB = (char *)malloc((strlen(sTitleRightBound) + strlen("LB=") + 1)*sizeof(char)))==NULL){

		return;
	}else {
		sprintf(sRB,"RB=%s",sTitleRightBound);
	}

	if((sLB = (char *)malloc((strlen(sTitleLeftBound) + strlen("LB=") + 1)*sizeof(char)))==NULL){
		return;
	}else {
		sprintf(sLB,"LB=%s",sTitleLeftBound);
	}

	web_reg_save_param("cPageTitle",
		sLB,
		sRB,
		"Notfound=warning",
		LAST);

	// free the memory for the buffer variable
	free(sRB);
	free(sLB);

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
	int   nPortErr = 8899;
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
    ret = vtc_send_row1(pvci, "VUID;Server;PageTitle;Err",
	        "{pVUID};{cServer};{cPageTitle};{cErr}", ";",
	        VTSEND_SAME_ROW,
       	&status);

	ret = vtc_disconnect(pvci);
}

#endif //_LIB_HPH_H