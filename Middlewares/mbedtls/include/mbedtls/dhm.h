#ifndef MBEDTLS_DHM_H
#define MBEDTLS_DHM_H
#include "mbedtls/build_info.h"
#if defined(MBEDTLS_DHM_C)
#include "mbedtls/bignum.h"
#define MBEDTLS_ERR_DHM_BAD_INPUT_DATA -0x3080
#define MBEDTLS_ERR_DHM_READ_PARAMS_FAILED -0x3100
#define MBEDTLS_ERR_DHM_MAKE_PARAMS_FAILED -0x3180
#define MBEDTLS_ERR_DHM_READ_PUBLIC_FAILED -0x3200
#define MBEDTLS_ERR_DHM_MAKE_PUBLIC_FAILED -0x3280
#define MBEDTLS_ERR_DHM_CALC_SECRET_FAILED -0x3300
typedef struct mbedtls_dhm_context { mbedtls_mpi P, G, X, GX, GY, K; size_t len; } mbedtls_dhm_context;
void mbedtls_dhm_init(mbedtls_dhm_context *ctx);
void mbedtls_dhm_free(mbedtls_dhm_context *ctx);
int mbedtls_dhm_read_params(mbedtls_dhm_context *ctx, const unsigned char **p, const unsigned char *end);
int mbedtls_dhm_make_params(mbedtls_dhm_context *ctx, int x_size, unsigned char *output, size_t *olen, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng);
int mbedtls_dhm_read_public(mbedtls_dhm_context *ctx, const unsigned char *input, size_t ilen);
int mbedtls_dhm_make_public(mbedtls_dhm_context *ctx, int x_size, unsigned char *output, size_t olen, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng);
int mbedtls_dhm_calc_secret(mbedtls_dhm_context *ctx, unsigned char *output, size_t output_size, size_t *olen, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng);
int mbedtls_dhm_self_test(int verbose);
#endif /* MBEDTLS_DHM_C */
#endif /* MBEDTLS_DHM_H */