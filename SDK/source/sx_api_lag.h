/*
 *  Copyright (C) 2014-2018. Mellanox Technologies, Ltd. ALL RIGHTS RESERVED.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License"); you may
 *    not use this file except in compliance with the License. You may obtain
 *    a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *    THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR
 *    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 *    LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 *    FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 *    See the Apache Version 2.0 License for specific language governing
 *    permissions and limitations under the License.
 *
 */

#ifndef __SX_API_LAG_H__
#define __SX_API_LAG_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This function sets the log verbosity level of LAG MODULE.
 * Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - LAG module verbosity level
 * @param[in] api_verbosity_level      - LAG API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_lag_log_verbosity_level_set(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               const sx_verbosity_level_t      module_verbosity_level,
                                               const sx_verbosity_level_t      api_verbosity_level);

/**
 * This function sets the log verbosity level of LAG MODULE.
 * Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - LAG module verbosity level
 * @param[out] api_verbosity_level_p    - LAG API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_lag_log_verbosity_level_get(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               sx_verbosity_level_t           *module_verbosity_level_p,
                                               sx_verbosity_level_t           *api_verbosity_level_p);

/**
 *  This function creates/destroys a new/existing LAG port group in the SDK.
 *  This function also adds/deletes ports to/from an existing LAG port group in the SDK.
 *
 *  Note:
 *  - All ports must be deleted from a LAG port groups before the group is destroyed.
 *  - Creating a LAG group and adding ports to it in the same api call is not supported.
 *
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle             - SX-API handle
 * @param[in] cmd                - CREATE/DESTROY/ADD/DELETE
 * @param[in] swid               - switch (virtual partition) ID
 * @param[in,out] lag_log_port_p - In: Already created LAG ports group ID
 *                                 Out: Newly created LAG ports group ID
 * @param[in] log_port_list_p    - List of logical ports to ADD/DELETE to/from a LAG ports group
 * @param[in] log_port_cnt       - Number of logical ports to ADD/DELETE to/from a LAG ports group
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if a requested element is not found in the DB
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceeds its range
 */
sx_status_t sx_api_lag_port_group_set(const sx_api_handle_t   handle,
                                      const sx_access_cmd_t   cmd,
                                      const sx_swid_t         swid,
                                      sx_port_log_id_t       *lag_log_port_p,
                                      const sx_port_log_id_t *log_port_list_p,
                                      const uint32_t          log_port_cnt);

/**
 *  This function retrieves an existing LAG ports group from the SDK.
 *
 *  Note: If the output ports list is NULL, only the number of ports in the LAG is retrieved.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] swid                  - switch (virtual partition) ID
 * @param[in] lag_log_port          - LAG ports group ID
 * @param[in,out] log_port_list_p   - list of logical ports
 * @param[in,out] log_port_cnt_p    - In: Number of logical ports in list
 *                                    Out: Number of logical ports in LAG
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if a requested element is not found in the DB
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceeds its range
 */
sx_status_t sx_api_lag_port_group_get(const sx_api_handle_t  handle,
                                      const sx_swid_t        swid,
                                      const sx_port_log_id_t lag_log_port,
                                      sx_port_log_id_t      *log_port_list_p,
                                      uint32_t              *log_port_cnt_p);


