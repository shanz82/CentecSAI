/**
 * Copyright (c) 2020 Microsoft Open Technologies, Inc.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License"); you may
 *    not use this file except in compliance with the License. You may obtain
 *    a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *    THIS CODE IS PROVIDED ON AN *AS IS* BASIS, WITHOUT WARRANTIES OR
 *    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 *    LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 *    FOR A PARTICULAR PURPOSE, MERCHANTABILITY OR NON-INFRINGEMENT.
 *
 *    See the Apache Version 2.0 License for specific language governing
 *    permissions and limitations under the License.
 *
 *    Microsoft would like to thank the following companies for their review and
 *    assistance with these files: Intel Corporation, Mellanox Technologies Ltd,
 *    Dell Products, L.P., Facebook, Inc., Marvell International Ltd.
 *
 * @file    saitwamp.h
 *
 * @brief   This module defines SAI TWAMP interface
 */

#if !defined (__SAITWAMP_H_)
#define __SAITWAMP_H_

#include <saitypes.h>

/**
 * @defgroup SAITWAMP SAI - TWAMP specific public APIs and data structures
 *
 * @{
 */

/**
 * @brief SAI TWAMP session authentication mode,
 * there are three modes: unauthenticated, authenticated, and encrypted.
 */
typedef enum _sai_twamp_session_auth_mode_t
{
    /** Session session unauthenticated mode */
    SAI_TWAMP_SESSION_AUTH_MODE_AUTHENTICATED = 0,

    /** Session session authenticated mode */
    SAI_TWAMP_SESSION_AUTH_MODE_UNAUTHENTICATED,

    /** Session session encrypted mode */
    SAI_TWAMP_SESSION_AUTH_MODE_ENCRYPTED

} sai_twamp_session_auth_mode_t;

/**
 * @brief SAI TWAMP role
 */
typedef enum _sai_twamp_session_role_t
{
    /** Session enable ingress port */
    SAI_TWAMP_SESSION_ROLE_SENDER = 0,

    /** Session enable egress port */
    SAI_TWAMP_SESSION_ROLE_REFLECTOR

} sai_twamp_session_role_t;

typedef enum _sai_twamp_mode_type_t
{
    /**
     * @brief Reflector will record session stats when enabling twamp full mode 
     */
    SAI_TWAMP_MODE_TYPE_FULL = 0,

    /**
     * @brief Reflector not record session stats when enabling twamp light mode
     */
    SAI_TWAMP_MODE_TYPE_LIGHT

} sai_twamp_mode_type_t;

typedef enum _sai_twamp_pkt_tx_mode_t
{
    /**@brief Continues send twamp test packet */
    SAI_TWAMP_PKT_TX_MODE_CONTINUOUS = 0,

    /**@brief Only send twamp test packet with assign numbers */
    SAI_TWAMP_PKT_TX_MODE_PACKET_NUM,

    /**@brief Send twamp test packet with period interval */
    SAI_TWAMP_PKT_TX_MODE_PERIOD

} sai_twamp_pkt_tx_mode_t;

typedef enum _sai_twamp_timestamp_format_t
{
    /**
     * @brief Packet timestamp format is Network Time Protocol format, 32 bit second and 32 bit fractional part of seconds
     */
    SAI_TWAMP_TIMESTAMP_FORMAT_NTP = 0,

    /**
     * @brief Packet timestamp format is PTP format, 32 bit second and 32 bit nanosecond
     */
    SAI_TWAMP_TIMESTAMP_FORMAT_PTP,

} sai_twamp_timestamp_format_t;

/**
 * @brief SAI TWAMP type of encapsulation for TWAMP
 */
typedef enum _sai_twamp_encapsulation_type_t
{
    /**
     * @brief IP Encapsulation, L2 header | IP(v4/v6) header | UDP header | Original TWAMP test packet
     */
    SAI_TWAMP_ENCAPSULATION_TYPE_IP = 0,

    /**
     * @brief L3 VPN Encapsulation, L2 header | MPLS Label List | IP(v4/v6) header | UDP header | Original TWAMP test packet
     */
    SAI_TWAMP_ENCAPSULATION_TYPE_L3_MPLS_VPN_UNI,

    /**
     * @brief L3 VPN Encapsulation, L2 header | MPLS Label List | IP(v4/v6) header | UDP header | Original TWAMP test packet
     */
    SAI_TWAMP_ENCAPSULATION_TYPE_L3_MPLS_VPN_NNI,

} sai_twamp_encapsulation_type_t;

