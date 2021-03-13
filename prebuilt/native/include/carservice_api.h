/**************************************************************************
 *
 * Copyright (c) 2014-2020 Banma Network Technology Co.,Ltd
 *                       All rights reserved.
 *
 * This software is supplied only under the terms of a license agreement,
 * nondisclosure agreement or other written agreement with Banma
 * Network Technology Co.,Ltd. Use, redistribution or other disclosure
 * of any parts of this software is prohibited except in accordance with
 * the terms of such written agreement with Banma Network Technology
 * Co.,Ltd. This software is confidential and proprietary information of
 * Banma Network Technology Co.,Ltd.
 *
 **************************************************************************/

#ifndef CARLIB_INC_CARSERVICE_API_H_
#define CARLIB_INC_CARSERVICE_API_H_

/**
 * sample code:
* @Init
      std::shared_ptr<mal::IpcPeerChan> peer_chan_;
      peer_chan_ = IpcFactory().CreatePeerChan(IpcPath(kCarSrvBusName,
                  kCarSrvPath, kCarSrvIf));
      if (peer_chan_ == nullptr) {
        LOG_E("peer_chan_ is nullptr");
        return -1;
      }
 * @Subscribe
    peer_chan_->Subscribe("ctrl.sys.power_status",
    [](const shared_ptr<IpcPacket>& packet) {
        auto msg = packet->ReadString();
        Json::Reader reader;
        Json::Value root;

        if (!(reader.parse(msg, root) && root[kSignalValueKey].isString())) {
            LOG_E("subscribePowerStatus format error:%s", msg.c_str());
            return;
        }

        string signal_value = root[kSignalValueKey].asString();

        if ((signal_value == kInvalidSignal)
            || (signal_value == kUninitSignal)
            || (signal_value == kIgnoredSignal)) {
            return;
        }

        int power_status = atoi(signal_value.c_str());
        LOG_I("subscribePowerStatus power_status:%d", power_status);
    });
 *
 */
const char* const kCarSrvBusName = "com.banma.ivi.carservice";
const char* const kCarSrvPath = "/com/banma/ivi/carservice";
const char* const kCarSrvIf = kCarSrvBusName;

/**
 * get signal value
 * @return json format string.
   case1: {"ret":"OK","sigName":"ctrl.sys.gear_status", "sigVal":"1"}, success, int value
   case2: {"ret":"OK", "sigName":"ctrl.sys.vehicle_speed","sigVal":"12.5"},
           success, float value
   case3: {"ret":"OK", "sigName":"ctrl.sys.vehicle_speed","sigVal":"Invalid"},
          success, but value is invalid
   case4: {"ret":"OK", "sigName":"ctrl.sys.vehicle_speed", "sigVal":"No Signal"},
          success, but no value received from CAN
   case5: {"kErrKey":"Signal is not supported","ret":"NG","sigName":"ctrl.sys.gear_status2",
        "sigVal":"Invalid"},failed, signal is invalid
 *
 * sample code:
 * @Get PowerStatus
    auto packet = peer_chan_->CreateRequestPacket(kGetValue);
    packet->WriteString("ctrl.sys.power_status");
    IpcResult ret = peer_chan_->RequestSync(packet, 3000);

    if (!ret.IsReplyOK()) {
        LOG_E("%s,error code: %d", __FUNCTION__, ret.GetErrorCode());
        return;
    }

    auto result = ret.GetReply()->ReadString();
    Json::Reader reader;
    Json::Value root;

    if (!(reader.parse(result, root)
          && root[kResultKey].isString()
          && (root[kResultKey].asString() == kResultOK))) {
        LOG_E("%s,error:%s", __FUNCTION__, result.c_str());
        return;
    }

    if (root[kSignalValueKey].isString()) {
        string signal_value = root[kSignalValueKey].asString();

        if ((signal_value == kInvalidSignal)
            || (signal_value == kUninitSignal)
            || (signal_value == kIgnoredSignal)) {
            return;
        }

        int power_status = atoi(signal_value.c_str());
        LOG_I("status:%d", power_status);
    }

 * @Get VehicleSpeed
    auto packet = peer_chan_->CreateRequestPacket(kGetValue);
    packet->WriteString("ctrl.sys.vehicle_speed");
    IpcResult ret = peer_chan_->RequestSync(packet, 3000);

    if (!ret.IsReplyOK()) {
        LOG_E("%s,error code: %d", __FUNCTION__, ret.GetErrorCode());
        return;
    }

    auto result = ret.GetReply()->ReadString();
    Json::Reader reader;
    Json::Value root;

    if (!(reader.parse(result, root)
          && root[kResultKey].isString()
          && (root[kResultKey].asString() == kResultOK))) {
        LOG_E("%s,error:%s", __FUNCTION__, result.c_str());
        return;
    }

    if (root[kSignalValueKey].isString()) {
        string signal_value = root[kSignalValueKey].asString();

        if ((signal_value == kInvalidSignal)
            || (signal_value == kUninitSignal)
            || (signal_value == kIgnoredSignal)) {
            return;
        }

        float speed = atof(signal_value.c_str());
        LOG_I("peed:%f", speed);
    }
 */
