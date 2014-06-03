Action()
{
	lrvtc_create_column("Message");
	
	//Lets measure how long the transaction takes
	lr_start_transaction("VTS_0010_SendMessage");
	
	lrvtc_send_message("Message", "VTS Session Created");

	lr_end_transaction("VTS_0010_SendMessage", LR_AUTO);
	
	return 0;
}
