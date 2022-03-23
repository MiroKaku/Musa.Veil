#include <Veil.h>

#ifdef  _KERNEL_MODE
EXTERN_C NTSTATUS DriverEntry(PDRIVER_OBJECT /*DriverObject*/, PUNICODE_STRING /*RegistryPath*/)
#else
int main(int /*argc*/, char* /*argv*/[])
#endif //  _KERNEL_MODE
{

    return STATUS_SUCCESS;
}
