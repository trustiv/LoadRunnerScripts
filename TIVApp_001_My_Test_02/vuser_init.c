char sAppVersion[6] = "V0.2";

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