/**
 * @brief SAI attributes for TWAMP session
 */
typedef enum _sai_twamp_session_attr_t
{
    /**
     * @brief Start of attributes
     */
    SAI_TWAMP_SESSION_ATTR_START,

    /**
     * @brief TWAMP test port
     *
     * @type sai_object_id_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     * @objects SAI_OBJECT_TYPE_PORT
     * @condition SAI_TWAMP_SESSION_ATTR_TWAMP_ENCAPSULATION_TYPE == SAI_TWAMP_ENCAPSULATION_TYPE_IP
     * or SAI_TWAMP_SESSION_ATTR_TWAMP_ENCAPSULATION_TYPE == SAI_TWAMP_ENCAPSULATION_TYPE_L3_MPLS_VPN_UNI
     */
    SAI_TWAMP_SESSION_ATTR_TWAMP_PORT = SAI_TWAMP_SESSION_ATTR_START,

    /**
     * @brief Receive port of TWAMP sender and reflector, enable ACL lookup on this port for match test packet to twamp engine.
     *
     * @type sai_object_list_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     * @objects SAI_OBJECT_TYPE_PORT
     */
    SAI_TWAMP_SESSION_ATTR_RECEIVE_PORT,

    /**
     * @brief TWAMP session role of sender or receiver.
     *
     * @type sai_twamp_session_role_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     */
    SAI_TWAMP_SESSION_ATTR_SESSION_ROLE,

    /**
     * @brief UDP Source port
     *
     * @type sai_uint32_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     */
    SAI_TWAMP_SESSION_ATTR_UDP_SRC_PORT,

    /**
     * @brief UDP Dest port
     *
     * @type sai_uint32_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     */
    SAI_TWAMP_SESSION_ATTR_UDP_DST_PORT,

    /**
     * @brief Local source IP address
     *
     * @type sai_ip4_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     */
    SAI_TWAMP_SESSION_ATTR_SRC_IP,

    /**
     * @brief Remote Dest IP address
     *
     * @type sai_ip4_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     */
    SAI_TWAMP_SESSION_ATTR_DST_IP,

    /**
     * @brief DSCP of Traffic Class
     *
     * @type sai_uint8_t
     * @flags CREATE_ONLY
     * @default 0     
     */
    SAI_TWAMP_SESSION_ATTR_TC,

    /**
     * @brief IP header TTL
     *
     * @type sai_uint8_t
     * @flags CREATE_ONLY
     * @default 255
     * @condition SAI_TWAMP_SESSION_ATTR_SESSION_ROLE == SAI_TWAMP_SESSION_ROLE_SENDER
     */
    SAI_TWAMP_SESSION_ATTR_TTL,

    /**
     * @brief Virtual Private Network virtual router (L3 MPLS VPN)
     *
     * @type sai_object_id_t
     * @flags CREATE_ONLY
     * @objects SAI_OBJECT_TYPE_VIRTUAL_ROUTER
     * @default SAI_NULL_OBJECT_ID
     * @validonly SAI_TWAMP_SESSION_ATTR_HW_LOOKUP_VALID == true
     */
    SAI_TWAMP_SESSION_ATTR_VPN_VIRTUAL_ROUTER,

    /**
     * @brief Encapsulation type
     *
     * @type sai_twamp_encapsulation_type_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     */
    SAI_TWAMP_SESSION_ATTR_TWAMP_ENCAPSULATION_TYPE,

    /**
     * @brief To enable TWAMP session transmit packet
     *
     * @type bool
     * @flags CREATE_AND_SET
     * @default false
     * @condition SAI_TWAMP_SESSION_ATTR_SESSION_ROLE == SAI_TWAMP_SESSION_ROLE_SENDER
     */
    SAI_TWAMP_SESSION_ATTR_SESSION_ENABLE_TRANSMIT,

    /**
     * @brief Hardware lookup valid
     *
     * @type bool
     * @flags CREATE_ONLY
     * @default true
     */
    SAI_TWAMP_SESSION_ATTR_HW_LOOKUP_VALID,

    /**
     * @brief Twamp packet length
     *
     * @type sai_uint32_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     * @condition SAI_TWAMP_SESSION_ATTR_SESSION_ROLE == SAI_TWAMP_SESSION_ROLE_SENDER
     */
    SAI_TWAMP_SESSION_ATTR_PACKET_LENGTH,

    /**
     * @brief TWAMP Session mode: unauthenticated, authenticated, and encrypted.
     *
     * @type sai_twamp_session_auth_mode_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     */
    SAI_TWAMP_SESSION_ATTR_AUTH_MODE,

    /**
     * @brief TWAMP Session nexthop ID for generating TWAMP test packet
     *
     * @type sai_object_id_t
     * @flags CREATE_ONLY
     * @objects SAI_OBJECT_TYPE_NEXT_HOP
     * @allownull true
     * @default SAI_NULL_OBJECT_ID
     */
    SAI_TWAMP_SESSION_ATTR_NEXT_HOP_ID,

    /**
     * @brief TWAMP test packet tx rate per Kbps, configuring by TWAMP sender bandwidth of Tx port
     *
     * @type sai_uint32_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     * @condition SAI_TWAMP_SESSION_ATTR_SESSION_ROLE == SAI_TWAMP_SESSION_ROLE_SENDER
     */
    SAI_TWAMP_SESSION_ATTR_TX_RATE,

    /**
     * @brief twamp packet tx mode of twamp: CONTINUOUS, PACKET_NUM, PERIOD
     *
     * @type sai_int32_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     * @condition SAI_TWAMP_SESSION_ATTR_SESSION_ROLE == SAI_TWAMP_SESSION_ROLE_SENDER
     */
    SAI_TWAMP_SESSION_ATTR_PKT_TX_MODE,

    /**
     * @brief TWAMP test packet tx duration per micro second, timeout of the tx pakcet generation
     *
     * @type sai_uint32_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     * @condition SAI_TWAMP_SESSION_ATTR_SESSION_ROLE == SAI_TWAMP_SESSION_ROLE_SENDER and SAI_TWAMP_SESSION_ATTR_PKT_TX_MODE == SAI_TWAMP_PKT_TX_MODE_CONTINUOUS
     */
    SAI_TWAMP_SESSION_ATTR_TX_PKT_DURATION,

    /**
     * @brief TWAMP test packet tx count, configuring by TWAMP send packet count of Tx 
     * condition SAI_TWAMP_SESSION_ATTR_SESSION_ROLE == SAI_TWAMP_SESSION_ROLE_SENDER and SAI_TWAMP_SESSION_ATTR_PKT_TX_MODE == SAI_TWAMP_PKT_TX_MODE_PACKET_NUM
     *
     * @type sai_uint32_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     */
    SAI_TWAMP_SESSION_ATTR_TX_PKT_CNT,

    /**
     * @brief TWAMP test packet tx period, configuring by TWAMP sender period of Tx
     * Note: if tx period equal 0, sender will continue to gen packet, duration configured by SAI_TWAMP_SESSION_ATTR_PKT_TX_PKT_DURATION.
     * condition SAI_TWAMP_SESSION_ATTR_SESSION_ROLE == SAI_TWAMP_SESSION_ROLE_SENDER and SAI_TWAMP_SESSION_ATTR_PKT_TX_MODE == SAI_TWAMP_PKT_TX_MODE_PERIOD
     *
     * @type sai_uint32_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     */
    SAI_TWAMP_SESSION_ATTR_TX_PKT_PERIOD,

    /**
     * @brief Twamp mode of twamp: light mode and full mode
     *
     * @type sai_int32_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     */
    SAI_TWAMP_SESSION_ATTR_MODE,

    /**
     * @brief Twamp mode of twamp: light mode and full mode
     *
     * @type sai_int32_t
     * @flags CREATE_ONLY
     * @default 0
     */
    SAI_TWAMP_SESSION_ATTR_TIMESTAMP_FORMAT,

    /**
     * @brief End of attributes
     */
    SAI_TWAMP_SESSION_ATTR_END,

    /** Custom range base value */
    SAI_TWAMP_SESSION_ATTR_CUSTOM_RANGE_START = 0x10000000,

    /** End of custom range base */
    SAI_TWAMP_SESSION_ATTR_CUSTOM_RANGE_END

} sai_twamp_session_attr_t;

