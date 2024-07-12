#include "../Veil.h"

EXTERN_C_START

_IRQL_requires_max_(PASSIVE_LEVEL)
MINCRYPTAPI
NTSTATUS
NTAPI
CiCheckSignedFile(
    _In_ PUCHAR FileHash,
    _In_ ULONG HashLength,
    _In_ ALG_ID HashAlgorithm,
    _In_ PUCHAR CertBuffer,
    _In_ ULONG CertSize,
    _Out_ PMINCRYPT_POLICY_INFO PolicyInfo,
    _Out_opt_ PLARGE_INTEGER SigningTime,
    _Out_opt_ PMINCRYPT_POLICY_INFO TimeStampPolicyInfo
)
{
    UNREFERENCED_PARAMETER(FileHash);
    UNREFERENCED_PARAMETER(HashLength);
    UNREFERENCED_PARAMETER(HashAlgorithm);
    UNREFERENCED_PARAMETER(CertBuffer);
    UNREFERENCED_PARAMETER(CertSize);
    UNREFERENCED_PARAMETER(PolicyInfo);
    UNREFERENCED_PARAMETER(SigningTime);
    UNREFERENCED_PARAMETER(TimeStampPolicyInfo);

    return STATUS_SUCCESS;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
MINCRYPTAPI
NTSTATUS
NTAPI
CiVerifyHashInCatalog(
    _In_ PUCHAR FileHash,
    _In_ ULONG HashLength,
    _In_ ALG_ID HashAlgorithm,
    _In_ ULONG Recheck,
    _In_ ULONG SecureProcess,
    _In_ ULONG AcceptRoots,
    _Out_opt_ PMINCRYPT_POLICY_INFO PolicyInfo,
    _Out_opt_ PUNICODE_STRING CatalogName,
    _Out_opt_ PLARGE_INTEGER SigningTime,
    _Out_opt_ PMINCRYPT_POLICY_INFO TimeStampPolicyInfo
)
{
    UNREFERENCED_PARAMETER(FileHash);
    UNREFERENCED_PARAMETER(HashLength);
    UNREFERENCED_PARAMETER(HashAlgorithm);
    UNREFERENCED_PARAMETER(Recheck);
    UNREFERENCED_PARAMETER(SecureProcess);
    UNREFERENCED_PARAMETER(AcceptRoots);
    UNREFERENCED_PARAMETER(PolicyInfo);
    UNREFERENCED_PARAMETER(CatalogName);
    UNREFERENCED_PARAMETER(SigningTime);
    UNREFERENCED_PARAMETER(TimeStampPolicyInfo);

    return STATUS_SUCCESS;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
MINCRYPTAPI
NTSTATUS
NTAPI
CiValidateFileObject(
    _In_ PFILE_OBJECT FileObject,
    _In_ ULONG SecureRequired,
    _In_ UCHAR RequestedSigningLevel,
    _Out_ PMINCRYPT_POLICY_INFO PolicyInfo,
    _Out_ PMINCRYPT_POLICY_INFO TimeStampPolicyInfo,
    _Out_ PLARGE_INTEGER SigningTime,
    _Out_ PUCHAR FileHash,
    _Inout_ PULONG FileHashSize,
    _Out_ ALG_ID* FileHashAlgorithm
)
{
    UNREFERENCED_PARAMETER(FileObject);
    UNREFERENCED_PARAMETER(SecureRequired);
    UNREFERENCED_PARAMETER(RequestedSigningLevel);
    UNREFERENCED_PARAMETER(PolicyInfo);
    UNREFERENCED_PARAMETER(TimeStampPolicyInfo);
    UNREFERENCED_PARAMETER(SigningTime);
    UNREFERENCED_PARAMETER(FileHash);
    UNREFERENCED_PARAMETER(FileHashSize);
    UNREFERENCED_PARAMETER(FileHashAlgorithm);

    return STATUS_SUCCESS;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
MINCRYPTAPI
PVOID
NTAPI
CiFreePolicyInfo(
    _Inout_ MINCRYPT_POLICY_INFO* PolicyInfo
)
{
    UNREFERENCED_PARAMETER(PolicyInfo);

    return nullptr;
}

typedef
_IRQL_requires_same_
_Function_class_(MINCRYPT_ALLOCATE_ROUTINE)
__drv_allocatesMem(Mem)
PVOID
NTAPI
MINCRYPT_ALLOCATE_ROUTINE (
    _In_ SIZE_T ByteSize
    );
typedef MINCRYPT_ALLOCATE_ROUTINE *PMINCRYPT_ALLOCATE_ROUTINE;

_IRQL_requires_max_(PASSIVE_LEVEL)
MINCRYPTAPI
NTSTATUS
NTAPI
CiGetCertPublisherName(
    _In_ MINCERT_BLOB* Certificate,
    _In_ PMINCRYPT_ALLOCATE_ROUTINE AllocateRoutine,
    _Out_ PUNICODE_STRING PublisherName
)
{
    UNREFERENCED_PARAMETER(Certificate);
    UNREFERENCED_PARAMETER(AllocateRoutine);
    UNREFERENCED_PARAMETER(PublisherName);

    return 0;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
MINCRYPTAPI
VOID
NTAPI
CiSetTrustedOriginClaimId(
    _In_ UINT32 ClaimId
)
{
    UNREFERENCED_PARAMETER(ClaimId);
}

EXTERN_C_END
