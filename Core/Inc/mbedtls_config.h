/* ============================================================
 * mbedtls_config.h — STM32 嵌入式最小 TLS 客户端配置
 * 适配于 STM32F1/F4 + LWIP + FreeRTOS
 * ============================================================ */
#ifndef MBEDTLS_CONFIG_H
#define MBEDTLS_CONFIG_H

/* —— 系统 —— */
#define MBEDTLS_HAVE_ASM                    /* 启用汇编优化 */
#define MBEDTLS_PLATFORM_MEMORY             /* 自定义内存分配 */
#define MBEDTLS_PLATFORM_PRINTF_ALT         /* 自定义 printf */

/* —— TLS 协议 —— */
#define MBEDTLS_SSL_TLS_C                   /* ★ TLS 核心模块（必须） */
#define MBEDTLS_SSL_PROTO_TLS1_2            /* TLS 1.2 */
// #define MBEDTLS_SSL_PROTO_TLS1_3        /* TLS 1.3（可选，占更多 Flash）*/

/* —— TLS 功能 —— */
#define MBEDTLS_SSL_CLI_C                   /* TLS 客户端 */
// #define MBEDTLS_SSL_SRV_C               /* TLS 服务端（不需要则注释）*/
#define MBEDTLS_SSL_KEEP_PEER_CERTIFICATE 0 /* 不保存对端证书（省 RAM）*/

/* —— TLS 缓冲区大小（按 RAM 预算调整）—— */
#define MBEDTLS_SSL_MAX_CONTENT_LEN    4096  /* TLS 记录最大长度 */
#define MBEDTLS_SSL_IN_CONTENT_LEN     4096
#define MBEDTLS_SSL_OUT_CONTENT_LEN    4096

/* —— 加密套件 —— */
#define MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED
#define MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED
#define MBEDTLS_KEY_EXCHANGE_PSK_ENABLED        /* 预共享密钥（轻量）*/

/* —— 对称加密 —— */
#define MBEDTLS_CIPHER_C                    /* ★ 加密抽象层（GCM/CCM 需要） */
#define MBEDTLS_AES_C
#define MBEDTLS_CIPHER_MODE_CBC
#define MBEDTLS_CIPHER_MODE_CTR
#define MBEDTLS_GCM_C
#define MBEDTLS_CCM_C

/* —— 哈希 —— */
#define MBEDTLS_SHA256_C
#define MBEDTLS_SHA512_C                     /* 含 SHA-384 */
#define MBEDTLS_MD_C
#define MBEDTLS_MD5_C                        /* 仅兼容旧协议 */

/* —— 非对称加密 —— */
#define MBEDTLS_RSA_C
#define MBEDTLS_ECP_C
#define MBEDTLS_ECP_DP_SECP256R1_ENABLED     /* P-256 曲线 */
#define MBEDTLS_ECP_DP_SECP384R1_ENABLED     /* P-384 曲线 */
#define MBEDTLS_ECDH_C
#define MBEDTLS_ECDSA_C
#define MBEDTLS_BIGNUM_C
#define MBEDTLS_PK_C
#define MBEDTLS_PK_PARSE_C

/* —— 随机数 —— */
#define MBEDTLS_ENTROPY_C
#define MBEDTLS_CTR_DRBG_C

/* —— X.509 证书 —— */
#define MBEDTLS_X509_CRT_PARSE_C
#define MBEDTLS_X509_USE_C
#define MBEDTLS_ASN1_PARSE_C
#define MBEDTLS_ASN1_WRITE_C
#define MBEDTLS_OID_C
#define MBEDTLS_PEM_PARSE_C
#define MBEDTLS_BASE64_C

/* —— 平台抽象 —— */
#define MBEDTLS_PLATFORM_C
#define MBEDTLS_PLATFORM_PRINTF

/* —— 错误和调试 —— */
#define MBEDTLS_ERROR_C
#define MBEDTLS_DEBUG_C                      /* TLS 调试输出 */

/* —— 常量时间（防侧信道攻击） —— */
#define MBEDTLS_TIMING_C
#define MBEDTLS_HAVE_TIME                    /* 需要时间函数 */

/* —— STM32 硬件加速（根据你的 MCU 选择）—— */
/* STM32F4/F7/H7 有 CRYP + HASH + RNG 外设 */
// #define MBEDTLS_AES_ALT                    /* 硬件 AES（CRYP）*/
// #define MBEDTLS_SHA256_ALT                 /* 硬件 SHA-256（HASH）*/
// #define MBEDTLS_ENTROPY_HARDWARE_ALT       /* 硬件随机数（RNG）*/

/* STM32L5/U5/H7 有 PKA 外设 */
// #define MBEDTLS_ECP_INTERNAL_ALT           /* 硬件 ECC 加速（PKA）*/

/* STM32: no Unix/Windows platform entropy, use hardware RNG instead */
#define MBEDTLS_NO_PLATFORM_ENTROPY

#endif /* MBEDTLS_CONFIG_H */
