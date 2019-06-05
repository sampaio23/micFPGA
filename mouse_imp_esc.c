
#include<stdlib.h>
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include<winuser.h>

int  main (void)
{
    char   lpBuffer[1] = "1";
	HANDLE hComm;                          // Handle to the Serial port
	char  ComPortName[] = "\\\\.\\COM4";  // Name of the Serial port(May Change) to be opened,
	BOOL  Status;                          // Status of the various operations
	DWORD dwEventMask;                     // Event mask to trigger
	char  TempChar;                        // Temperory Character
	char  SerialBuffer[500000];               // Buffer Containing Rxed Data
	DWORD NoBytesRead;                     // Bytes read by ReadFile()
	int i = 0;
	POINT p;

	FILE *fp;
    int h;
    fp=fopen("arquivo_log.txt","w");
    if(fp==NULL)
    {
        printf("Erro na abertura do arquivo!");
        exit(1);
    }

	printf("\n\n +==========================================+");
	printf("\n |    Serial Port  Reception (Win32 API)    |");
	printf("\n +==========================================+\n");
	//---------------------------------- Opening the Serial Port -------------------------------------------/

	hComm = CreateFile(ComPortName,                  // Name of the Port to be Opened
		GENERIC_READ | GENERIC_WRITE, // Read/Write Access
		0,                            // No Sharing, ports cant be shared
		NULL,                         // No Security
		OPEN_EXISTING,                // Open existing port only
		0,                            // Non Overlapped I/O
		NULL);                        // Null for Comm Devices

	if (hComm == INVALID_HANDLE_VALUE)
		printf("\n    Error! - Port %s can't be opened\n", ComPortName);
	else
		printf("\n    Port %s Opened\n ", ComPortName);

	//------------------------------- Setting the Parameters for the SerialPort ------------------------------/

	DCB dcbSerialParams = { 0 };                         // Initializing DCB structure
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	Status = GetCommState(hComm, &dcbSerialParams);      //retreives  the current settings

	if (Status == FALSE)
		printf("\n    Error! in GetCommState()");

	dcbSerialParams.BaudRate = CBR_9600;      // Setting BaudRate = 9600
	dcbSerialParams.ByteSize = 8;             // Setting ByteSize = 8
	dcbSerialParams.StopBits = ONESTOPBIT;    // Setting StopBits = 1
	dcbSerialParams.Parity = NOPARITY;        // Setting Parity = None

	Status = SetCommState(hComm, &dcbSerialParams);  //Configuring the port according to settings in DCB

	if (Status == FALSE)
	{
		printf("\n    Error! in Setting DCB Structure");
	}
	else //If Successfull display the contents of the DCB Structure
	{
		printf("\n\n    Setting DCB Structure Successfull\n");
		printf("\n       Baudrate = %d", dcbSerialParams.BaudRate);
		printf("\n       ByteSize = %d", dcbSerialParams.ByteSize);
		printf("\n       StopBits = %d", dcbSerialParams.StopBits);
		printf("\n       Parity   = %d", dcbSerialParams.Parity);
	}

	//------------------------------------ Setting Timeouts --------------------------------------------------/

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
		printf("\n\n    Error! in Setting CommMask");
	else
		printf("\n\n    Setting CommMask successfull");


	//------------------------------------ Setting WaitComm() Event   ----------------------------------------/

	printf("\n\n    Waiting for Data Reception");

	Status = WaitCommEvent(hComm, &dwEventMask, NULL); //Wait for the character to be received

	//-------------------------- Program will Wait here till a Character is received ------------------------/

	if (Status == FALSE)
	{
		printf("\n    Error! in Setting WaitCommEvent()");
	}
	else //If  WaitCommEvent()==True Read the RXed data using ReadFile();
	{
		printf("\n\n    Characters Received \n");
		do
		{
			Status = ReadFile(hComm, &TempChar, sizeof(TempChar), &NoBytesRead, NULL);
			SerialBuffer[i] = TempChar;
			GetCursorPos(&p);
            if((unsigned char)TempChar == 64) // Right Arrow Key
                p.x += 1;  // Move Cursor Right
            if((unsigned char)TempChar == 128) // Left Arrow Key
                p.x -= 1;  // Move Cursor Left
            if((unsigned char)TempChar == 192) // Up Arrow Key
                p.y += 1;  // Move Cursor Up
            if((unsigned char)TempChar == 32) // Down Arrow KEy
                p.y -= 1;  // Move Cursor Down
            if((unsigned char) TempChar==16){
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                DWORD  dNoOFBytestoWrite;              // No of bytes to write into the port
                DWORD  dNoOfBytesWritten = 0;          // No of bytes written to the port

                dNoOFBytestoWrite = sizeof(lpBuffer); // Calculating the no of bytes to write into the port

                Status = WriteFile(hComm,               // Handle to the Serialport
                    lpBuffer,            // Data to be written to the port
                    dNoOFBytestoWrite,   // No of bytes to write into the port
                    &dNoOfBytesWritten,  // No of bytes written to the port
                    NULL);

                if (Status == TRUE)
                    printf("\n\n    %s - Written to %s", lpBuffer, ComPortName);
                else
                    printf("\n\n   Error %d in Writing to Serial Port", GetLastError());

            }




    SetCursorPos(p.x,p.y);

			i++;

		} while (NoBytesRead > 0);



		//------------Printing the RXed String to Console----------------------/

		//printf("\n\n    ");
		int j = 0;
		for (j = 0; j < i - 1; j++)
        {// j < i-1 to remove the dupliated last character
			printf("%x\t%u\n", SerialBuffer[j],(unsigned char) SerialBuffer[j]);
			fprintf(fp,"%u\n",(unsigned char)SerialBuffer[j]);
        }

	}

	CloseHandle(hComm);//Closing the Serial Port
	fclose(fp);
	printf("\n +==========================================+\n");

	//getchar();
}//End of Main()

