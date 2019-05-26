#include<windows.h>
#include<stdio.h>

DCB DCBrs232win;

int main()
{
  HANDLE hComm;
  char teste[10];

  hComm = CreateFile("\\\\.\\COM4\0",                //port name
                      GENERIC_READ | GENERIC_WRITE, //Read/Write
                      0,                            // No Sharing
                      NULL,                         // No Security
                      OPEN_EXISTING,// Open existing port only
                      0,            // Non Overlapped I/O
                      NULL);        // Null for Comm Devices
GetCommState(hComm,&DCBrs232win);
DCBrs232win.BaudRate = 9600; /* 9600, 144400, etc. */
DCBrs232win.ByteSize = 8; /* 5, 6, 7 ou 8 */
DCBrs232win.Parity = NOPARITY; /* NOPARITY, MARKPARITY,EVENPARITY, ODDPARITY */
DCBrs232win.StopBits = ONESTOPBIT;
if (SetCommState(hComm,&DCBrs232win))
{printf("\n passou");}
else{printf("\n nao");}


int checatransmissao;

BOOL batata ;
char *enviado;
*enviado=9;
batata=WriteFile(hComm,enviado,1,
(LPDWORD)(&checatransmissao),NULL);

  if (hComm == INVALID_HANDLE_VALUE)
      printf("Error in opening serial port");
  else
      printf("opening serial port successful");


  CloseHandle(hComm);//Closing the Serial Port

  return 0;
}
