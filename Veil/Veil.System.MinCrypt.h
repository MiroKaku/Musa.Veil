/*
 * PROJECT:   Veil
 * FILE:      Veil.System.MinCrypt.h
 * PURPOSE:   This file is part of Veil.
 *
 * LICENSE:   MIT License
 *
 * DEVELOPER: MiroKaku (kkmi04@outlook.com)
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

#ifdef _KERNEL_MODE

#ifndef _MINCRYPT_LIB
#define MINCRYPTAPI __declspec(dllimport)
#else
#define MINCRYPTAPI
#endif

//
// Algorithm IDs and Flags
//

// ALG_ID crackers
#define GET_ALG_CLASS(x)                (x & (7 << 13))
#define GET_ALG_TYPE(x)                 (x & (15 << 9))
#define GET_ALG_SID(x)                  (x & (511))

// Algorithm classes
// certenrolld_begin -- ALG_CLASS_*
#define ALG_CLASS_ANY                   (0)
#define ALG_CLASS_SIGNATURE             (1 << 13)
#define ALG_CLASS_MSG_ENCRYPT           (2 << 13)
#define ALG_CLASS_DATA_ENCRYPT          (3 << 13)
#define ALG_CLASS_HASH                  (4 << 13)
#define ALG_CLASS_KEY_EXCHANGE          (5 << 13)
#define ALG_CLASS_ALL                   (7 << 13)
// certenrolld_end

// Algorithm types
#define ALG_TYPE_ANY                    (0)
#define ALG_TYPE_DSS                    (1 << 9)
#define ALG_TYPE_RSA                    (2 << 9)
#define ALG_TYPE_BLOCK                  (3 << 9)
#define ALG_TYPE_STREAM                 (4 << 9)
#define ALG_TYPE_DH                     (5 << 9)
#define ALG_TYPE_SECURECHANNEL          (6 << 9)
#define ALG_TYPE_ECDH                   (7 << 9)
#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)
#define ALG_TYPE_THIRDPARTY             (8 << 9)
#endif //(NTDDI_VERSION >= NTDDI_WIN10_RS1)

// Generic sub-ids
#define ALG_SID_ANY                     (0)

// Generic ThirdParty sub-ids
#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)
#define ALG_SID_THIRDPARTY_ANY          (0)
#endif //(NTDDI_VERSION >= NTDDI_WIN10_RS1)

// Some RSA sub-ids
#define ALG_SID_RSA_ANY                 0
#define ALG_SID_RSA_PKCS                1
#define ALG_SID_RSA_MSATWORK            2
#define ALG_SID_RSA_ENTRUST             3
#define ALG_SID_RSA_PGP                 4

// Some DSS sub-ids
//
#define ALG_SID_DSS_ANY                 0
#define ALG_SID_DSS_PKCS                1
#define ALG_SID_DSS_DMS                 2
#define ALG_SID_ECDSA                   3

// Block cipher sub ids
// DES sub_ids
#define ALG_SID_DES                     1
#define ALG_SID_3DES                    3
#define ALG_SID_DESX                    4
#define ALG_SID_IDEA                    5
#define ALG_SID_CAST                    6
#define ALG_SID_SAFERSK64               7
#define ALG_SID_SAFERSK128              8
#define ALG_SID_3DES_112                9
#define ALG_SID_CYLINK_MEK              12
#define ALG_SID_RC5                     13
#define ALG_SID_AES_128                 14
#define ALG_SID_AES_192                 15
#define ALG_SID_AES_256                 16
#define ALG_SID_AES                     17

// Fortezza sub-ids
#define ALG_SID_SKIPJACK                10
#define ALG_SID_TEK                     11

// KP_MODE
#define CRYPT_MODE_CBCI                 6       // ANSI CBC Interleaved
#define CRYPT_MODE_CFBP                 7       // ANSI CFB Pipelined
#define CRYPT_MODE_OFBP                 8       // ANSI OFB Pipelined
#define CRYPT_MODE_CBCOFM               9       // ANSI CBC + OF Masking
#define CRYPT_MODE_CBCOFMI              10      // ANSI CBC + OFM Interleaved

// RC2 sub-ids
#define ALG_SID_RC2                     2

// Stream cipher sub-ids
#define ALG_SID_RC4                     1
#define ALG_SID_SEAL                    2

// Diffie-Hellman sub-ids
#define ALG_SID_DH_SANDF                1
#define ALG_SID_DH_EPHEM                2
#define ALG_SID_AGREED_KEY_ANY          3
#define ALG_SID_KEA                     4
#define ALG_SID_ECDH                    5
#define ALG_SID_ECDH_EPHEM              6

// Hash sub ids
#define ALG_SID_MD2                     1
#define ALG_SID_MD4                     2
#define ALG_SID_MD5                     3
#define ALG_SID_SHA                     4
#define ALG_SID_SHA1                    4
#define ALG_SID_MAC                     5
#define ALG_SID_RIPEMD                  6
#define ALG_SID_RIPEMD160               7
#define ALG_SID_SSL3SHAMD5              8
#define ALG_SID_HMAC                    9
#define ALG_SID_TLS1PRF                 10
#define ALG_SID_HASH_REPLACE_OWF        11
#define ALG_SID_SHA_256                 12
#define ALG_SID_SHA_384                 13
#define ALG_SID_SHA_512                 14

// secure channel sub ids
#define ALG_SID_SSL3_MASTER             1
#define ALG_SID_SCHANNEL_MASTER_HASH    2
#define ALG_SID_SCHANNEL_MAC_KEY        3
#define ALG_SID_PCT1_MASTER             4
#define ALG_SID_SSL2_MASTER             5
#define ALG_SID_TLS1_MASTER             6
#define ALG_SID_SCHANNEL_ENC_KEY        7

// misc ECC sub ids
#define ALG_SID_ECMQV                   1

// Our silly example sub-id
#define ALG_SID_EXAMPLE                 80

// certenrolls_begin -- PROV_ENUMALGS_EX
#ifndef ALGIDDEF
#define ALGIDDEF
typedef unsigned int ALG_ID;
#endif
// certenrolls_end

// algorithm identifier definitions
#define CALG_MD2                (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_MD2)
#define CALG_MD4                (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_MD4)
#define CALG_MD5                (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_MD5)
#define CALG_SHA                (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_SHA)
#define CALG_SHA1               (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_SHA1)
#define CALG_MAC                (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_MAC)           // Deprecated. Don't use.
#define CALG_RSA_SIGN           (ALG_CLASS_SIGNATURE | ALG_TYPE_RSA | ALG_SID_RSA_ANY)
#define CALG_DSS_SIGN           (ALG_CLASS_SIGNATURE | ALG_TYPE_DSS | ALG_SID_DSS_ANY)
#define CALG_NO_SIGN            (ALG_CLASS_SIGNATURE | ALG_TYPE_ANY | ALG_SID_ANY)
#define CALG_RSA_KEYX           (ALG_CLASS_KEY_EXCHANGE|ALG_TYPE_RSA|ALG_SID_RSA_ANY)
#define CALG_DES                (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_DES)
#define CALG_3DES_112           (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_3DES_112)
#define CALG_3DES               (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_3DES)
#define CALG_DESX               (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_DESX)
#define CALG_RC2                (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_RC2)
#define CALG_RC4                (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_STREAM|ALG_SID_RC4)
#define CALG_SEAL               (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_STREAM|ALG_SID_SEAL)
#define CALG_DH_SF              (ALG_CLASS_KEY_EXCHANGE|ALG_TYPE_DH|ALG_SID_DH_SANDF)
#define CALG_DH_EPHEM           (ALG_CLASS_KEY_EXCHANGE|ALG_TYPE_DH|ALG_SID_DH_EPHEM)
#define CALG_AGREEDKEY_ANY      (ALG_CLASS_KEY_EXCHANGE|ALG_TYPE_DH|ALG_SID_AGREED_KEY_ANY)
#define CALG_KEA_KEYX           (ALG_CLASS_KEY_EXCHANGE|ALG_TYPE_DH|ALG_SID_KEA)
#define CALG_HUGHES_MD5         (ALG_CLASS_KEY_EXCHANGE|ALG_TYPE_ANY|ALG_SID_MD5)
#define CALG_SKIPJACK           (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_SKIPJACK)
#define CALG_TEK                (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_TEK)
#define CALG_CYLINK_MEK         (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_CYLINK_MEK)  // Deprecated. Do not use
#define CALG_SSL3_SHAMD5        (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_SSL3SHAMD5)
#define CALG_SSL3_MASTER        (ALG_CLASS_MSG_ENCRYPT|ALG_TYPE_SECURECHANNEL|ALG_SID_SSL3_MASTER)
#define CALG_SCHANNEL_MASTER_HASH   (ALG_CLASS_MSG_ENCRYPT|ALG_TYPE_SECURECHANNEL|ALG_SID_SCHANNEL_MASTER_HASH)
#define CALG_SCHANNEL_MAC_KEY   (ALG_CLASS_MSG_ENCRYPT|ALG_TYPE_SECURECHANNEL|ALG_SID_SCHANNEL_MAC_KEY)
#define CALG_SCHANNEL_ENC_KEY   (ALG_CLASS_MSG_ENCRYPT|ALG_TYPE_SECURECHANNEL|ALG_SID_SCHANNEL_ENC_KEY)
#define CALG_PCT1_MASTER        (ALG_CLASS_MSG_ENCRYPT|ALG_TYPE_SECURECHANNEL|ALG_SID_PCT1_MASTER)
#define CALG_SSL2_MASTER        (ALG_CLASS_MSG_ENCRYPT|ALG_TYPE_SECURECHANNEL|ALG_SID_SSL2_MASTER)
#define CALG_TLS1_MASTER        (ALG_CLASS_MSG_ENCRYPT|ALG_TYPE_SECURECHANNEL|ALG_SID_TLS1_MASTER)
#define CALG_RC5                (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_RC5)
#define CALG_HMAC               (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_HMAC)
#define CALG_TLS1PRF            (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_TLS1PRF)
#define CALG_HASH_REPLACE_OWF   (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_HASH_REPLACE_OWF)
#define CALG_AES_128            (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_AES_128)
#define CALG_AES_192            (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_AES_192)
#define CALG_AES_256            (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_AES_256)
#define CALG_AES                (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_AES)
#define CALG_SHA_256            (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_SHA_256)
#define CALG_SHA_384            (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_SHA_384)
#define CALG_SHA_512            (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_SHA_512)
#define CALG_ECDH               (ALG_CLASS_KEY_EXCHANGE | ALG_TYPE_DH | ALG_SID_ECDH)
#define CALG_ECDH_EPHEM         (ALG_CLASS_KEY_EXCHANGE | ALG_TYPE_ECDH | ALG_SID_ECDH_EPHEM)
#define CALG_ECMQV              (ALG_CLASS_KEY_EXCHANGE | ALG_TYPE_ANY | ALG_SID_ECMQV)
#define CALG_ECDSA              (ALG_CLASS_SIGNATURE | ALG_TYPE_DSS | ALG_SID_ECDSA)
#define CALG_NULLCIPHER         (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_ANY | 0)
#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)
#define CALG_THIRDPARTY_KEY_EXCHANGE    (ALG_CLASS_KEY_EXCHANGE | ALG_TYPE_THIRDPARTY | ALG_SID_THIRDPARTY_ANY)
#define CALG_THIRDPARTY_SIGNATURE       (ALG_CLASS_SIGNATURE    | ALG_TYPE_THIRDPARTY | ALG_SID_THIRDPARTY_ANY)
#define CALG_THIRDPARTY_CIPHER          (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_THIRDPARTY | ALG_SID_THIRDPARTY_ANY)
#define CALG_THIRDPARTY_HASH            (ALG_CLASS_HASH         | ALG_TYPE_THIRDPARTY | ALG_SID_THIRDPARTY_ANY)
#endif //(NTDDI_VERSION >= NTDDI_WIN10_RS1)

#include <pshpack8.h>
typedef struct _MINCRYPTOAPI_BLOB
{
    UINT32 Size;
    _Field_size_bytes_(Size)  UINT8* Data;

} MINCRYPT_INTEGER_BLOB, * PMINCRYPT_INTEGER_BLOB,
MINCRYPT_UINT_BLOB, * PMINCRYPT_UINT_BLOB,
MINCRYPT_OBJID_BLOB, * PMINCRYPT_OBJID_BLOB,
MINCERT_NAME_BLOB, * PMINCERT_NAME_BLOB,
MINCERT_RDN_VALUE_BLOB, * PMINCERT_RDN_VALUE_BLOB,
MINCERT_BLOB, * PMINCERT_BLOB,
MINCRL_BLOB, * PMINCRL_BLOB,
MINCRYPT_DATA_BLOB, * PMINCRYPT_DATA_BLOB,
MINCRYPT_HASH_BLOB, * PMINCRYPT_HASH_BLOB,
MINCRYPT_DIGEST_BLOB, * PMINCRYPT_DIGEST_BLOB,
MINCRYPT_DER_BLOB, * PMINCRYPT_DER_BLOB,
MINCRYPT_ATTR_BLOB, * PMINCRYPT_ATTR_BLOB;

typedef struct _MINCRYPT_NAME_BLOB
{
    _Field_size_bytes_(Size)  PCHAR Data;
    USHORT Size;

}MINCRYPT_NAME_BLOB, * PMINCRYPT_NAME_BLOB;

#define MINCRYPT_MAX_HASH_LENGTH    (64)
#define MINCRYPT_SHA1_LENGTH        (160/8)
#define MINCRYPT_SHA256_LENGTH      (256/8)

typedef struct _MINCRYPT_CHAIN_ELEMENT
{
    ALG_ID          HashAlgId;  // CALG_SHA1,       CALG_SHA_256
    UINT32          HashSize;   // SHA1(160bit/8),  SHA256(256bit/8)
    UINT8           Hash[MINCRYPT_MAX_HASH_LENGTH];

    MINCRYPT_NAME_BLOB Subject;
    MINCRYPT_NAME_BLOB Issuer;

    MINCERT_BLOB    Certificate;

}MINCRYPT_CHAIN_ELEMENT, * PMINCRYPT_CHAIN_ELEMENT;

typedef struct _MINCRYPT_CHAIN_INFO
{
    UINT32          Size;

    MINCERT_BLOB*   PublicKeys;
    UINT32          NumberOfPublicKeys;

    MINCERT_BLOB*   EKUs;
    UINT32          NumberOfEKUs;

#if (NTDDI_VERSION >= NTDDI_WIN10)

    PMINCRYPT_CHAIN_ELEMENT ChainElements;
    UINT32          NumberOfChainElement;

    // ASN.1 blob of authenticated attributes - spcSpOpusInfo, contentType, etc.
    MINCRYPT_ATTR_BLOB AuthenticodeAttributes;

    // UINT8 Hash[32];

#endif // NTDDI_VERSION >= NTDDI_WIN10

    /* memory layout */

    // EKUs[NumberOfEKUs]

    // PublicKeys[NumberOfPublicKeys]

    // AuthenticodeAttributes.Data[AuthenticodeAttributes.Size]

    // ChainElements[NumberOfChainElement]

}MINCRYPT_CHAIN_INFO, * PMINCRYPT_CHAIN_INFO;