/**
 * @brief TWAMP Session counter IDs in sai_get_twamp_session_stats() call
 */
typedef enum _sai_twamp_session_stats_t
{
    /** Rx packet stat count */
    SAI_TWAMP_SESSION_STATS_RX_PACKETS,

    /** Rx byte stat count */
    SAI_TWAMP_SESSION_STATS_RX_BYTE,

    /** Tx packet stat count */
    SAI_TWAMP_SESSION_STATS_TX_PACKETS,

    /** Tx byte stat count */
    SAI_TWAMP_SESSION_STATS_TX_BYTE,

    /** Packet Drop stat count */
    SAI_TWAMP_SESSION_STATS_DROP_PACKETS,

    /** Packet max latency */
    SAI_TWAMP_SESSION_STATS_MAX_LATENCY,

    /** Packet min latency */
    SAI_TWAMP_SESSION_STATS_MIN_LATENCY,

    /** Packet avg latency */
    SAI_TWAMP_SESSION_STATS_AVG_LATENCY,

    /** Packet max jitter */
    SAI_TWAMP_SESSION_STATS_MAX_JITTER,

    /** Packet min jitter */
    SAI_TWAMP_SESSION_STATS_MIN_JITTER,

    /** Packet avg jitter */
    SAI_TWAMP_SESSION_STATS_AVG_JITTER,

    /** Session first timestamp */
    SAI_TWAMP_SESSION_STATS_FIRST_TS,

    /** Session last timestamp */
    SAI_TWAMP_SESSION_STATS_LAST_TS,

    /** Session duration timestamp */
    SAI_TWAMP_SESSION_STATS_DURATION_TS

} sai_twamp_session_stats_t;

