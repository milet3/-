#ifndef MBEDTLS_PKCS12_H
#define MBEDTLS_PKCS12_H
#include "mbedtls/build_info.h"
#if defined(MBEDTLS_PKCS12_C)
#include "mbedtls/md.h"
#include "mbedtls/cipher.h"
#include "mbedtls/asn1.h"
#define MBEDTLS_ERR_PKCS12_BAD_INPUT_DATA -0x1F00
#define MBEDTLS_ERR_PKCS12_FEATURE_UNAVAILABLE -0x1F80
#define MBEDTLS_ERR_PKCS12_PASSWORD_MISMATCH -0x2000
#define MBEDTLS_PKCS12_DERIVE_KEY 1
#define MBEDTLS_PKCS12_DERIVE_IV 2
#define MBEDTLS_PKCS12_DERIVE_MAC_KEY 3
int mbedtls_pkcs12_pbe_sha1_rc4_128(const mbedtls_asn1_buf *params, int mode, const unsigned char *pwd, size_t pwdlen, const unsigned char *input, size_t ilen, unsigned char *output);
int mbedtls_pkcs12_pbe(const mbedtls_asn1_buf *params, int mode, mbedtls_md_type_t md_type, mbedtls_cipher_id_t cipher_id, const unsigned char *pwd, size_t pwdlen, const unsigned char *input, size_t ilen, unsigned char *output, size_t *olen);
int mbedtls_pkcs12_derivation(unsigned char *data, size_t datalen, const unsigned char *pwd, size_t pwdlen, const unsigned char *salt, size_t slen, mbedtls_md_type_t md_type, int id, int iterations);
#endif /* MBEDTLS_PKCS12_C */
#endif /* MBEDTLS_PKCS12_H */