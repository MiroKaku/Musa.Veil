#include "../Veil.h"

EXTERN_C_START

_IRQL_requires_max_(PASSIVE_LEVEL)
MINCRYPTAPI
NTSTATUS
NTAPI
CiCheckSignedFile(
    _In_ PVOID                  Hash,
    _In_ UINT32                 HashSize,
    _In_ ALG_ID                 HashAlgId,
    _In_ PVOID                  SecurityDirectory,
    _In_ UINT32                 SizeOfSecurityDirectory,
    _Out_ MINCRYPT_POLICY_INFO* PolicyInfo,
    _Out_ LARGE_INTEGER*        SigningTime,
    _Out_ MINCRYPT_POLICY_INFO* TimeStampPolicyInfo
)
{
    UNREFERENCED_PARAMETER(Hash);
    UNREFERENCED_PARAMETER(HashSize);
    UNREFERENCED_PARAMETER(HashAlgId);
    UNREFERENCED_PARAMETER(SecurityDirectory);
    UNREFERENCED_PARAMETER(SizeOfSecurityDirectory);
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
    _In_ PVOID                  Hash,
    _In_ UINT32                 HashSize,
    _In_ ALG_ID                 HashAlgId,
    _In_ BOOLEAN                IsReloadCatalogs,
    _In_ UINT32                 Always0,                // This is for IsReloadCatalogs, Always0 != 0 ? 16 : 24;
    _In_ UINT32                 Always2007F,
    _Out_ MINCRYPT_POLICY_INFO* PolicyInfo,
    _Out_opt_ UNICODE_STRING*   CatalogName,
    _Out_ LARGE_INTEGER*        SigningTime,
    _Out_ MINCRYPT_POLICY_INFO* TimeStampPolicyInfo
)
{
    UNREFERENCED_PARAMETER(Hash);
    UNREFERENCED_PARAMETER(HashSize);
    UNREFERENCED_PARAMETER(HashAlgId);
    UNREFERENCED_PARAMETER(IsReloadCatalogs);
    UNREFERENCED_PARAMETER(Always0);
    UNREFERENCED_PARAMETER(Always2007F);
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
    _In_ FILE_OBJECT*           FileObject,
    _In_opt_ UINT32             Unkonwn1,   // 0 is a valid value. if it is 4, select sha256
    _In_opt_ UINT32             Unkonwn2,   // 0 is a valid value.
    _Out_ MINCRYPT_POLICY_INFO* PolicyInfo,
    _Out_ MINCRYPT_POLICY_INFO* TimeStampPolicyInfo,
    _Out_ LARGE_INTEGER*        SigningTime,
    _Out_ UINT8*                Hash,
    _Inout_ UINT32*             HashSize,
    _Out_ ALG_ID*               HashAlgId
)
{
    UNREFERENCED_PARAMETER(FileObject);
    UNREFERENCED_PARAMETER(Unkonwn1);
    UNREFERENCED_PARAMETER(Unkonwn2);
    UNREFERENCED_PARAMETER(PolicyInfo);
    UNREFERENCED_PARAMETER(TimeStampPolicyInfo);
    UNREFERENCED_PARAMETER(SigningTime);
    UNREFERENCED_PARAMETER(Hash);
    UNREFERENCED_PARAMETER(HashSize);
    UNREFERENCED_PARAMETER(HashAlgId);

    return STATUS_SUCCESS;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
MINCRYPTAPI
PVOID
NTAPI
CiFreePolicyInfo(
    _In_ MINCRYPT_POLICY_INFO* PolicyInfo
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

MINCRYPTAPI
INT
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
