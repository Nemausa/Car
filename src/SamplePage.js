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

//jscs:disable
/* jshint ignore:start */
"use strict";
process.env.CAFUI2 = true;
var Page = require("yunos/page/Page");
var TextView = require("yunos/ui/view/TextView");
var native = nativeLoad("sample.so");

class SamplePage extends Page {
    onStart() {
        var textView = new TextView();
        textView.text = native.sayHello();
        textView.width = this.window.width;
        textView.height = this.window.height;
        textView.fontSize = 100;
        textView.color = "#FFFFFF";
        textView.background = "#FF6600";
        textView.align = TextView.Align.Center;
        textView.verticalAlign = TextView.VerticalAlign.Middle;
        this.window.addChild(textView);
    }
}
module.exports = SamplePage;
/* jshint ignore:end */
