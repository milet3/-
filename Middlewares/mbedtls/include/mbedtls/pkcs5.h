#ifndef MBEDTLS_PKCS5_H
#define MBEDTLS_PKCS5_H
#include "mbedtls/build_info.h"
#if defined(MBEDTLS_PKCS5_C)
#include "mbedtls/md.h"
#include "mbedtls/asn1.h"
#define MBEDTLS_ERR_PKCS5_BAD_INPUT_DATA -0x2e80
#define MBEDTLS_ERR_PKCS5_INVALID_FORMAT -0x2f00
#define MBEDTLS_ERR_PKCS5_FEATURE_UNAVAILABLE -0x2f80
#define MBEDTLS_ERR_PKCS5_PASSWORD_MISMATCH -0x3000
#define MBEDTLS_PKCS5_DECRYPT 0
#define MBEDTLS_PKCS5_ENCRYPT 1
int mbedtls_pkcs5_pbes2(const mbedtls_asn1_buf *params, int mode, const unsigned char *pwd, size_t pwdlen, const unsigned char *input, size_t ilen, unsigned char *output, size_t *olen);
int mbedtls_pkcs5_pbkdf2_hmac(const mbedtls_md_info_t *md, const unsigned char *password, size_t plen, const unsigned char *salt, size_t slen, unsigned int iteration_count, uint32_t key_length, unsigned char *output);
int mbedtls_pkcs5_self_test(int verbose);
#endif /* MBEDTLS_PKCS5_C */
#endif /* MBEDTLS_PKCS5_H */