#include <windows.h>

HANDLE manip_hiddll,manip_setupapidll;		/* manipuladores das DLLs */

typedef struct {
BYTE longid[16];
} GU_ID;

typedef struct {
int tamanho;
GU_ID classe;
int flags;
int *reserv;
} DEVICE_INTERFACE_DATA;

typedef struct {
int tamanho;
char path[256];
} DEVICE_INTERFACE_DETAIL;

typedef struct {
int tamanho;
int idfabricanteproduto;
USHORT versao;
char serial[10];
} HIDD_ATTRIBUTES;

void(__stdcall *pHidD_GetHidGuid)(GU_ID *);
HANDLE(__stdcall *pSetupDiGetClassDevs)(GU_ID *, char *, int, int);
BOOL(__stdcall *pSetupDiEnumDeviceInterfaces)(HANDLE, int *, GU_ID *, int, DEVICE_INTERFACE_DATA *);
BOOL(__stdcall *pSetupDiGetDeviceInterfaceDetail)(HANDLE, DEVICE_INTERFACE_DATA *, DEVICE_INTERFACE_DETAIL *, int, int *, int);
BOOL(__stdcall *pHidD_GetAttributes)(HANDLE, HIDD_ATTRIBUTES *);
BOOL(__stdcall *pHidD_GetManufacturerString)(HANDLE, char *, int);
BOOL(__stdcall *pHidD_GetProductString)(HANDLE, char *, int);
BOOL(__stdcall *pHidD_GetIndexedString)(HANDLE, int, char *, int);
BOOL(__stdcall *pHidD_GetPreparsedData)(HANDLE, BYTE *);
BOOL(__stdcall *pHidD_GetSerialNumberString)(HANDLE, char *, int);
BOOL(__stdcall *pHidD_GetConfiguration)(HANDLE, BYTE *, int);
BOOL(__stdcall *pHidD_SetConfiguration)(HANDLE, BYTE *, int);
BOOL(__stdcall *pHidD_GetPhysicalDescriptor)(HANDLE, BYTE *, int);

BOOL Carrega_Rotinas_API_USB(void)
	{
		manip_hiddll = LoadLibrary("hid.dll");
		if (manip_hiddll == NULL) return(FALSE);
		manip_setupapidll = LoadLibrary("setupapi.dll");
		if (manip_setupapidll == NULL) return(FALSE);
}
