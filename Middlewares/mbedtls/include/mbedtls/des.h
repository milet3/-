#ifndef MBEDTLS_DES_H
#define MBEDTLS_DES_H
#include "mbedtls/build_info.h"
#if defined(MBEDTLS_DES_C)
#include <stddef.h>
#include <stdint.h>
#define MBEDTLS_DES_ENCRYPT 1
#define MBEDTLS_DES_DECRYPT 0
#define MBEDTLS_ERR_DES_INVALID_INPUT_LENGTH -0x0032
typedef struct mbedtls_des_context { uint32_t sk[32]; } mbedtls_des_context;
typedef struct mbedtls_des3_context { uint32_t sk[96]; } mbedtls_des3_context;
static inline void mbedtls_des_init(mbedtls_des_context *ctx) { (void)ctx; }
static inline void mbedtls_des_free(mbedtls_des_context *ctx) { (void)ctx; }
static inline void mbedtls_des3_init(mbedtls_des3_context *ctx) { (void)ctx; }
static inline void mbedtls_des3_free(mbedtls_des3_context *ctx) { (void)ctx; }
static inline int mbedtls_des_setkey_enc(mbedtls_des_context *ctx, const unsigned char key[8]) { (void)ctx; (void)key; return 0; }
static inline int mbedtls_des_setkey_dec(mbedtls_des_context *ctx, const unsigned char key[8]) { (void)ctx; (void)key; return 0; }
static inline int mbedtls_des_crypt_ecb(mbedtls_des_context *ctx, const unsigned char input[8], unsigned char output[8]) { (void)ctx; (void)input; (void)output; return 0; }
static inline int mbedtls_des3_set2key_enc(mbedtls_des3_context *ctx, const unsigned char key[16]) { (void)ctx; (void)key; return 0; }
static inline int mbedtls_des3_set2key_dec(mbedtls_des3_context *ctx, const unsigned char key[16]) { (void)ctx; (void)key; return 0; }
static inline int mbedtls_des3_crypt_ecb(mbedtls_des3_context *ctx, const unsigned char input[8], unsigned char output[8]) { (void)ctx; (void)input; (void)output; return 0; }
#endif /* MBEDTLS_DES_C */
#endif /* MBEDTLS_DES_H */