/**
 *  This function retrieves a list of one or more LAG IDs.
 *  The following use case scenarios apply with different input parameters
 *  X = don't-care
 *   - 1) cmd = SX_ACCESS_CMD_GET, swid = valid, lag_id = X, lag_id_list = X,
 *        lag_id_cnt = 0:
 *        In this case the API will return the total number of LAG IDs in
 *        the internal DB.
 *
 *   - 2) cmd = SX_ACCESS_CMD_GET, swid = valid, lag_id = valid/invalid,
 *        lag_id_list = valid, lag_id_cnt = 1:
 *        In this case the API will check if the specified LAG ID exists.
 *        If it does, the LAG ID will be returned in the lag_id_list along with a
 *        lag_id_cnt of 1.
 *        If the LAG ID does not exist, an empty list will be returned with
 *        lag_id_cnt = 0.
 *        A non-NULL lag_id_list pointer must be provided in this case.
 *
 *   - 3) cmd = SX_ACCESS_CMD_GET, swid = valid, lag_id = valid/invalid,
 *        lag_id_list = valid, lag_id_cnt > 1:
 *        An lag_id_cnt > 1 will be treated as a lag_id_cnt of 1 and the behavior will be
 *        same as the earlier GET use cases.
 *
 *   - 4) cmd = SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, swid = X, lag_id = X,
 *        lag_id_list = NULL, lag_id_cnt = 0:
 *        A zero lag_id_cnt and an empty lag_id_list will be returned.
 *
 *   - 5) cmd = SX_ACCESS_CMD_GET_FIRST, swid = valid, lag_id = X,
 *        lag_id_list = valid, lag_id_cnt > 0:
 *        In this case the API will return the first lag_id_cnt LAG IDs starting
 *        from the head of the database. The total number of elements fetched will be
 *        returned as lag_id_cnt. Note: returned lag_id_cnt may be less than or equal to
 *        the requested lag_id_cnt. The input LAG ID is ignored in this case.
 *        A non-NULL lag_id_list pointer must be provided in this case.
 *
 *   - 6) cmd = SX_ACCESS_CMD_GETNEXT, swid = valid, lag_id = valid/invalid,
 *        lag_id_list = valid, lag_id_cnt > 0:
 *        In this case the API will return the next set of LAG IDs starting from
 *        the next LAG ID after the specified LAG ID. The total number of
 *        elements fetched will be returned as the lag_id_cnt.
 *        Note: returned lag_id_cnt may be less than or equal to the requested lag_id_cnt.
 *        If no valid next LAG ID exists in the db, an empty list will be returned.
 *        A non-NULL lag_id_list pointer must be provided in this case.
 *
 *
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle                  - SX-API handle
 * @param [in] cmd                    - GET/GET_FIRST/GET_NEXT
 * @param[in] swid                    - virtual switch partition ID
 * @param[in] lag_id                  - LAG ID
 * @param [in] filter_p               - specify a filter parameter (not supported yet)
 * @param [out] lag_id_list_p         - return list of LAG IDs
 * @param [in,out] lag_id_cnt_p       - [in] number of LAG IDs to get
 *                                    - [out] number of LAG IDs returned
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceeds its range
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in the DB
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_lag_port_group_iter_get(const sx_api_handle_t  handle,
                                           const sx_access_cmd_t  cmd,
                                           const sx_swid_t        swid,
                                           const sx_port_log_id_t lag_id,
                                           const sx_lag_filter_t *filter_p,
                                           sx_port_log_id_t      *lag_id_list_p,
                                           uint32_t              *lag_id_cnt_p);


/**
 *  This function enables/disables collection on a specific LAG port.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] lag_log_port   - a logical port number representing
 *                             the LAG ports group
 * @param[in] log_port       - logical port number
 * @param[in] collector_mode - collector mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 */

sx_status_t sx_api_lag_port_collector_set(const sx_api_handle_t     handle,
                                          const sx_port_log_id_t    lag_log_port,
                                          const sx_port_log_id_t    log_port,
                                          const sx_collector_mode_t collector_mode);


/**
 *  This function returns information whether collection is enabled
 *  or disabled on a specific port in a LAG port.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle            - SX-API handle.
 * @param[in] lag_log_port      - a logical port number representing
 *                                the LAG ports group
 * @param[in] log_port          - logical port number
 * @param[out] collector_mode_p - collector mode.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameter exceeds its range
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 */

sx_status_t sx_api_lag_port_collector_get(const sx_api_handle_t  handle,
                                          const sx_port_log_id_t lag_log_port,
                                          const sx_port_log_id_t log_port,
                                          sx_collector_mode_t   *collector_mode_p);

/**
 *  This function enables/disables distribution on a specific LAG port.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] lag_log_port     - a logical port number representing
 *                               the LAG ports group
 * @param[in] log_port         - logical port number
 * @param[in] distributor_mode - distributor mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_ENTRY_ALREADY_EXISTS if requested element is already exists
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 */
sx_status_t sx_api_lag_port_distributor_set(const sx_api_handle_t       handle,
                                            const sx_port_log_id_t      lag_log_port,
                                            const sx_port_log_id_t      log_port,
                                            const sx_distributor_mode_t distributor_mode);


/**
 *  This function returns information whether distribution is enabled
 *  or disabled on a specific port in a LAG port.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle              - SX-API handle.
 * @param[in] lag_log_port        - a logical port number representing
 *                                  the LAG ports group
 * @param[in] log_port            - logical port number
 * @param[out] distributor_mode_p - distributor mode.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameter exceeds its range
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 */

sx_status_t sx_api_lag_port_distributor_get(const sx_api_handle_t  handle,
                                            const sx_port_log_id_t lag_log_port,
                                            const sx_port_log_id_t log_port,
                                            sx_distributor_mode_t *distributor_mode_p);

/**
 *  This function configures the flow indicators that impact the
 *  LAG hash distribution function.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 *  @param[in] handle               - SX-API handle
 *  @param[in] lag_hash_param_p     - hash parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_NO_MEMORY if memory allocation fails
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceeds its range
 */
