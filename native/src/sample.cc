/*
 * Copyright (C) 2017-2018 Alibaba Group Holding Limited. All Rights Reserved.
 *
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <jsni.h>
#include "CanBus.hpp"


void test() {
    CanDrv* _candrv = new CanDrv();
    if (!_candrv){

    }

    _candrv->Init(false);
    

    SigValue value;
    auto r = _candrv->Get("VehicleSpeed", &value);
}

void SayHello(JSNIEnv* env, JSNICallbackInfo info) {


    test();
    JSValueRef js_str = JSNINewStringFromUtf8(env, "Hello, World!", -1);
    JSNISetReturnValue(env, info, js_str);
}

int JSNIInit(JSNIEnv* env, JSValueRef exports) {
    JSNIRegisterMethod(env, exports, "sayHello", SayHello);
    return JSNI_VERSION_2_0;
}
