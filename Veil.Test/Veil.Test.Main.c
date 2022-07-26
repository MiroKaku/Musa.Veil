#include <Veil.h>

#ifdef  _KERNEL_MODE
EXTERN_C NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
    DriverObject;
    RegistryPath;

    return STATUS_SUCCESS;
}
#else
int main(int argc, char* argv[])
{
    argc;
    argv;

    return 0;
}
#endif // if _KERNEL_MODE
