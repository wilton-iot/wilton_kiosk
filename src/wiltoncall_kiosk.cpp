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
 * File:   wiltoncall_kiosk.cpp
 * Author: alex
 *
 * Created on April 22, 2018, 9:52 PM
 */

#include <string>

#include "wilton/wilton.h"
#include "wilton/wiltoncall.h"
#include "wilton/wilton_kiosk.h"

#include "wilton/support/buffer.hpp"
#include "wilton/support/registrar.hpp"

#include "webview.hpp"

namespace wilton {
namespace kiosk {

support::buffer run(sl::io::span<const char> data) {
    // call wilton
    char* err = wilton_kiosk_run(data.data(), static_cast<int> (data.size()));
    if (nullptr != err) {
        support::throw_wilton_error(err, TRACEMSG(err));
    }
    return support::make_null_buffer();
}

} // namespace
}

extern "C" char* wilton_module_init() {
    try {
        wilton::kiosk::webview::initialize();
        wilton::support::register_wiltoncall("kiosk_run", wilton::kiosk::run);
        return nullptr;
    } catch (const std::exception& e) {
        return wilton::support::alloc_copy(TRACEMSG(e.what() + "\nException raised"));
    }
}
