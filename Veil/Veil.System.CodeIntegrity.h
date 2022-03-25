/*
 * PROJECT:   Veil
 * FILE:      Veil.h
 * PURPOSE:   Definition for the Windows Internal API from ntdll.dll,
 *            samlib.dll and winsta.dll
 *
 * LICENSE:   Relicensed under The MIT License from The CC BY 4.0 License
 *
 * DEVELOPER: MiroKaku (50670906+MiroKaku@users.noreply.github.com)
 */

/*
 * PROJECT:   https://github.com/Ido-Moshe-Github/CiDllDemo
 * FILE:      ci.h
 * PURPOSE:   Definition for the ci.dll API and Struct.
 *
 * LICENSE:   Relicensed under The MIT License from The CC BY 4.0 License
 *
 * DEVELOPER: [Ido Moshe, Liron Zuarets]
 * 
 * This file copy from https://github.com/Ido-Moshe-Github/CiDllDemo/blob/master/CiDemoDriver/ci.h
 */

#pragma once

// Warnings which disabled for compiling
#if _MSC_VER >= 1200
#pragma warning(push)
// nonstandard extension used : nameless struct/union
#pragma warning(disable:4201)
// 'struct_name' : structure was padded due to __declspec(align())
#pragma warning(disable:4324)
// 'enumeration': a forward declaration of an unscoped enumeration must have an
// underlying type (int assumed)
#pragma warning(disable:4471)
#endif

VEIL_BEGIN()

//
// WinTrust
//

#ifdef _KERNEL_MODE

/**
 *  This struct was copied from <wintrust.h> and encapsulates a signature used in verifying executable files.
 */
typedef struct _WIN_CERTIFICATE
{
    UINT32       Length;
    UINT16       Revision;
    UINT16       CertificateType;   // WIN_CERT_TYPE_xxx
    UINT8        Certificate[ANYSIZE_ARRAY];

} WIN_CERTIFICATE, * LPWIN_CERTIFICATE, * const LPCWIN_CERTIFICATE;

#define WIN_CERT_REVISION_1_0               (0x0100)
#define WIN_CERT_REVISION_2_0               (0x0200)

#define WIN_CERT_TYPE_X509                  (0x0001)   // bCertificate contains an X.509 Certificate
#define WIN_CERT_TYPE_PKCS_SIGNED_DATA      (0x0002)   // bCertificate contains a PKCS SignedData structure
#define WIN_CERT_TYPE_RESERVED_1            (0x0003)   // Reserved
#define WIN_CERT_TYPE_TS_STACK_SIGNED       (0x0004)   // Terminal Server Protocol Stack Certificate signing

#endif // _KERNEL_MODE

//
// Code Integrity (ci.dll)
//

#ifdef _KERNEL_MODE

/**
 *  Describes the location (address) and size of a ASN.1 blob within a buffer.
 *
 *  @note  The data itself is not contained in the struct.
 */
typedef struct _CI_ASN1_BLOB
{
    UINT32 Size;    // Size of the ASN.1 blob
    PVOID  Data;    // Where the ASN.1 blob starts
} CI_ASN1_BLOB, * PCI_ASN1_BLOB;

/**
 *  Describes the location (address) and size of a certificate subject/issuer name, within a buffer.
 *
 *  @note  The data itself (name) is not contained in the struct.
 *
 *  @note  the reason for separating these fields into their own struct was to match the padding we
 *         observed in CertChainMember struct after the second 'short' field - once you enclose it
 *         into a struct, on x64 bit machines there will be a padding of 4 bytes at the end of the struct,
 *         because the largest member of the struct is of size 8 and it dictates the alignment of the struct.
 */
typedef struct _CI_NAME_BLOB
{
    PVOID Data;     // UTF-8 encode
    short Length;   // Number of bytes  
    short LangId;   // Maybe the language id. 19 for English, 12 for Chinese ?
} CI_NAME_BLOB, * PCI_NAME_BLOB;

/**
 *  Contains various data about a specific certificate in the chain and also points to the actual certificate.
 *
 *  @note  the digest described in this struct is the digest that was used to create the certificate - not for
 *         signing the file.
 *
 *  @note  The size reserved for digest is 64 byte regardless of the digest type, in order to accomodate SHA2/3's
 *         max size of 512bit. The memory is not zeroed, so we must take the actual digestSize into account when
 *         reading it.
 */