const char* const kGetValue = "GetValue";

/**
 * set signal value
 * @return json format string.
   case1: {"ret":"OK"}, success
   case2: {"kErrKey":"Signal is not supported","ret":"NG"}  failed, signal is invalid
   case3: {"ret":"NG"}
 * sample code:
    auto packet = peer_chan_->CreateRequestPacket(kSetValue);
    packet->WriteString("ctrl.ac.power_status");
    packet->WriteString("1");
    IpcResult ret = peer_chan_->RequestSync(packet, 3000);

    if (!ret.IsReplyOK()) {
        LOG_E("%s,error code: %d", __FUNCTION__, ret.GetErrorCode());
        return;
    }

    auto result = ret.GetReply()->ReadString();
    Json::Reader reader;
    Json::Value root;

    LOG_E("SetAcPowerStatus: result:%s", result.c_str());

    if (!(reader.parse(result, root)
          && root[kResultKey].isString()
          && (root[kResultKey].asString() == kResultOK))) {
        LOG_E("%s,error:%s", __FUNCTION__, result.c_str());
    }
 */
const char* const kSetValue = "SetValue";

/**
 * get one or more signal value
 * @return string.
   case1: json format {"ctrl.sys.gear_status":"0",
                       "ctrl.sys.vehicle_speed":"0"}, success
   case2: "Invalid"
 *
 * sample code:
    auto packet = peer_chan_->CreateRequestPacket(kGetMultiValue);
    Json::Value root;
    root[kGetMultiKey].append("ctrl.sys.vehicle_speed");
    root[kGetMultiKey].append("ctrl.sys.gear_status");
    Json::FastWriter writer;
    string param = writer.write(root);

    packet->WriteString(param);
    IpcResult ret = peer_chan_->RequestSync(packet, 3000);

    if (!ret.IsReplyOK()) {
        LOG_E("%s,error code: %d", __FUNCTION__, ret.GetErrorCode());
        return;
    }

    auto result = ret.GetReply()->ReadString();
    Json::Reader reader;
    Json::Value result_root;
    LOG_I("result: %s", result.c_str());

    if (!reader.parse(result, result_root)) {
        LOG_E("%s,error:%s", __FUNCTION__, result.c_str());
        return;
    }

    if (result_root["ctrl.sys.gear_status"].isString()) {
        string signal_value = result_root["ctrl.sys.gear_status"].asString();

        if ((signal_value != kInvalidSignal)
            && (signal_value != kUninitSignal)
            && (signal_value != kIgnoredSignal)) {
            int value = atoi(signal_value.c_str());
            LOG_I("GearStatus:%d", value);
        }
    }

    if (result_root["ctrl.sys.vehicle_speed"].isString()) {
        string signal_value = result_root["ctrl.sys.vehicle_speed"].asString();

        if ((signal_value != kInvalidSignal)
            && (signal_value != kUninitSignal)
            && (signal_value != kIgnoredSignal)) {
            float value = atof(signal_value.c_str());
            LOG_I("VehicleSpeed:%f", value);
        }
    }
 */
