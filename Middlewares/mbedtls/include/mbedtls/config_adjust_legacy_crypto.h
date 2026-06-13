/**
 * \file config_adjust_legacy_crypto.h
 *
 * \brief Derive internal capability macros from user-facing config options.
 *
 * This file is included automatically by build_info.h.
 * Do not include it directly.
 */

#ifndef MBEDTLS_CONFIG_ADJUST_LEGACY_CRYPTO_H
#define MBEDTLS_CONFIG_ADJUST_LEGACY_CRYPTO_H

/* =================================================================
 *  1. MD_CAN_* : which hash algorithms are available
 * ================================================================= */
#if defined(MBEDTLS_SHA256_C)
#define MBEDTLS_MD_CAN_SHA256   1
#define MBEDTLS_MD_CAN_SHA224   1
#endif

#if defined(MBEDTLS_SHA512_C)
#define MBEDTLS_MD_CAN_SHA384   1
#define MBEDTLS_MD_CAN_SHA512   1
#endif

#if defined(MBEDTLS_SHA1_C)
#define MBEDTLS_MD_CAN_SHA1     1
#endif

#if defined(MBEDTLS_MD5_C)
#define MBEDTLS_MD_CAN_MD5      1
#endif

#if defined(MBEDTLS_RIPEMD160_C)
#define MBEDTLS_MD_CAN_RIPEMD160 1
#endif

/* =================================================================
 *  2. CCM / GCM capability : which block ciphers work with CCM/GCM
 * ================================================================= */
#if defined(MBEDTLS_AES_C)
#define MBEDTLS_CCM_GCM_CAN_AES      1
#endif

#if defined(MBEDTLS_ARIA_C)
#define MBEDTLS_CCM_GCM_CAN_ARIA     1
#endif

#if defined(MBEDTLS_CAMELLIA_C)
#define MBEDTLS_CCM_GCM_CAN_CAMELLIA 1
#endif

/* =================================================================
 *  3. SSL_HAVE_* : which AEAD modes are available for TLS
 * ================================================================= */
#if defined(MBEDTLS_GCM_C)
#define MBEDTLS_SSL_HAVE_GCM         1
#endif

#if defined(MBEDTLS_CCM_C)
#define MBEDTLS_SSL_HAVE_CCM         1
#endif

#if defined(MBEDTLS_CHACHAPOLY_C)
#define MBEDTLS_SSL_HAVE_CHACHAPOLY  1
#endif

/* =================================================================
 *  4. CAN_ECDH : ECDH available (needs both ECDH and ECP)
 * ================================================================= */
#if defined(MBEDTLS_ECDH_C) && defined(MBEDTLS_ECP_C)
#define MBEDTLS_CAN_ECDH             1
#endif

/* =================================================================
 *  5. PKCS1 versions : RSA PKCS#1 v1.5 and v2.1
 * ================================================================= */
#if defined(MBEDTLS_RSA_C)
#define MBEDTLS_PKCS1_V15            1
#define MBEDTLS_PKCS1_V21            1
#endif

/* =================================================================
 *  6. PK_CAN_* : public-key algorithm capabilities
 * ================================================================= */
#if defined(MBEDTLS_ECDSA_C)
#define MBEDTLS_PK_CAN_ECDSA_SIGN    1
#define MBEDTLS_PK_CAN_ECDSA_VERIFY  1
#endif

/* =================================================================
 *  7. PSA crypto type mappings (when not using PSA config)
 * ================================================================= */
#if !defined(MBEDTLS_PSA_CRYPTO_CONFIG)

#if defined(MBEDTLS_ECP_C)
#define PSA_WANT_KEY_TYPE_ECC_KEY_PAIR    1
#define PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY  1
#endif

#if defined(MBEDTLS_RSA_C)
#define PSA_WANT_KEY_TYPE_RSA_KEY_PAIR    1
#define PSA_WANT_KEY_TYPE_RSA_PUBLIC_KEY  1
#endif

#endif /* !MBEDTLS_PSA_CRYPTO_CONFIG */

#endif /* MBEDTLS_CONFIG_ADJUST_LEGACY_CRYPTO_H */
