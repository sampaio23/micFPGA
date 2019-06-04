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

// Create the overlapped event. Must be closed before exiting
// to avoid a handle leak.
osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

if (osReader.hEvent == NULL)
   {
       printf("Erro");
   }

if (!fWaitingOnRead) {
   // Issue read operation.
   if (!ReadFile(hComm, lpBuf, 3, &dwRead, &osReader)) {
      if (GetLastError() != ERROR_IO_PENDING)     // read not delayed?
         printf("Error in communications; report it.");
      else
         fWaitingOnRead = TRUE;
   }
   else {
      // read completed immediately
     printf("%x\n",lpBuf);
    }
}
}