typedef struct _MINCRYPT_POLICY_INFO
{
    UINT32          Size;
    UINT32          VerificationStatus;
    UINT32          PolicyBits;

    MINCRYPT_CHAIN_INFO* ChainInfo;

    LARGE_INTEGER   RevocationTime;     // When was the certificate revoked (if applicable)

#if (NTDDI_VERSION >= NTDDI_WIN10)

    LARGE_INTEGER   NotBefore;          // The certificate is not valid before this time
    LARGE_INTEGER   NotAfter;           // The certificate is not valid after  this time

#endif // NTDDI_VERSION >= NTDDI_WIN10

}MINCRYPT_POLICY_INFO, * PMINCRYPT_POLICY_INFO;
#include <poppack.h>


/**
*  Resets a PolicyInfo struct - frees the dynamically allocated buffer in PolicyInfo (ChainInfo) if not null.
*  Zeros the entire PolicyInfo struct.
*
*  @param  PolicyInfo - the struct to reset.
*
*  @return the struct which was reset.
*/
_IRQL_requires_max_(PASSIVE_LEVEL)
MINCRYPTAPI
PVOID
NTAPI
CiFreePolicyInfo(
    _Inout_ MINCRYPT_POLICY_INFO* PolicyInfo
);


/**
*  Win7SP1-Win8.1 only (KB3033929 installed). Use CiValidateFileObject on Win10!
*
*  Given a file digest and signature of a file, verify the signature and provide information regarding
*  the certificates that was used for signing (the entire certificate chain)
*
*  @note   must be attached to the PsInitialSystemProcess first!
*
*  @param  Hash - buffer containing the digest
*
*  @param  HashSize - size of the digest, e.g. 0x14(160bit) for SHA1, 0x20(256bit) for SHA256
*
*  @param  HashAlgId - digest algorithm identifier, e.g. CALG_SHA1(0x8004), CALG_SHA_256(0x800C)
*
*  @param  SecurityDirectory - pointer to the start of the security directory
*
*  @param  SizeOfSecurityDirectory - size the security directory
*
*  @param  PolicyInfo[out] - PolicyInfo containing information about the signer certificate chain
*
*  @param  SigningTime[out] - when the file was signed (FILETIME format)
*
*  @param  TimeStampPolicyInfo[out] - PolicyInfo containing information about the timestamping authority (TSA) certificate chain
*
*  @return STATUS_SUCCESS if the file digest in the signature matches the given digest and the signer cetificate is verified.
*           Various error values otherwise, for example:
*           STATUS_INVALID_IMAGE_HASH - the digest does not match the digest in the signature
*           STATUS_IMAGE_CERT_REVOKED - the certificate used for signing the file is revoked
*           STATUS_IMAGE_CERT_EXPIRED - the certificate used for signing the file has expired
*/
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
    _Out_ LARGE_INTEGER* SigningTime,
    _Out_ MINCRYPT_POLICY_INFO* TimeStampPolicyInfo
);