sx_status_t sx_api_lag_hash_flow_params_set(const sx_api_handle_t      handle,
                                            const sx_lag_hash_param_t *lag_hash_param_p);


/**
 * This function sets the ingress port configuration parameters of LAG hash.
 * Once this API is called sx_api_lag_hash_params_set is disabled.
 *
 * Command SET replaces existing hash parameters, fields enables and fields with new values.
 * Command ADD adds new fields and fields enables to existing ones. Hash parameters are ignored
 * Command DELETE deletes specific fields and fields enables from the existing ones. Hash parameters are ignored
 * Each element in hash_field_enable_list_p enables a specific layer field to be
 * included in the hash calculation according to the de-facto fields of the
 * parsed packet.
 * Each element in hash_field_list_p represents a different field to
 * be included in the hash calculation, subject to the enables which are given in hash_field_enable_list_p.
 * LAG hash parameters are configured per ingress port and impact egress LAG.
 *
 * Supported devices: Spectrum
 *
 * @param[in] handle                     - SX-API handle.
 * @param[in] cmd                        - SET/ ADD/ DELETE.
 * @param[in] log_port                   - log port ID of ingress port
 * @param[in] lag_hash_params_p          - LAG hash configuration parameters.
 * @param[in] hash_field_enable_list_p   - Array of enables to be included in the hash calculation (may be NULL if empty)
 * @param[in] hash_field_enable_list_cnt - Number of elements in hash_field_enable_list_p
 * @param[in] hash_field_list_p          - Array of fields to be included in the hash calculation (may be NULL if empty)
 *                                         Note that for Spectrum-1 the custom_bytes are not supported
 * @param[in] hash_field_list_cnt        - Number of elements in hash_field_list_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_NULL if parameter is incorrectly NULL.
 * @return SX_STATUS_ERROR general error.
 */

sx_status_t sx_api_lag_port_hash_flow_params_set(const sx_api_handle_t             handle,
                                                 const sx_access_cmd_t             cmd,
                                                 const sx_port_log_id_t            log_port,
                                                 const sx_lag_port_hash_params_t  *hash_params_p,
                                                 const sx_lag_hash_field_enable_t *hash_field_enable_list_p,
                                                 const uint32_t                    hash_field_enable_list_cnt,
                                                 const sx_lag_hash_field_t        *hash_field_list_p,
                                                 const uint32_t                    hash_field_list_cnt);


/**
 *  This function retrieves the flow indicators that impact the
 *  LAG hash distribution function.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 *  @param[in] handle               - SX-API handle
 *  @param[out] lag_hash_param_p    - hash parameters to be retrieved
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 */
sx_status_t sx_api_lag_hash_flow_params_get(const sx_api_handle_t handle,
                                            sx_lag_hash_param_t  *lag_hash_param_p);

/**
 *  This function gets the LAG hash function configuration parameters.
 *  if the given number of fields / field enables is 0, the API will only return number of
 *  fields / field enables.
 * Once this API is called sx_api_lag_hash_params_get is disable
 *
 * Supported devices: Spectrum.
 *
 * @param[in]     handle                       - SX-API handle.
 * @param[in]     log_port                     - local port
 * @param[out]    lag_hash_params_p            - LAG hash configuration parameters.
 * @param[out]    hash_field_enable_list_p     - array of enables used in the hash calculation
 * @param[in/out] hash_field_enable_list_cnt_p - number of objects in hash_field_list_p
 * @param[out]    hash_field_list_p            - array of fields used in the hash calculation
 * @param[in/out] hash_field_list_cnt_p        - number of objects in hash_field_list_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_lag_port_hash_flow_params_get(const sx_api_handle_t       handle,
                                                 const sx_port_log_id_t      log_port,
                                                 sx_lag_port_hash_params_t  *lag_hash_params_p,
                                                 sx_lag_hash_field_enable_t *hash_field_enable_list_p,
                                                 uint32_t                   *hash_field_enable_list_cnt_p,
                                                 sx_lag_hash_field_t        *hash_field_list_p,
                                                 uint32_t                   *hash_field_list_cnt_p);

/**
 *  This function CREATEs/DESTROYs a redirection between a LAG and a
 *  destination LAG.
 *  Redirection doesn't align LAG configuration, only TX traffic.
 *
 *  Note:
 *  - Redirect operation is valid only between 2 LAGs. Cannot create chain of
 *    redirected LAGs.
 *  - Redirect is L2 action, and not valid for Router Port.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] cmd                   - CREATE/DESTROY
 * @param[in] lag_log_port          - LAG logical ID
 * @param[in] redirect_lag_log_port - LAG logical ID which lag_log_port now
 *                                    points to. Ignored in DESTROY command.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 */