#define CI_MAX_DIGEST_LEN  64

typedef struct _CI_CERT_CHAIN_ELEMENT
{
    ALG_ID          AlgId;                              // e.g. CALG_SHA1(0x8004), CALG_SHA_256(0x800C)
    UINT32          DigestSize;                         // e.g. 0x14(160bit) for SHA1, 0x20(256bit) for SHA256
    UINT8           DigestBuffer[CI_MAX_DIGEST_LEN];    // Contains the digest itself, where the digest size is dictated by digestSize

    CI_NAME_BLOB    Subject;                            // Pointer to the subject name
    CI_NAME_BLOB    Issuer;                             // Pointer to the issuer name

    CI_ASN1_BLOB    Certificate;                        // Pointer to actual cert in ASN.1 - including the public key
} CI_CERT_CHAIN_ELEMENT, * PCI_CERT_CHAIN_ELEMENT;

/**
 *  Describes the format of certChainInfo buffer member of PolicyInfo struct. This header maps the types,
 *  locations, and quantities of the data which is contained in the buffer.
 *
 *  @note  when using this struct make sure to check its size first (Size) because it's not guaranteed
 *         that all the fields below will exist.
 */
typedef struct _CI_CERT_INFO_HEADER
{
    // The size of the dynamically allocated buffer
    UINT32          Size;

    // Points to the start of a series of Asn1Blobs which contain the public keys of the certificates in the chain
    CI_ASN1_BLOB*   PublicKeys;
    UINT32          NumberOfPublicKeys;

    // Points to the start of a series of Asn1Blobs which contain the EKUs
    CI_ASN1_BLOB*   EKUs;
    UINT32          NumberOfEKUs;

    // Points to the start of a series of CertChainMembers
    CI_CERT_CHAIN_ELEMENT* CertChain;
    UINT32          NumberOfCertChain;

    // TODO
    UINT32          Unknown;

    // ASN.1 blob of authenticated attributes - spcSpOpusInfo, contentType, etc.
    CI_ASN1_BLOB AuthenticatedAttributes;

    // ... PublicKeys + EKUs + CertChain

} CI_CERT_INFO_HEADER, * PCI_CERT_INFO_HEADER;

typedef struct _CI_CERT_TRUST_STATUS {

    UINT32 ErrorStatus; // CERT_TRUST_xx
    UINT32 InfoStatus;  // CERT_TRUST_xx

} CI_CERT_TRUST_STATUS, * PCI_CERT_TRUST_STATUS;

/**
*  Contains information regarding the certificates that were used for signing/timestamping
*
*  @note  you must check structSize before accessing the other members, since some members were added later.
*
*  @note  all structs members, including the length, are populated by ci functions - no need
*         to fill them in adavnce.
*/
typedef struct _CI_POLICY_INFO
{
    UINT32      Size;
    CI_CERT_TRUST_STATUS TrustStatus;
    CI_CERT_INFO_HEADER* CertChainInfo;     // If not null - contains info about certificate chain
    FILETIME    RevocationDate;             // When was the certificate revoked (if applicable)
    FILETIME    NotBefore;                  // The certificate is not valid before this time
    FILETIME    NotAfter;                   // The certificate is not valid after  this time
} CI_POLICY_INFO, * PCI_POLICY_INFO;

/**
*  Resets a PolicyInfo struct - frees the dynamically allocated buffer in PolicyInfo (CertChainInfo) if not null.
*  Zeros the entire PolicyInfo struct.
*
*  @param  PolicyInfo - the struct to reset.
*
*  @return  the struct which was reset.
*/

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
PVOID
NTAPI
CiFreePolicyInfo(
    _In_ CI_POLICY_INFO* PolicyInfo
);