/**
*  Win7SP1-Win8.1 only (KB3033929 installed). Use CiValidateFileObject on Win10!
*
*  Checks if the SHA-1 message digest is contained within a verified system catalog
*
*  @note   must be attached to the PsInitialSystemProcess first!
*
*  @param  Hash - buffer containing the digest
*
*  @param  HashSize - size of the digest, e.g. 0x14(160bit) for SHA1, 0x20(256bit) for SHA256
*
*  @param  HashAlgId - digest algorithm identifier, e.g. CALG_SHA1(0x8004), CALG_SHA_256(0x800C)
*
*  @param  IsReloadCatalogs - is reload catalogs cache.
*
*  @param  Always0 - this is for IsReloadCatalogs, Always0 != 0 ? 16 : 24;
* 
*  @param  Always2007F - unknown, always 0x2007F, maybe a mask.
*
*  @param  PolicyInfo[out] - PolicyInfo containing information about the signer certificate chain.
*
*  @param  CatalogName[out option] - catalog file name.
* 
*  @param  SigningTime[out] - when the file was signed (FILETIME format)
*
*  @param  TimeStampPolicyInfo[out] - PolicyInfo containing information about the timestamping authority (TSA) certificate chain.
*
*  @return STATUS_SUCCESS if the file digest in the signature matches the given digest and the signer cetificate is verified.
*           Various error values otherwise, for example:
*           STATUS_INVALID_IMAGE_HASH - the digest does not match the digest in the signature
*           STATUS_IMAGE_CERT_REVOKED - the certificate used for signing the file is revoked
*           STATUS_IMAGE_CERT_EXPIRED - the certificate used for signing the file has expired
*/
_IRQL_requires_max_(PASSIVE_LEVEL)
MINCRYPTAPI
NTSTATUS
NTAPI
CiVerifyHashInCatalog(
    _In_ PVOID                  Hash,
    _In_ UINT32                 HashSize,
    _In_ ALG_ID                 HashAlgId,
    _In_ BOOLEAN                IsReloadCatalogs,
    _In_ UINT32                 Always0,
    _In_ UINT32                 Always2007F,
    _Out_ MINCRYPT_POLICY_INFO* PolicyInfo,
    _Out_opt_ UNICODE_STRING*   CatalogName,
    _Out_ LARGE_INTEGER*        SigningTime,
    _Out_ MINCRYPT_POLICY_INFO* TimeStampPolicyInfo
);