sx_status_t sx_api_lag_redirect_set(const sx_api_handle_t  handle,
                                    const sx_access_cmd_t  cmd,
                                    const sx_port_log_id_t lag_log_port,
                                    const sx_port_log_id_t redirect_lag_log_port);

/**
 *  This function returns information whether a given LAG is redirected.
 *  If so, the redirected LAG logical ID is return.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle                     - SX-API handle.
 * @param[in] lag_log_port               - LAG logical ID.
 * @param[out] is_redirected_p           - is lag_port redirected.
 * @param[out] redirected_lag_log_port_p - the LAG logical ID which lag_log_port
 *                                         point to.
 *                                         Valid when the LAG is redirected.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 */
sx_status_t sx_api_lag_redirect_get(const sx_api_handle_t  handle,
                                    const sx_port_log_id_t lag_log_port,
                                    boolean_t             *is_redirected_p,
                                    sx_port_log_id_t      *redirected_lag_log_port_p);

/**
 *  This function returns all LAGs redirected to the given LAG.
 *  Call this API with lag_log_port_list_p=NULL will set to lag_log_port_cnt_p
 *  the number of LAG redirected to lag_port.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] lag_log_port              - LAG logical ID
 * @param[in,out] lag_log_port_list_p   - pointer to array of LAG port list
 * @param[in,out] lag_log_port_cnt_p    - number of LAG ports in a list retrieve
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 */
sx_status_t sx_api_lag_redirected_lags_get(const sx_api_handle_t  handle,
                                           const sx_port_log_id_t lag_log_port,
                                           sx_port_log_id_t      *lag_log_port_list_p,
                                           uint32_t              *lag_log_port_cnt_p);

/**
 *  This function sets a fine grained LAG distribution list.
 *  Lag distribution will be according to the given port list with relative weight.
 *
 *  Note:
 *  - Setting the distribution list is optional and only affects unicast traffic.
 *  - In case the distribution list is not set the hash will be done according to the LAG member ports.
 *  - Port may be not a LAG member.
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle       - SX-API handle.
 * @param[in] access_cmd   - SET/ADD/DELETE/DELETE_ALL.
 *       SET - LAG distribution list according to port list with relative weight.
 *       ADD - Add ports to the existing LAG distribution list.
 *       DELETE - Delete ports from distribution list.
 *       DELETE ALL - return to the default distribution function.
 * @param[in] lag_log_port - logical port number representing the LAG.
 * @param[in] params_p     - the fine grain lag parameters. Controls the resolution of the distribution list.
 *                           valid for SET command only.
 * @param[in] port_list_p  - list of ports to SET/ADD/DELETE distribution list with weights.
 *                           On add the members should not exist in the LAG distribution list.
 *                           On delete the members should exist in the LAG distribution list.
 * @param[in] port_cnt     - number of elements on port_list_p
 *
 * @return SX_STATUS_SUCCESS - Operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE - Invalid handle.
 * @return SX_STATUS_PARAM_ERROR - Parameter is invalid.
 * @return SX_STATUS_NO_RESOURCES if there are no more resources.
 * @return SX_STATUS_CMD_UNSUPPORTED - Access Command isn't supported.
 */
sx_status_t sx_api_lag_distributer_list_set(const sx_api_handle_t             handle,
                                            const sx_access_cmd_t             access_cmd,
                                            const sx_port_log_id_t            lag_log_port,
                                            const sx_lag_fine_grain_params_t *params_p,
                                            const sx_lag_fine_grain_member_t *port_list_p,
                                            const uint32_t                    port_cnt);

/**
 *  This function retrieves a fine grained LAG distribution list and the fine grain lag parameters.
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle             - SX-API handle.
 * @param[in] lag_log_port       - logical port number representing the LAG.
 * @param[out] params_p          - the fine grained lag parameters.
 * @param[out] port_list_p       - list of ports and weights in the advance distribution port list.
 * @param[in/out] port_cnt_p     - number of ports in the distribution list
 *
 * @return SX_STATUS_SUCCESS - Operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE - Invalid handle.
 * @return SX_STATUS_PARAM_ERROR - Parameter is invalid.
 */
sx_status_t sx_api_lag_distributer_list_get(const sx_api_handle_t       handle,
                                            const sx_port_log_id_t      lag_log_port,
                                            sx_lag_fine_grain_params_t *params_p,
                                            sx_lag_fine_grain_member_t *port_list_p,
                                            uint32_t                   *port_cnt_p);


#endif /* __SX_API_LAG_H__ */
