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
 * File:   webview.hpp
 * Author: alex
 *
 * Created on April 22, 2018, 10:15 PM
 */

#ifndef WILTON_KIOSK_WEBVIEW_HPP
#define WILTON_KIOSK_WEBVIEW_HPP

#include <cstdint>
#include <string>

#include "staticlib/config.hpp"
#include "staticlib/io.hpp"
#include "staticlib/pimpl.hpp"

#include "webview_config.hpp"

namespace wilton {
namespace kiosk {

class webview : public sl::pimpl::object {
protected:
    /**
     * implementation class
     */
    class impl;

public:
    /**
     * PIMPL-specific constructor
     * 
     * @param pimpl impl object
     */
    PIMPL_CONSTRUCTOR(webview)

    webview(webview_config&& conf);

    void run();

    static void initialize();
};

} // namespace
}

#endif /* WILTON_KIOSK_WEBVIEW_HPP */