#if (NTDDI_VERSION >= NTDDI_WIN10)

typedef
_IRQL_requires_same_
_Function_class_(MINCRYPT_ALLOCATE_ROUTINE)
__drv_allocatesMem(Mem)
PVOID
NTAPI
MINCRYPT_ALLOCATE_ROUTINE(
    _In_ SIZE_T ByteSize
);
typedef MINCRYPT_ALLOCATE_ROUTINE* PMINCRYPT_ALLOCATE_ROUTINE;

/**
*  Parse the publisher name from the certificate
*
*  @param  Certificate - &PolicyInfo.ChainInfo->ChainElements[x].Certificate
*
*  @param  AllocateRoutine - used to allocate PublisherName buffer.
*
*  @param  PublisherName[out] - publisher name.
*
*  @return buffer length.
*/
MINCRYPTAPI
NTSTATUS
NTAPI
CiGetCertPublisherName(
    _In_ MINCERT_BLOB* Certificate,
    _In_ PMINCRYPT_ALLOCATE_ROUTINE AllocateRoutine,
    _Out_ PUNICODE_STRING PublisherName
);


MINCRYPTAPI
VOID
NTAPI
CiSetTrustedOriginClaimId(
    _In_ UINT32 ClaimId
);

/**
*  Given a file object, verify the signature and provide information regarding
*   the certificates that was used for signing (the entire certificate chain)
*
*  @param  FileObject - FileObject of the PE in question
*
*  @param  Unkonwn1 - unknown, 0 is a valid value. (Unkonwn1 and Unkonwn2 together calculate the minimum support algorithm)
*
*  @param  Unkonwn2 - unknown, 0 is a valid value. (^ the words above refer to 'CipGetHashAlgorithmForLegacyScenario')
*
*  @param  PolicyInfo[out] - PolicyInfo containing information about the signer certificate chain.
*
*  @param  TimeStampPolicyInfo[out] - PolicyInfo containing information about the timestamping authority (TSA) certificate chain.
*
*  @param  SigningTime[out] - when the file was signed (FILETIME format)
*
*  @param  Hash - buffer containing the digest
*
*  @param  HashSize - size of the digest, e.g. 0x14(160bit) for SHA1, 0x20(256bit) for SHA256
*
*  @param  HashAlgId - digest algorithm identifier, e.g. CALG_SHA1(0x8004), CALG_SHA_256(0x800C)
*
*  @return STATUS_SUCCESS if the file digest in the signature matches the given digest and the signer cetificate is verified.
*           Various error values otherwise, for example:
*           STATUS_INVALID_IMAGE_HASH - the digest does not match the digest in the signature
*           STATUS_IMAGE_CERT_REVOKED - the certificate used for signing the file is revoked
*           STATUS_IMAGE_CERT_EXPIRED - the certificate used for signing the file has expired
*/
_IRQL_requires_max_(PASSIVE_LEVEL)
MINCRYPTAPI
NTSTATUS
NTAPI
CiValidateFileObject(
    _In_ FILE_OBJECT*           FileObject,
    _In_opt_ UINT32             Unkonwn1,
    _In_opt_ UINT32             Unkonwn2,
    _Out_ MINCRYPT_POLICY_INFO* PolicyInfo,
    _Out_ MINCRYPT_POLICY_INFO* TimeStampPolicyInfo,
    _Out_ LARGE_INTEGER*        SigningTime,
    _Out_ UINT8*                Hash,
    _Inout_ UINT32*             HashSize,
    _Out_ ALG_ID*               HashAlgId
);

#endif // NTDDI_VERSION >= NTDDI_WIN10

#endif // _KERNEL_MODE

VEIL_END()

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
