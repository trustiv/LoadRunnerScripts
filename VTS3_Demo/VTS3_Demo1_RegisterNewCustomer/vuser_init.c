//Details for first VTS server (used for source data)
char  *VtsServer1 = "127.0.0.1";
int   nPort1 = 8888; 

//Details for second VTS server (used for output data)
char  *VtsServer2 = "127.0.0.1";
int   nPort2 = 8889; 
 
//Connection descriptor 
PVCI2 pvci = 0; 

vuser_init()
{
   return 0;
}