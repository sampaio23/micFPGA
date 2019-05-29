#include<windows.h>
#include<stdio.h>

DCB DCBrs232win;

int main()
{
  HANDLE hComm;
  char teste[10];

  hComm = CreateFile("\\\\.\\COM3\0",                //port name
                      GENERIC_READ | GENERIC_WRITE, //Read/Write
                      0,                            // No Sharing
                      NULL,                         // No Security
                      OPEN_EXISTING,// Open existing port only
                      0,            // Non Overlapped I/O
                      NULL);        // Null for Comm Devices

  if (hComm == INVALID_HANDLE_VALUE)
      printf("Error in opening serial port");
  else
      printf("opening serial port successful");

GetCommState(hComm,&DCBrs232win);

DCBrs232win.BaudRate = 9600; /* 9600, 144400, etc. */
DCBrs232win.ByteSize = 8; /* 5, 6, 7 ou 8 */
DCBrs232win.Parity = NOPARITY; /* NOPARITY, MARKPARITY,EVENPARITY, ODDPARITY */
DCBrs232win.StopBits = ONESTOPBIT;
if (SetCommState(hComm,&DCBrs232win))
{printf("\n passou");}
else{printf("\n nao");}

int checatransmissao;

/*
BOOL batata ;
char *enviado;
*enviado=9;
batata=WriteFile(hComm,enviado,1,
(LPDWORD)(&checatransmissao),NULL);
printf("teste");

*/

BOOL status;
char lido[10000] = {0};
SetCommMask(hComm,EV_RXCHAR);
DWORD dwEventMask;
int j;

//char buffer[100000];

//int cont=100000;
//while(cont>0){
    //if(WaitCommEvent(hComm, &dwEventMask, NULL))
    //{
    status = ReadFile(hComm,lido,9999,
(LPDWORD)(&checatransmissao),NULL);

    for (j = 0; j < 10000 ; j++)
        printf("%c",(char)lido[j]);
    //}
//    cont--;
//}

    //printf("%s",buffer);


  CloseHandle(hComm);//Closing the Serial Port

  return 0;
}
