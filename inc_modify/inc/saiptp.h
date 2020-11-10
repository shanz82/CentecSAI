/**
 * Copyright (c) 2014 Microsoft Open Technologies, Inc.
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
 * @file    saiptp.h
 *
 * @brief   This module defines SAI PTP 
 */

#if !defined (__SAIPTP_H_)
#define __SAIPTP_H_

#include <saitypes.h>

#define TOD_INTF_DISABLE 2

/**
 * @brief Define PTP device type
 */
typedef enum _sai_ptp_device_type_t
{
    /** Blind for PTP message,forward it as one normal packet*/
    SAI_PTP_DEVICE_NONE,

    /** Ordinary clock device */
    SAI_PTP_DEVICE_OC,

    /** Boundary clock device */
    SAI_PTP_DEVICE_BC,

    /** End-to-end transparent clock device */
    SAI_PTP_DEVICE_E2E_TC,

    /** Peer-to-peer transparent clock device*/
    SAI_PTP_DEVICE_P2P_TC,

} sai_ptp_device_type_t;

/**
 * @brief Attribute data for 
 */
typedef enum _sai_ptp_enable_based_type_t
{
    /** PTP enable based on vlan */
    SAI_PTP_ENABLE_BASED_ON_VLAN,

    /** PTP enable based on port */
    SAI_PTP_ENABLE_BASED_ON_PORT,

} sai_ptp_enable_based_type_t;

/**
 * @brief Attribute data for
 */
typedef enum _sai_ptp_tod_interface_format_type_t
{
    /** PTP tod interface format selects CCSA YD/T 2375-2011 as the standard*/
    SAI_PTP_TOD_INTERFACE_FORMAT_CCSA_YDT2375,

    /** PTP tod interface format selects ITU.T G.703 as the standard*/
    SAI_PTP_TOD_INTERFACE_FORMAT_ITUT_G703,

    /** User define the ptp tod interface format */
    SAI_PTP_TOD_INTERFACE_FORMAT_USER_DEFINE,

}sai_ptp_tod_interface_format_type_t;

/**
 * @brief Attribute data for
 */
typedef enum _sai_ptp_tod_intf_mode_t
{
    /** Interface input mode */
    SAI_PTP_TOD_INTERFACE_INPUT,

    /** Interface output mode */
    SAI_PTP_TOD_INTERFACE_OUTPUT,

    /** Interface disable */
    SAI_PTP_TOD_INTERFACE_DISABLE,

} sai_ptp_tod_intf_mode_t;

/**
 * @brief Attribute Id in create_ptp_domain() and;
 * set_ptp_domain_attribute();
 * remove_ptp_domain();
 * get_ptp_domain_attribute();
 */