/**
 * @brief Create TWAMP session.
 *
 * @param[out] twamp_session_id TWAMP session id
 * @param[in] switch_id Switch id
 * @param[in] attr_count Number of attributes
 * @param[in] attr_list Value of attributes
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 * error code is returned.
 */
typedef sai_status_t (*sai_create_twamp_session_fn)(
        _Out_ sai_object_id_t *twamp_session_id,
        _In_ sai_object_id_t switch_id,
        _In_ uint32_t attr_count,
        _In_ const sai_attribute_t *attr_list);

/**
 * @brief Remove TWAMP session.
 *
 * @param[in] twamp_session_id TWAMP session id
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 * error code is returned.
 */
typedef sai_status_t (*sai_remove_twamp_session_fn)(
        _In_ sai_object_id_t twamp_session_id);

/**
 * @brief Set TWAMP session attributes.
 *
 * @param[in] twamp_session_id TWAMP session id
 * @param[in] attr Value of attribute
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 * error code is returned.
 */
typedef sai_status_t (*sai_set_twamp_session_attribute_fn)(
        _In_ sai_object_id_t twamp_session_id,
        _In_ const sai_attribute_t *attr);

/**
 * @brief Get TWAMP session attributes.
 *
 * @param[in] twamp_session_id TWAMP session id
 * @param[in] attr_count Number of attributes
 * @param[inout] attr_list Value of attribute
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 * error code is returned.
 */
typedef sai_status_t (*sai_get_twamp_session_attribute_fn)(
        _In_ sai_object_id_t twamp_session_id,
        _In_ uint32_t attr_count,
        _Inout_ sai_attribute_t *attr_list);

/**
 * @brief Get TWAMP session statistics counters. Deprecated for backward compatibility.
 *
 * @param[in] twamp_session_id TWAMP session id
 * @param[in] number_of_counters Number of counters in the array
 * @param[in] counter_ids Specifies the array of counter ids
 * @param[out] counters Array of resulting counter values.
 *
 * @return SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_get_twamp_session_stats_fn)(
        _In_ sai_object_id_t twamp_session_id,
        _In_ uint32_t number_of_counters,
        _In_ const sai_stat_id_t *counter_ids,
        _Out_ uint64_t *counters);

/**
 * @brief Clear TWAMP session statistics counters.
 *
 * @param[in] twamp_session_id TWAMP session id
 * @param[in] number_of_counters Number of counters in the array
 * @param[in] counter_ids Specifies the array of counter ids
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_clear_twamp_session_stats_fn)(
        _In_ sai_object_id_t twamp_session_id,
        _In_ uint32_t number_of_counters,
        _In_ const sai_stat_id_t *counter_ids);

/**
 * @brief TWAMP method table retrieved with sai_api_query()
 */
typedef struct _sai_twamp_api_t
{
    sai_create_twamp_session_fn            create_twamp_session;
    sai_remove_twamp_session_fn            remove_twamp_session;
    sai_set_twamp_session_attribute_fn     set_twamp_session_attribute;
    sai_get_twamp_session_attribute_fn     get_twamp_session_attribute;
    sai_get_twamp_session_stats_fn         get_twamp_session_stats;
    sai_clear_twamp_session_stats_fn       clear_twamp_session_stats;

} sai_twamp_api_t;

/**
 * @}
 */
#endif /** __SAITWAMP_H_ */
