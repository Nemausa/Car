/**************************************************************************
 *
 *  Copyright  (c)  2014-2020 Banma Network Technology Co.,Ltd
 *                         All rights reserved.
 *
 *  This software is supplied only under the terms of a license agreement,
 *  nondisclosure agreement or other written agreement with Banma
 *  Network Technology Co.,Ltd. Use, redistribution or other disclosure
 *  of any parts of this software is prohibited except in accordance with
 *  the terms of such written agreement with Banma Network Technology
 *  Co.,Ltd. This software is confidential and proprietary information of
 *  Banma Network Technology Co.,Ltd.
 *
 **************************************************************************/

#ifndef CARLIB_INC_CARSRVTYPES_H_
#define CARLIB_INC_CARSRVTYPES_H_

#include <string>
#include <functional>

#include "carservice_api.h"

#define IPCL_CAN_SIGNAL_EVENT_KEY "IPCL_CAN_SIGNAL_EVENT"
#define IPCL_CAN_STATUS_EVENT_KEY "IPCL_CAN_STATUS_EVENT"
#define IPCL_CAN_MULTI_SIGNAL_KEY "IPCL_CAN_MULTI_SIGNAL"
#define IPCL_CAN_USDT_SIGNAL_KEY "IPCL_CAN_USDT_SIGNAL"

enum IPCL_CAN_CTL_ID
{
    IPCL_CAN_DISABLE_EVENT = 0,
    IPCL_CAN_ENABLE_EVENT,
    IPCL_CAN_GET_FULL_DATA,
};

// IPCL CAN event type
enum IPCL_CAN_EVENT_TYPE
{
    IPCL_CAN_CTL_EVENT = 1,
    IPCL_CAN_SIGNAL_EVENT,
};

typedef uint16_t SigId;
typedef std::string FuncName;
typedef std::string SigName;
typedef std::string SigValue;


namespace carsrv {

enum SigErr
{
    kNoError = 0,
    kIpclUnready,
    kSigMgrInvalid,
    kSignalUnknown,
    kNoRxSig,
    kNoTxSig,
    kMissedSpecialHandler,
    kNullPtr,
    kParamInvalid,
    kRxValInvalid,
    kTxValInvalid,
    kBusy,
    kNoReply,
    kNoPermission,
    kError
};

enum SigType
{
    kRx,
    kTx
};

enum SwitchType
{
    kStatusOff,
    kStatusOn
};

enum HandlerType
{
    kCommonHandler,
    kSpecialHandler,
    kTxValidation,
    kTxValidation2,
    kTxBtn,
    kTriggerBtn,
    kAlarm,
    kUnknownHandlerType
};

enum class SeatHeatType
{
    kHigh,
    kLow,
    kUnknown
};

struct CalcParam
{
    float scale;
    float offset;
    bool  is_valid;
};

struct SigRange
{
    int64_t min_value;
    int64_t max_value;
    bool    is_valid;
};

struct SigData
{
    SigId rx_id;
    SigId tx_id;
    SigId tx_v_id;
    uint8_t len;
    CalcParam calc_param;
    SigRange range;
    int type;
    uint64_t interval;
};

/**
 * When receive signal, it need to call this interface to
 * trigger the callback
 * @param param1: signal name
 * @param param2: json format. for example: "{"sigVal":"1"}"
 */
using CarSrvSigCb = std::function<void(const SigName&,
                                       const std::string&)>;
using CarSrvStatusCb = std::function<void(bool)>;

// virtual receive signal ID
const uint16_t kVirtualRxSignal = 0xfffb;
// virtual transmit signal ID
const uint16_t kVirtualTxSignal = 0xfffc;
// No transmit valid signal ID
const uint16_t kIdNoTxVSignal = 0xfffd;
// No receive signal ID
const uint16_t kIdNoRxSignal = 0xfffe;
// No transmit signal ID
const uint16_t kIdNoTxSignal = 0xffff;


const char* const kTotalDistance = "total_dist";
const char* const kAcAirSpeed = "ac_air_speed";

}  // namespace carsrv
#endif  // CARLIB_INC_CARSRVTYPES_H_
