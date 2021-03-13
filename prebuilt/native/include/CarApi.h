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

#ifndef CARAPI_INC_CARAPI_H_
#define CARAPI_INC_CARAPI_H_

#include <memory>
#include "CarSrvTypes.h"

namespace carsrv {

class CarApiImpl;

class CarApi
{
public:
    CarApi();
    virtual ~CarApi();

    /**
    * Init function.The process which use carapi should be in the white list.
    * @param auto_switch:
    *    if true:
    *        when carservice is working, it will listen and get signal from carservice
    *        when carservice is not working, it will listen and get signal from ipcl
    *    if false:it alwasy listen and get signal from ipcl
    * Note: regarding to Set function, whether auto_switch is true or not, it will switch
    * @param enable_set: if need to Set function, set enable_set true, otherwise false
    */
    void Init(bool auto_switch = true, bool enable_set = false);

    /**
     * Shutdown. only call it when process exit
     */
    void Shutdown();

    /**
     * Subscribe a signal
     * @param name     : signal name
     * @param callback : callback function
     * @param passthrough   : true, transmit value passthrough, otherwise
     * carapi will do some filter.
     */
    void Subscribe(const SigName& name,
                   const CarSrvSigCb& callback,
                   bool passthrough = true);

    /**
     * Subscribe CarService status, onbirth or ondeath
     * @param callback : callback function
     */
    void SubscribeCarServiceStatus(const CarSrvStatusCb& callback);

    /**
     * Get value of a signal
     * @param  name: signal name
     * @param  value :value. out param
     * @param  timeout : timeout interval, ms
     * @return : true, success; false: failed.
     * Note: if auto_switch is true, it will switch
    *    to carservice when carservice is working and switch to ipcl
    *    when carservice is not working.
     */
    bool Get(const SigName& name, SigValue* value, int timeout = 3000);

    /**
     * Set value of a signal
     * @param  name: signal name
     * @param  value :value
     * @return : true, success; false: failed.     *
     * Note: no matter auto_switch is true for false, it will switch
    *    to carservice when carservice is working and switch to ipcl when carservice is
    *    not working.
     */
    bool Set(const SigName& name, const SigValue& value);

private:
    std::shared_ptr<CarApiImpl> impl_;
};

}    // namespace carsrv

#endif  // CARAPI_INC_CARAPI_H_
