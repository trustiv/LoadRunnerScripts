
void fTestMe(char* sVar){
	char * sBuf;

	if((sBuf = (char *)malloc((strlen(sVar) + strlen(" was a bar fighter") + 2)* sizeof(char))) == NULL){
		lr_error_message("Out of memory error");
	}else{
		sprintf(sBuf,"%s was a bar fighter", sVar);
		lr_output_message(sBuf);

	}

	free(sBuf);
}

void fGetVUID(){
	char * sBuf;
	int iid;
	int	isid;
	char *sGroupname;

	lr_whoami(&iid, &sGroupname, &isid);

	if((sBuf = (char *)malloc((strlen(sGroupname) + 7)* sizeof(char))) == NULL){
		lr_error_message("Out of memory error");
	}else{
		sprintf(sBuf,"%s:%d",sGroupname, iid);
		lr_save_string(sBuf,"pVUID");
	}

	lr_output_message("TIVMsg: Group name: %s", sBuf);

	free(sBuf);
}

void fCaptureScreen (char* sTitleLeftBound, char* sTitleRightBound){
	char * sLB;
	char * sRB;

	if((sLB = (char *)malloc((strlen(sTitleLeftBound) + strlen("LB/IC=") + 2)* sizeof(char))) == NULL){
		lr_error_message("Out of memory error");
		lr_exit(LR_EXIT_VUSER, LR_FAIL);
	}else{
		sprintf(sLB,"LB/IC=%s", sTitleLeftBound);
		lr_output_message("TIVMsg: LB:%s", sLB);

	}

	if((sRB = (char *)malloc((strlen(sTitleRightBound) + strlen("RB/IC=") + 2)* sizeof(char))) == NULL){
		lr_error_message("Out of memory error");
		lr_exit(LR_EXIT_VUSER,LR_FAIL);
	}else{
		sprintf(sRB,"RB/IC=%s", sTitleRightBound);
		lr_output_message("TIVMsg: RB:%s", sRB);
	}

	web_reg_save_param("cPageTitle",
		sLB,
		sRB,
		"Notfound=warning",
	LAST);

	free (sLB);
	free (sRB);
}