/**
*  Vista-Win8.1 only. Use CiValidateFileObject on Win10!
* 
*  Given a file digest and signature of a file, verify the signature and provide information regarding
*  the certificates that was used for signing (the entire certificate chain)
*
*  @param  DigestBuffer - buffer containing the digest
*
*  @param  DigestSize - size of the digest, e.g. 0x14(160bit) for SHA1, 0x20(256bit) for SHA256
*
*  @param  DigestAlgId - digest algorithm identifier, e.g. CALG_SHA1(0x8004), CALG_SHA_256(0x800C)
*
*  @param  WinCert - pointer to the start of the security directory
*
*  @param  SizeOfSecurityDirectory - size the security directory
*
*  @param  SignerPolicy[out] - PolicyInfo containing information about the signer certificate chain
*
*  @param  SigningTime[out] - when the file was signed (FILETIME format)
*
*  @param  TimeStampPolicy[out] - PolicyInfo containing information about the timestamping authority (TSA) certificate chain
*
*  @return  0 if the file digest in the signature matches the given digest and the signer cetificate is verified.
*           Various error values otherwise, for example:
*           STATUS_INVALID_IMAGE_HASH - the digest does not match the digest in the signature
*           STATUS_IMAGE_CERT_REVOKED - the certificate used for signing the file is revoked
*           STATUS_IMAGE_CERT_EXPIRED - the certificate used for signing the file has expired
*/

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
CiCheckSignedFile(
    _In_  PVOID DigestBuffer,
    _In_  UINT32  DigestSize,
    _In_  ALG_ID  DigestAlgId,
    _In_  LPCWIN_CERTIFICATE WinCert,
    _In_  UINT32 SizeOfSecurityDirectory,
    _Out_ CI_POLICY_INFO* SignerPolicy,
    _Out_ FILETIME* SigningTime,
    _Out_ CI_POLICY_INFO* TimeStampPolicy
);

/**
* Vista-Win8.1 only. Use CiValidateFileObject on Win10!
* 
* Checks if the SHA-1 message digest is contained within a verified system catalog
*/

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
CiVerifyHashInCatalog(
    _In_  PVOID DigestBuffer,
    _In_  UINT32  DigestSize,
    _In_  ALG_ID  DigestAlgId,
    _In_ UINT32   a4,           // system context?
    _In_ UINT32   Always0,
    _In_ UINT32   Always0x2007F,
    _Out_ CI_POLICY_INFO* SignerPolicy,
    _Out_opt_ UNICODE_STRING* CatalogName,
    _Out_ LARGE_INTEGER* SigningTime,
    _Out_ CI_POLICY_INFO* TimeStampPolicy
);

/**
*  Given a file object, verify the signature and provide information regarding
*  the certificates that was used for signing (the entire certificate chain)
*
*  @param  FileObject[in] - fileObject of the PE in question
*
*  @param  AlgIdFilter[in] - Min digest algorithm identifier? e.g. 0 return any, CALG_SHA1(0x8004) return > 0x8004, CALG_SHA_256(0x800C)
*
*  @param  Unknown[in] - unknown, needs to be reversed. 0 is a valid value.
*
*  @param  SignerPolicy[out] - PolicyInfo containing information about the signer certificate chain
*
*  @param  SigningTime[out] - when the file was signed
*
*  @param  TimeStampPolicy[out] - PolicyInfo containing information about the timestamping
*          authority (TSA) certificate chain
*
*  @param  DigestBuffer[out] - buffer to be filled with the digest, must be at least 64 bytes
*
*  @param  DigestSize[inout] - Size of the digest. Must be at leat CI_MAX_DIGEST_LEN(64) and will be changed by the function to
*                              reflect the actual digest length.
*
*  @param  DigestAlgId[out] - returned digest algorithm identifier, e.g. CALG_SHA1(0x8004), CALG_SHA_256(0x800C)
*
*  @return  0 if the file digest in the signature matches the given digest and the signer cetificate is verified.
*           Various error values otherwise, for example:
*           STATUS_INVALID_IMAGE_HASH - the digest does not match the digest in the signature
*           STATUS_IMAGE_CERT_REVOKED - the certificate used for signing the file is revoked
*           STATUS_IMAGE_CERT_EXPIRED - the certificate used for signing the file has expired
*/

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
CiValidateFileObject(
    _In_        PFILE_OBJECT FileObject,
    _In_opt_    ALG_ID AlgIdFilter,
    _In_opt_    PVOID  Unknown,
    _Out_       CI_POLICY_INFO* SignerPolicy,
    _Out_       CI_POLICY_INFO* TimeStampPolicy,
    _Out_       FILETIME* SigningTime,
    _Out_       PVOID   DigestBuffer,
    _Inout_     UINT32* DigestSize,
    _Out_       ALG_ID* DigestAlgId
);

#endif // _KERNEL_MODE

VEIL_END()

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
