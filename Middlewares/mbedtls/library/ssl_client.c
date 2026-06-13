/**
 *  Minimal ssl_client.c ¡ª stubs for missing mbedTLS source
 */

#include "common.h"

#if defined(MBEDTLS_SSL_TLS_C)

#include "ssl_client.h"
#include "ssl_misc.h"
#include "mbedtls/ssl.h"
#include "mbedtls/ecp.h"

int mbedtls_ssl_check_curve(const mbedtls_ssl_context *ssl, mbedtls_ecp_group_id grp_id)
{
    const mbedtls_ecp_curve_info *curve_info;
    ((void) ssl);
    for (curve_info = mbedtls_ecp_curve_list();
         curve_info->grp_id != MBEDTLS_ECP_DP_NONE;
         curve_info++) {
        if (curve_info->grp_id == grp_id) {
            return 0;
        }
    }
    return -1;
}

MBEDTLS_CHECK_RETURN_CRITICAL
int mbedtls_ssl_write_client_hello(mbedtls_ssl_context *ssl)
{
    return mbedtls_ssl_handshake_client_step(ssl);
}

#endif /* MBEDTLS_SSL_TLS_C */