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
 * File:   webview_config.hpp
 * Author: alex
 *
 * Created on April 22, 2018, 10:03 PM
 */

#ifndef WILTON_KIOSK_WEBVIEW_CONFIG_HPP
#define WILTON_KIOSK_WEBVIEW_CONFIG_HPP

#include <cstdint>
#include <string>

#include "staticlib/config.hpp"
#include "staticlib/support.hpp"
#include "staticlib/json.hpp"

#include "wilton/support/exception.hpp"

namespace wilton {
namespace kiosk {

class webview_config {
public:
    std::string url;
    bool fullscreen = true;
    // defaults are updated inside webview
    uint32_t fullscreen_key = 0;
    uint32_t close_key = 0;
    uint16_t window_width = 640;
    uint16_t window_height = 480;
    bool console_to_stdout = false;
    bool inspector_mode = false;
    bool enable_wilton_calls = false;
    std::string title;
    std::string icon_path;

    webview_config(const webview_config&) = delete;

    webview_config& operator=(const webview_config&) = delete;

    webview_config(webview_config&& other) :
    url(std::move(other.url)),
    fullscreen(other.fullscreen),
    fullscreen_key(other.fullscreen_key),
    close_key(other.close_key),
    window_width(other.window_width),
    window_height(other.window_height),
    console_to_stdout(other.console_to_stdout),
    inspector_mode(other.inspector_mode),
    enable_wilton_calls(other.enable_wilton_calls),
    title(std::move(other.title)),
    icon_path(std::move(other.icon_path)) { }

    webview_config& operator=(webview_config&& other) {
        url = std::move(other.url);
        fullscreen = other.fullscreen;
        fullscreen_key = other.fullscreen_key;
        close_key = other.close_key;
        window_width = other.window_width;
        window_height = other.window_height;
        console_to_stdout = other.console_to_stdout;
        inspector_mode = other.inspector_mode;
        enable_wilton_calls = other.enable_wilton_calls;
        title = std::move(other.title);
        icon_path = std::move(other.icon_path);
        return *this;
    }

    webview_config() { }

    webview_config(const sl::json::value& json) {
        for (const sl::json::field& fi : json.as_object()) {
            auto& name = fi.name();
            if ("url" == name) {
                this->url = fi.as_string_nonempty_or_throw(name);
            } else if("fullscreen" == name) {
                this->fullscreen = fi.as_bool_or_throw(name);
            } else if("fullscreenKey" == name) {
                this->fullscreen_key = fi.as_uint32_positive_or_throw(name);
            } else if("closeKey" == name) {
                this->close_key = fi.as_uint32_positive_or_throw(name);
            } else if("windowWidth" == name) {
                this->window_width = fi.as_uint16_positive_or_throw(name);
            } else if("windowHeight" == name) {
                this->window_height = fi.as_uint16_positive_or_throw(name);
            } else if("consoleToStdout" == name) {
                this->console_to_stdout = fi.as_bool_or_throw(name);
            }  else if("inspectorMode" == name) {
                this->inspector_mode = fi.as_bool_or_throw(name);
            }  else if("enableWiltonCalls" == name) {
                this->enable_wilton_calls = fi.as_bool_or_throw(name);
            }  else if("windowTitle" == name) {
                this->title = fi.as_string_nonempty_or_throw(name);
            }  else if("windowIconPath" == name) {
                this->icon_path = fi.as_string_nonempty_or_throw(name);
            }  else if("fxStageCallback" == name) {
                // ignore on linux
            } else {
                throw support::exception(TRACEMSG("Unknown 'webview_config' field: [" + name + "]"));
            }
        }
        if (url.empty()) throw support::exception(TRACEMSG(
                "Invalid 'webview.url' field: []"));
    }

    sl::json::value to_json() const {
        return {
            { "url", url },
            { "fullscreen", fullscreen },
            { "fullscreenKey", fullscreen_key },
            { "closeKey", close_key },
            { "windowHeight", window_height },
            { "windowWidth", window_width },
            { "consoleToStdout", console_to_stdout },
            { "inspectorMode", inspector_mode },
            { "enableWiltonCalls", enable_wilton_calls },
            { "windowTitle", title },
            { "windowIconPath", icon_path }
        };
    }
};

} // namespace
}


#endif /* WILTON_KIOSK_WEBVIEW_CONFIG_HPP */

