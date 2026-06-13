/**
 *  Minimal ssl_debug_helpers_generated.c ¡ª stubs for missing mbedTLS source
 */

#include "common.h"

#if defined(MBEDTLS_DEBUG_C)

#include "mbedtls/ssl.h"
#include "ssl_debug_helpers.h"

const char *mbedtls_ssl_states_str(mbedtls_ssl_states in)
{
    switch (in) {
        case MBEDTLS_SSL_HELLO_REQUEST: return "HELLO_REQUEST";
        case MBEDTLS_SSL_CLIENT_HELLO: return "CLIENT_HELLO";
        case MBEDTLS_SSL_SERVER_HELLO: return "SERVER_HELLO";
        case MBEDTLS_SSL_SERVER_CERTIFICATE: return "SERVER_CERTIFICATE";
        case MBEDTLS_SSL_SERVER_KEY_EXCHANGE: return "SERVER_KEY_EXCHANGE";
        case MBEDTLS_SSL_CERTIFICATE_REQUEST: return "CERTIFICATE_REQUEST";
        case MBEDTLS_SSL_SERVER_HELLO_DONE: return "SERVER_HELLO_DONE";
        case MBEDTLS_SSL_CLIENT_CERTIFICATE: return "CLIENT_CERTIFICATE";
        case MBEDTLS_SSL_CLIENT_KEY_EXCHANGE: return "CLIENT_KEY_EXCHANGE";
        case MBEDTLS_SSL_CERTIFICATE_VERIFY: return "CERTIFICATE_VERIFY";
        case MBEDTLS_SSL_CLIENT_CHANGE_CIPHER_SPEC: return "CLIENT_CHANGE_CIPHER_SPEC";
        case MBEDTLS_SSL_CLIENT_FINISHED: return "CLIENT_FINISHED";
        case MBEDTLS_SSL_SERVER_CHANGE_CIPHER_SPEC: return "SERVER_CHANGE_CIPHER_SPEC";
        case MBEDTLS_SSL_SERVER_FINISHED: return "SERVER_FINISHED";
#if defined(MBEDTLS_SSL_EARLY_DATA)
        case MBEDTLS_SSL_EARLY_END_OF_EARLY_DATA: return "END_OF_EARLY_DATA";
#endif
        default: return "UNKNOWN";
    }
}

const char *mbedtls_ssl_sig_alg_to_str(uint16_t in)
{
    (void) in;
    return "SIG_ALG";
}

const char *mbedtls_ssl_named_group_to_str(uint16_t in)
{
    (void) in;
    return "NAMED_GROUP";
}

#endif /* MBEDTLS_DEBUG_C */