typedef enum _sai_ptp_domain_attr_t
{
    /**
     * @brief Start of attributes
     */
    SAI_PTP_DOMAIN_ATTR_START = 0x00000000,

    /**
     * @brief PTP will be enabled by port or vlan, by port as default
     *
     * @type sai_ptp_enable_based_type_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     */
    SAI_PTP_DOMAIN_ATTR_PTP_ENABLE_BASED_TYPE = SAI_PTP_DOMAIN_ATTR_START,

    /**
     * @brief Define PTP device type
     *
     * @type sai_int32_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     */
    SAI_PTP_DOMAIN_ATTR_DEVICE_TYPE,

    /**
     * @brief Define the clock drift offset.
     *
     * @type sai_timeoffset_t
     * @flags CREATE_AND_SET
     */
    SAI_PTP_DOMAIN_ATTR_ADJUEST_CLOCK_DRIFT_OFFSET,

    /**
     * @brief Define the clock time offset.
     *
     * @type sai_timeoffset_t
     * @flags CREATE_AND_SET
     */
    SAI_PTP_DOMAIN_ATTR_ADJUEST_CLOCK_TIME_OFFSET,

    /**
     * @brief Tod interface type
     *
     * @type sai_int32_t
     * @flags CREATE_AND_SET
     * @default 0
     */
    SAI_PTP_DOMAIN_ATTR_TOD_INTF_FORMAT_TYPE,

    /**
     * @brief Leap seconds between GPS and UTC, set attr only support output mode, get attr support output and input mode
     * @condition  SAI_PTP_DOMAIN_ATTR_TOD_INTF_ENABLE == false
     *
     * @type sai_int8_t
     * @flags CREATE_AND_SET
     */
    SAI_PTP_DOMAIN_ATTR_TOD_INTF_LEAP_SECOND,

    /**
     * @brief Tod interface code 1PPS status <0-0xFF>, set attr only support output mode, get attr support output and input mode
     * @condition SAI_PTP_DOMAIN_ATTR_TOD_INTF_ENABLE == false
     *
     * @type  sai_uint8_t
     * @flags CREATE_AND_SET
     */
    SAI_PTP_DOMAIN_ATTR_TOD_INTF_PPS_STATUS,

    /**
     * @brief Tod interface code 1PPS accuracy, set attr only support output mode, get attr support output and input mode  
     * @condition SAI_PTP_DOMAIN_ATTR_TOD_INTF_ENABLE == false
     *
     * @type  sai_uint8_t
     * @flags CREATE_AND_SET
     */
    SAI_PTP_DOMAIN_ATTR_TOD_INTF_PPS_ACCURACY,

    /**
     * @brief Tod interface  GPS week, used for input mode with get attr
     * condition SAI_PTP_DOMAIN_ATTR_TOD_INTF_MODE == SAI_PTP_TOD_INTERFACE_INPUT
     * @type  sai_uint16_t
     * @flags READ_ONLY
     */
    SAI_PTP_DOMAIN_ATTR_TOD_INTF_GPS_WEEK,

    /**
     * @brief Tod interface GPS Second time of week, used for input mode with get attr
     * condition SAI_PTP_DOMAIN_ATTR_TOD_INTF_MODE== SAI_PTP_TOD_INTERFACE_INPUT
     * @type  sai_uint32_t
     * @flags READ_ONLY
     */
    SAI_PTP_DOMAIN_ATTR_TOD_INTF_GPS_SECOND_OF_WEEK,

    /**
     * @brief Tod interface mode,input or output,
     * the value can only be modified when the SAI_PTP_DOMAIN_ATTR_TOD_INTF_ENABLE == TOD_INTF_DISABLE
     *
     * @type sai_int32_t
     * @flags CREATE_AND_SET
     */
    SAI_PTP_DOMAIN_ATTR_TOD_INTF_MODE,

    /**
     * @brief Enable the tod interface 
     *
     * @type bool
     * @flags CREATE_AND_SET
     */
    SAI_PTP_DOMAIN_ATTR_TOD_INTF_ENABLE,

    /**
     * @brief get TAI timestamp
     *
     * @type  sai_timespec_t
     * @flags READ_ONLY
     */
    SAI_PTP_DOMAIN_ATTR_TAI_TIMESTAMP,

    /**
     * @brief Get ptp captured timestamp from fifo 
     * it can indicate the time when sync message is sent and is filled in the Follow_Up message
     * it can indicate the time when Pdelay_Resp is sent and is filled in the Pdelay_Resp_Follow_Up message
     *
     * @type  sai_captured_timespec_t
     * @flags READ_ONLY
     */
    SAI_PTP_DOMAIN_ATTR_CAPTURED_TIMESTAMP,

    /**
     * @brief End of attributes
     */
    SAI_PTP_DOMAIN_ATTR_END,

    /** Custom range base value */
    SAI_PTP_DOMAIN_ATTR_CUSTOM_RANGE_START = 0x10000000,

    /** End of custom range base */
    SAI_PTP_DOMAIN_ATTR_CUSTOM_RANGE_END

} sai_ptp_domain_attr_t;

/**
 * @brief Create ptp domain
 *
 * @param[out] ptp_domain_id ptp domain id
 * @param[in] switch_id Switch id
 * @param[in] attr_count Number of attributes
 * @param[in] attr_list Array of attributes
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_create_ptp_domain_fn)(
        _Out_ sai_object_id_t *ptp_domain_id,
        _In_ sai_object_id_t switch_id,
        _In_ uint32_t attr_count,
        _In_ const sai_attribute_t *attr_list);

/**
 * @brief Remove ptp domain
 *
 * @param[in] ptp_domain_id ptp domain id
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_remove_ptp_domain_fn)(
        _In_ sai_object_id_t ptp_domain_id);

/**
 * @brief Set ptp domain attribute
 *
 * @param[in] ptp_domain_id ptp domain id
 * @param[in] attr attributes
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_set_ptp_domain_attribute_fn)(
        _In_ sai_object_id_t ptp_domain_id,
        _In_ const sai_attribute_t *attr);

/**
 * @brief Get ptp domain attribute
 *
 * @param[in] ptp_domain_id ptp domain id
 * @param[in] attr_count Number of attributes
 * @param[inout] attr_list Array of attributes
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t (*sai_get_ptp_domain_attribute_fn)(
        _In_ sai_object_id_t ptp_domain_id,
        _In_ uint32_t attr_count,
        _Inout_ sai_attribute_t *attr_list);

/**
 * @brief PTP API
 */
typedef struct _sai_ptp_api_t
{ 
    sai_create_ptp_domain_fn               create_ptp_domain;
    sai_remove_ptp_domain_fn               remove_ptp_domain;
    sai_set_ptp_domain_attribute_fn        set_ptp_domain_attribute;
    sai_get_ptp_domain_attribute_fn        get_ptp_domain_attribute;

} sai_ptp_api_t;

/**
 * @}
 */
#endif /** __SAIPTP_H_ */

