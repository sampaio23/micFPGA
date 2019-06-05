#include <Windows.h>
#include <stdio.h>
#include <string.h>

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
char lpBuf[300];
char auxchar;
BOOL Status;

// Create the overlapped event. Must be closed before exiting
// to avoid a handle leak.
osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;

	if (SetCommTimeouts(hComm, &timeouts) == FALSE)
		printf("\n\n    Error! in Setting Time Outs");
	else
		printf("\n\n    Setting Serial Port Timeouts Successfull");

	//------------------------------------ Setting Receive Mask ----------------------------------------------/

	Status = SetCommMask(hComm, EV_RXCHAR); //Configure Windows to Monitor the serial device for Character Reception

	if (Status == FALSE)
		printf("\n\n  Error! in Setting CommMask");
	else
		printf("\n\n  Setting CommMask successfull");

DWORD dwEventMask;
Status = WaitCommEvent(hComm, &dwEventMask, NULL);
int i, j;
if (Status == FALSE)
	{
		printf("\n    Error! in Setting WaitCommEvent()");
	}
	else //If  WaitCommEvent()==True Read the RXed data using ReadFile();
	{
		printf("\n\n    Characters Received");
		do
		{
			Status = ReadFile(hComm, &auxchar, sizeof(auxchar), &dwRead, NULL);
			printf("TESTE");
			lpBuf[i] = auxchar;
			i++;
		} while (dwRead > 0);

//------------Printing the RXed String to Console----------------------/

        printf("\n\n    ");
        int j = 0;
        for (j = 0; j < i - 1; j++){	// j < i-1 to remove the dupliated last character
            printf("%c", lpBuf[j]);}

}
CloseHandle(hComm);//Closing the Serial Port
}
