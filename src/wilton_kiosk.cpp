/*
 * Copyright 2018, alex at staticlibs.net
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 
 * File:   wilton_webview.cpp
 * Author: alex
 *
 * Created on April 22, 2018, 9:52 PM
 */

#include "wilton/wilton_kiosk.h"

#include "staticlib/config.hpp"

#include "wilton/support/alloc.hpp"
#include "wilton/support/buffer.hpp"
#include "wilton/support/logging.hpp"

#include "webview.hpp"
#include "webview_config.hpp"

namespace { // anonymous

const std::string logger = std::string("wilton.kiosk.webview");

} // namespace

char* wilton_kiosk_run(const char* conf, int conf_len) /* noexcept */ {
    if (nullptr == conf) return wilton::support::alloc_copy(TRACEMSG("Null 'conf' parameter specified"));
    if (!sl::support::is_uint16_positive(conf_len)) return wilton::support::alloc_copy(TRACEMSG(
            "Invalid 'conf_len' parameter specified: [" + sl::support::to_string(conf_len) + "]"));
    try {
        auto conf_json = sl::json::load({conf, conf_len});
        auto wconf = wilton::kiosk::webview_config(conf_json);
        wilton::support::log_debug(logger, std::string("Running webview,") +
                " config: [" + wconf.to_json().dumps() + "] ...");
        auto webview = wilton::kiosk::webview(std::move(wconf));
        webview.run();
        wilton::support::log_debug(logger, "Webview run completes successfully");
        return nullptr;
    } catch (const std::exception& e) {
        return wilton::support::alloc_copy(TRACEMSG(e.what() + "\nException raised"));
    }
}
