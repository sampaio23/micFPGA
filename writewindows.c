#include<windows.h>
#include<stdio.h>
int main()
{


HANDLE hComm;
hComm = CreateFile( "\\\\.\\COM3\0",
                    GENERIC_READ | GENERIC_WRITE,
                    0,
                    0,
                    OPEN_EXISTING,
                    FILE_FLAG_OVERLAPPED,
                    0);

   // error opening port; abort
DCB DCBrs232win;
GetCommState(hComm,&DCBrs232win);
DCBrs232win.BaudRate = 9600; /* 9600, 144400, etc. */
DCBrs232win.ByteSize = 8; /* 5, 6, 7 ou 8 */
DCBrs232win.Parity = NOPARITY; /* NOPARITY, MARKPARITY,EVENPARITY, ODDPARITY */
DCBrs232win.StopBits = ONESTOPBIT;
if (SetCommState(hComm,&DCBrs232win))
{printf("\n passou");}
else{printf("\n nao");}

DWORD dwRead;
BOOL fWaitingOnRead = FALSE;
OVERLAPPED osReader = {0};
char lpBuf[300]= {0};
lpBuf[0]=5;


   OVERLAPPED osWrite = {0};
   DWORD dwWritten;
   BOOL fRes;

   // Create this writes OVERLAPPED structure hEvent.
   osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
   if (osWrite.hEvent == NULL){
      printf("Error creating overlapped event handle.");
      return FALSE;}

   // Issue write.
   if (!WriteFile(hComm, lpBuf, 1, &dwWritten, &osWrite)) {
      if (GetLastError() != ERROR_IO_PENDING) {
         // WriteFile failed, but it isn't delayed. Report error and abort.
         fRes = FALSE;
      }
      else {
         // Write is pending.
         if (!GetOverlappedResult(hComm, &osWrite, &dwWritten, TRUE)){
            fRes = FALSE;}
         else{
            // Write operation completed successfully.
            fRes = TRUE;}
      }
   }
   else{
      // WriteFile completed immediately.
      fRes = TRUE;}

printf("%c",lpBuf);
CloseHandle(osWrite.hEvent);}


