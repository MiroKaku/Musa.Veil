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
 * PROJECT:   Mouri's Internal NT API Collections (MINT)
 * FILE:      MINT.h
 * PURPOSE:   Definition for the Windows Internal API from ntdll.dll,
 *            samlib.dll and winsta.dll
 *
 * LICENSE:   Relicensed under The MIT License from The CC BY 4.0 License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

/*
 * This file is part of the Process Hacker project - https://processhacker.sf.io/
 *
 * You can redistribute this file and/or modify it under the terms of the
 * Attribution 4.0 International (CC BY 4.0) license.
 *
 * You must give appropriate credit, provide a link to the license, and
 * indicate if changes were made. You may do so in any reasonable manner, but
 * not in any way that suggests the licensor endorses you or your use.
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
#if (NTDDI_VERSION >= NTDDI_VISTA)
#define ALG_TYPE_ECDH                   (7 << 9)
#endif //(NTDDI_VERSION >= NTDDI_VISTA)
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
#if (NTDDI_VERSION >= NTDDI_VISTA)
#define ALG_SID_ECDSA                   3
#endif //(NTDDI_VERSION >= NTDDI_VISTA)

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
#if (NTDDI_VERSION >= NTDDI_WINXP)
#define ALG_SID_AES_128                 14
#define ALG_SID_AES_192                 15
#define ALG_SID_AES_256                 16
#define ALG_SID_AES                     17
#endif //(NTDDI_VERSION >= NTDDI_WINXP)

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
#if (NTDDI_VERSION >= NTDDI_VISTA)
#define ALG_SID_ECDH                    5
#define ALG_SID_ECDH_EPHEM              6
#endif //(NTDDI_VERSION >= NTDDI_VISTA)

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
#if (NTDDI_VERSION >= NTDDI_WINXP)
#define ALG_SID_HASH_REPLACE_OWF        11
#endif //(NTDDI_VERSION >= NTDDI_WINXP)
#if (NTDDI_VERSION > NTDDI_WINXPSP2)
#define ALG_SID_SHA_256                 12
#define ALG_SID_SHA_384                 13
#define ALG_SID_SHA_512                 14
#endif //(NTDDI_VERSION > NTDDI_WINXPSP2)

// secure channel sub ids
#define ALG_SID_SSL3_MASTER             1
#define ALG_SID_SCHANNEL_MASTER_HASH    2
#define ALG_SID_SCHANNEL_MAC_KEY        3
#define ALG_SID_PCT1_MASTER             4
#define ALG_SID_SSL2_MASTER             5
#define ALG_SID_TLS1_MASTER             6
#define ALG_SID_SCHANNEL_ENC_KEY        7

#if (NTDDI_VERSION >= NTDDI_VISTA)
// misc ECC sub ids
#define ALG_SID_ECMQV                   1
#endif //(NTDDI_VERSION >= NTDDI_VISTA)

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
#if (NTDDI_VERSION >= NTDDI_WINXP)
#define CALG_NO_SIGN            (ALG_CLASS_SIGNATURE | ALG_TYPE_ANY | ALG_SID_ANY)
#endif //(NTDDI_VERSION >= NTDDI_WINXP)
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
#if (NTDDI_VERSION >= NTDDI_WINXP)
#define CALG_HASH_REPLACE_OWF   (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_HASH_REPLACE_OWF)
#define CALG_AES_128            (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_AES_128)
#define CALG_AES_192            (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_AES_192)
#define CALG_AES_256            (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_AES_256)
#define CALG_AES                (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_AES)
#endif //(NTDDI_VERSION >= NTDDI_WINXP)
#if (NTDDI_VERSION > NTDDI_WINXPSP2)
#define CALG_SHA_256            (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_SHA_256)
#define CALG_SHA_384            (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_SHA_384)
#define CALG_SHA_512            (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_SHA_512)
#endif //(NTDDI_VERSION > NTDDI_WINXPSP2)
#if (NTDDI_VERSION >= NTDDI_VISTA)
#define CALG_ECDH               (ALG_CLASS_KEY_EXCHANGE | ALG_TYPE_DH | ALG_SID_ECDH)
#define CALG_ECDH_EPHEM         (ALG_CLASS_KEY_EXCHANGE | ALG_TYPE_ECDH | ALG_SID_ECDH_EPHEM)
#define CALG_ECMQV              (ALG_CLASS_KEY_EXCHANGE | ALG_TYPE_ANY | ALG_SID_ECMQV)
#define CALG_ECDSA              (ALG_CLASS_SIGNATURE | ALG_TYPE_DSS | ALG_SID_ECDSA)
#define CALG_NULLCIPHER         (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_ANY | 0)
#endif //(NTDDI_VERSION >= NTDDI_VISTA)
#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)
#define CALG_THIRDPARTY_KEY_EXCHANGE    (ALG_CLASS_KEY_EXCHANGE | ALG_TYPE_THIRDPARTY | ALG_SID_THIRDPARTY_ANY)
#define CALG_THIRDPARTY_SIGNATURE       (ALG_CLASS_SIGNATURE    | ALG_TYPE_THIRDPARTY | ALG_SID_THIRDPARTY_ANY)
#define CALG_THIRDPARTY_CIPHER          (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_THIRDPARTY | ALG_SID_THIRDPARTY_ANY)
#define CALG_THIRDPARTY_HASH            (ALG_CLASS_HASH         | ALG_TYPE_THIRDPARTY | ALG_SID_THIRDPARTY_ANY)
#endif //(NTDDI_VERSION >= NTDDI_WIN10_RS1)

//
// The following are error status bits
//

// These can be applied to certificates and chains

#define CERT_TRUST_NO_ERROR                             0x00000000
#define CERT_TRUST_IS_NOT_TIME_VALID                    0x00000001
#define CERT_TRUST_IS_NOT_TIME_NESTED                   0x00000002
#define CERT_TRUST_IS_REVOKED                           0x00000004
#define CERT_TRUST_IS_NOT_SIGNATURE_VALID               0x00000008
#define CERT_TRUST_IS_NOT_VALID_FOR_USAGE               0x00000010
#define CERT_TRUST_IS_UNTRUSTED_ROOT                    0x00000020
#define CERT_TRUST_REVOCATION_STATUS_UNKNOWN            0x00000040
#define CERT_TRUST_IS_CYCLIC                            0x00000080

#define CERT_TRUST_INVALID_EXTENSION                    0x00000100
#define CERT_TRUST_INVALID_POLICY_CONSTRAINTS           0x00000200
#define CERT_TRUST_INVALID_BASIC_CONSTRAINTS            0x00000400
#define CERT_TRUST_INVALID_NAME_CONSTRAINTS             0x00000800
#define CERT_TRUST_HAS_NOT_SUPPORTED_NAME_CONSTRAINT    0x00001000

// In LH, this error will never be set.
#define CERT_TRUST_HAS_NOT_DEFINED_NAME_CONSTRAINT      0x00002000

#define CERT_TRUST_HAS_NOT_PERMITTED_NAME_CONSTRAINT    0x00004000
#define CERT_TRUST_HAS_EXCLUDED_NAME_CONSTRAINT         0x00008000

#define CERT_TRUST_IS_OFFLINE_REVOCATION                0x01000000
#define CERT_TRUST_NO_ISSUANCE_CHAIN_POLICY             0x02000000
#define CERT_TRUST_IS_EXPLICIT_DISTRUST                 0x04000000
#define CERT_TRUST_HAS_NOT_SUPPORTED_CRITICAL_EXT       0x08000000
#define CERT_TRUST_HAS_WEAK_SIGNATURE                   0x00100000
#define CERT_TRUST_HAS_WEAK_HYGIENE                     0x00200000

// These can be applied to chains only

#define CERT_TRUST_IS_PARTIAL_CHAIN                     0x00010000
#define CERT_TRUST_CTL_IS_NOT_TIME_VALID                0x00020000
#define CERT_TRUST_CTL_IS_NOT_SIGNATURE_VALID           0x00040000
#define CERT_TRUST_CTL_IS_NOT_VALID_FOR_USAGE           0x00080000

//
// The following are info status bits
//

// These can be applied to certificates only

#define CERT_TRUST_HAS_EXACT_MATCH_ISSUER               0x00000001
#define CERT_TRUST_HAS_KEY_MATCH_ISSUER                 0x00000002
#define CERT_TRUST_HAS_NAME_MATCH_ISSUER                0x00000004
#define CERT_TRUST_IS_SELF_SIGNED                       0x00000008
#define CERT_TRUST_AUTO_UPDATE_CA_REVOCATION            0x00000010
#define CERT_TRUST_AUTO_UPDATE_END_REVOCATION           0x00000020
#define CERT_TRUST_NO_OCSP_FAILOVER_TO_CRL              0x00000040
#define CERT_TRUST_IS_KEY_ROLLOVER                      0x00000080
#define CERT_TRUST_SSL_HANDSHAKE_OCSP                   0x00040000
#define CERT_TRUST_SSL_TIME_VALID_OCSP                  0x00080000
#define CERT_TRUST_SSL_RECONNECT_OCSP                   0x00100000

// These can be applied to certificates and chains

#define CERT_TRUST_HAS_PREFERRED_ISSUER                 0x00000100
#define CERT_TRUST_HAS_ISSUANCE_CHAIN_POLICY            0x00000200
#define CERT_TRUST_HAS_VALID_NAME_CONSTRAINTS           0x00000400
#define CERT_TRUST_IS_PEER_TRUSTED                      0x00000800
#define CERT_TRUST_HAS_CRL_VALIDITY_EXTENDED            0x00001000

// Indicates that the certificate was found in
// a store specified by hExclusiveRoot or hExclusiveTrustedPeople
#define CERT_TRUST_IS_FROM_EXCLUSIVE_TRUST_STORE        0x00002000

#if (NTDDI_VERSION >= NTDDI_WIN8)
#define CERT_TRUST_IS_CA_TRUSTED                        0x00004000
#define CERT_TRUST_HAS_AUTO_UPDATE_WEAK_SIGNATURE       0x00008000
#define CERT_TRUST_HAS_ALLOW_WEAK_SIGNATURE             0x00020000
#endif

// These can be applied to chains only

#define CERT_TRUST_IS_COMPLEX_CHAIN                     0x00010000
#define CERT_TRUST_SSL_TIME_VALID                       0x01000000
#define CERT_TRUST_NO_TIME_CHECK                        0x02000000

#endif // _KERNEL_MODE

VEIL_END()

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