const char* const kGetMultiValue = "GetMultiValue";
const char* const kGetMultiKey = "getmulti";

/**
 * get all warning status
 * @return json format string.
   e.g. json format {"FrontAxlePressureImbalance":"0",
   "FrontLeftTireStatus":"0","FrontRightTireStatus":"0",
   "FuelStatusWarning":"0","RearAxlePressureImbalance":"0",
   "RearLeftTireStatus":"0","RearRightTireStatus":"0",
   "SecurityKeyBatteryLowWarning":"0","WasherFluidLowWarning":"0"}
 *
 * sample code:
    auto packet = peer_chan_->CreateRequestPacket(kReqAllWarnningStatus);
    IpcResult ret = peer_chan_->RequestSync(packet, 3000);

    if (!ret.IsReplyOK()) {
        LOG_E("%s,error code: %d", __FUNCTION__, ret.GetErrorCode());
        return;
    }

    auto result = ret.GetReply()->ReadString();
    Json::Reader reader;
    Json::Value result_root;

    LOG_I("result: %s", result.c_str());

    if (!reader.parse(result, result_root)) {
        LOG_E("%s,error:%s", __FUNCTION__, result.c_str());
        return;
    }
 */
const char* const kReqAllWarnningStatus = "ReqAllWanningStatus";

/**
 * get all abnormal status
 *
 * sample code:
    auto packet = peer_chan_->CreateRequestPacket(kReqAllAbnormalStatus);
    IpcResult ret = peer_chan_->RequestSync(packet, 3000);

    if (!ret.IsReplyOK()) {
        LOG_E("%s,error code: %d", __FUNCTION__, ret.GetErrorCode());
        return;
    }

    auto result = ret.GetReply()->ReadString();
    Json::Reader reader;
    Json::Value result_root;

    LOG_I("result: %s", result.c_str());

    if (!reader.parse(result, result_root)) {
        LOG_E("%s,error:%s", __FUNCTION__, result.c_str());
        return;
    }
 */
const char* const kReqAllAbnormalStatus = "ReqAllAbnormalStatus";

/**
 * get all maintance status
 *
 * sample code:
    auto packet = peer_chan_->CreateRequestPacket(kReqAllMaintCarStatus);
    IpcResult ret = peer_chan_->RequestSync(packet, 3000);

    if (!ret.IsReplyOK()) {
        LOG_E("%s,error code: %d", __FUNCTION__, ret.GetErrorCode());
        return;
    }

    auto result = ret.GetReply()->ReadString();
    Json::Reader reader;
    Json::Value result_root;

    LOG_I("result: %s", result.c_str());

    if (!reader.parse(result, result_root)) {
        LOG_E("%s,error:%s", __FUNCTION__, result.c_str());
        return;
    }
 */
const char* const kReqAllMaintCarStatus = "ReqAllMaintCarStatus";
const char* const kGetElecConsumption = "GetElecCsump";
const char* const kGetFuelConsumption = "GetFuelCsump";

