/**
 * \file config_psa.h
 * \brief PSA crypto configuration options for mbedTLS
 *
 * This file provides default PSA crypto configuration.
 * When MBEDTLS_PSA_CRYPTO_CONFIG is not enabled, these macros
 * ensure backward compatibility with the legacy mbedtls_config.h approach.
 */
#ifndef MBEDTLS_CONFIG_PSA_H
#define MBEDTLS_CONFIG_PSA_H

#if defined(MBEDTLS_PSA_CRYPTO_CONFIG)

/* PSA crypto configuration file */
#include "psa/crypto_config.h"

#else /* MBEDTLS_PSA_CRYPTO_CONFIG */

/* Without PSA crypto config, derive PSA settings from legacy config */

#if defined(MBEDTLS_AES_C)
#define PSA_WANT_ALG_CMAC                1
#endif

#if defined(MBEDTLS_CCM_C)
#define PSA_WANT_ALG_CCM                 1
#endif

#if defined(MBEDTLS_GCM_C)
#define PSA_WANT_ALG_GCM                 1
#endif

#if defined(MBEDTLS_CHACHA20_C) && defined(MBEDTLS_POLY1305_C)
#define PSA_WANT_ALG_CHACHA20_POLY1305   1
#endif

#if defined(MBEDTLS_ECP_DP_SECP256R1_ENABLED)
#define PSA_WANT_ECC_SECP_R1_256         1
#endif

#if defined(MBEDTLS_ECP_DP_SECP384R1_ENABLED)
#define PSA_WANT_ECC_SECP_R1_384         1
#endif

#if defined(MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED) || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED)
#define PSA_WANT_ALG_ECDH                1
#endif

#if defined(MBEDTLS_ECDSA_C)
#define PSA_WANT_ALG_ECDSA               1
#define PSA_WANT_ALG_DETERMINISTIC_ECDSA 1
#endif

#if defined(MBEDTLS_RSA_C)
#define PSA_WANT_ALG_RSA_PKCS1V15_CRYPT  1
#define PSA_WANT_ALG_RSA_PKCS1V15_SIGN   1
#define PSA_WANT_ALG_RSA_OAEP            1
#define PSA_WANT_ALG_RSA_PSS             1
#endif

#if defined(MBEDTLS_SHA256_C)
#define PSA_WANT_ALG_SHA_256             1
#endif

#if defined(MBEDTLS_SHA384_C)
#define PSA_WANT_ALG_SHA_384             1
#endif

#if defined(MBEDTLS_SHA512_C)
#define PSA_WANT_ALG_SHA_512             1
#endif

#if defined(MBEDTLS_MD5_C)
#define PSA_WANT_ALG_MD5                 1
#endif

#if defined(MBEDTLS_SHA1_C)
#define PSA_WANT_ALG_SHA_1               1
#endif

#define PSA_WANT_KEY_TYPE_DERIVE          1
#define PSA_WANT_KEY_TYPE_PASSWORD        1
#define PSA_WANT_KEY_TYPE_PASSWORD_HASH   1
#define PSA_WANT_KEY_TYPE_RAW_DATA        1

#if defined(MBEDTLS_AES_C)
#define PSA_WANT_KEY_TYPE_AES             1
#endif

#if defined(MBEDTLS_ECP_C)
#define PSA_WANT_KEY_TYPE_ECC_KEY_PAIR    1
#define PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY  1
#endif

#if defined(MBEDTLS_RSA_C)
#define PSA_WANT_KEY_TYPE_RSA_KEY_PAIR    1
#define PSA_WANT_KEY_TYPE_RSA_PUBLIC_KEY  1
#endif

#endif /* MBEDTLS_PSA_CRYPTO_CONFIG */

#endif /* MBEDTLS_CONFIG_PSA_H */