/**
 * Get signal status: 1 is supported, 0 is unsupported,
 * the parameter can be one signal or multiple signals splited with ",".
 * @return json format string.
   case1: {"ctrl.engine.status":{"get":1,"pub":1,"set":0}}
   case2: {"ctrl.ac.power_status":{"get":1,"pub":1,"set":1},
          "ctrl.air_cleaner.filter_reset":{"get":0,"pub":0,"set":1},
          "ctrl.sys.power_status":{"get":1,"pub":1,"set":0}}
 *
 * sample code:
 * @Get ctrl.engine.status support status
    auto packet = peer_chan_->CreateRequestPacket(kGetSignalStatus);
    packet->WriteString("ctrl.engine.status");
    IpcResult ret = peer_chan_->RequestSync(packet, 3000);

    if (!ret.IsReplyOK()) {
        LOG_E("%s,error code: %d", __FUNCTION__, ret.GetErrorCode());
        return;
    }

    auto result = ret.GetReply()->ReadString();
    Json::Reader reader;
    Json::Value root;

    if (!(reader.parse(result, root))) {
        LOG_E("%s,error:%s", __FUNCTION__, result.c_str());
        return;
    }

    if (!root.isMember(ctrl.engine.status)) {
        LOG_E("%s, has no member ctrl.engine.status!", __FUNCTION__);
        return;
    }

    Json::Value& status = root[ctrl.engine.status];

    if (!status.isMember(kSetKey)) {
        LOG_E("%s, has no member set!", __FUNCTION__);
        return;
    }

    LOG_I("ctrl.engine.status: set: %d", status[kSetKey].asInt());

    if (!status.isMember(kGetKey)) {
        LOG_E("%s, has no member get!", __FUNCTION__);
        return;
    }

    LOG_I("ctrl.engine.status: get: %d", status[kGetKey].asInt());

    if (!status.isMember(kPubKey)) {
        LOG_E("%s, has no member pub!", __FUNCTION__);
        return;
    }

    LOG_I("ctrl.engine.status: pub: %d", status[kPubKey].asInt());
 */
const char* const kGetSignalStatus = "GetSignalStatus";

// result key
const char* const kResultKey = "ret";
// result OK
const char* const kResultOK = "OK";
// result NOK
const char* const kResultNG = "NG";
// error information key
const char* const kErrKey = "errcode";
// methoed is unsupported
const char* const kMethodUnsupported = "Method is not supported";
// signal is unsupported
const char* const kSignalUnsupported = "Signal is not supported";
// no persmission
const char* const kPermissionError = "No permission";

// signal value key
const char* const kSignalValueKey = "sigVal";
// invalid value
const char* const kInvalidSignal = "Invalid";
// default value of each signal
const char* const kUninitSignal = "No Signal";
// ignored value of signals
const char* const kIgnoredSignal = "Ignored";

// signal support status set key
const char* const kSetKey = "set";
// signal support status get key
const char* const kGetKey = "get";
// signal support status pub key
const char* const kPubKey = "pub";

enum class GearStatus
{
    kBetween = 0,
    kGearP = 1,
    kGearR = 2,
    kGearN = 3,
    kGearA = 4,
    kGearB = 5,
    kGearC = 6,
    kGearD = 7,
    kGearE = 8,
    kGearF = 9,
    kGearG = 10,
    kGearH = 11,
    kReserved,
    kInvalid = 0xf,
};

enum class FuelType
{
    kOilWear,
    kMixSport,
    kElectric,
    kInvalid
};

enum class EngineStatus
{
    kOff = 0,
    kOn,
    kInvalid
};

enum class PowerStatus
{
    kOff,
    kAcc,
    kRun,
    kCrank,
    kInvalid
};

enum class SideLightStatus
{
    kOff,
    kLeft,
    kRight,
    kAll,
    kInvalid
};

enum class DoorStatus
{
    kClosed,
    kOpen,
    kAjar,
    kFullOpen,
    kInvalid
};

enum class TailGateStatus
{
    kSysFault = 0,
    kSysLimit,
    kFullOpen,
    kFullClose,
    kOpening,
    kClosing,
    kMiddleStop,
    kTransition,
    kInvalid
};

enum class TpmStatus
{
    kNormal = 0,
    kUnnormal,
    kInvalid
};

enum class TirePressureUnit
{
    kBar,
    kKpa,
    kInvalid
};

enum class WarningType
{
    kNoWarning,
    kWarning
};

enum class Transmission
{
    kMt,
    kAt,
    kInvalid
};

enum class GearboxType
{
    kAT = 0,
    kMT,
    kAMT,
    kCVT,
    kDCT
};

enum class AcAirMode
{
    kFace = 0,
    kFaceFoot = 1,
    kFoot = 2,
    kAuto = 7
};

enum class FuelStatus
{
    kOk = 0,
    kLow = 1,
    kCritical = 2,
    kInvalid = 3
};

#endif  // CARLIB_INC_CARSERVICE_API_H_
