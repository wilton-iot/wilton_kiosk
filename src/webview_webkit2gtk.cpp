/*
 * Copyright 2018, myasnikov.mike at gmail.com
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
 * File:   webview_webkit2gtk.cpp
 * Author: alex
 * 
 * Created on April 22, 2018, 9:56 PM
 */

#include "webview.hpp"

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <webkit2/webkit2.h>

#include "staticlib/support.hpp"
#include "staticlib/pimpl/forward_macros.hpp"
#include "staticlib/utils.hpp"

#include "wilton/support/exception.hpp"
#include "wilton/support/handle_registry.hpp"

#include "webview_config.hpp"

#include <iostream>

namespace wilton {
namespace kiosk {

class webview::impl : public staticlib::pimpl::object::impl {
    webview_config conf;
    GtkWidget* window;
    WebKitWebView* web_view;
    WebKitWebInspector *inspector;
    bool fullscreen_state;

public:
    impl(webview_config&& wconf) :
    conf(std::move(wconf)),
    window(gtk_window_new(GTK_WINDOW_TOPLEVEL)),
    web_view(WEBKIT_WEB_VIEW(webkit_web_view_new())),
    inspector(nullptr),
    fullscreen_state(conf.fullscreen) {
        // defaults
        if (0 == conf.fullscreen_key) {
            conf.fullscreen_key = GDK_KEY_F11;
        }
        if (0 == conf.close_key) {
            conf.close_key = GDK_KEY_Escape;
        }
 
        // window
        gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
        gtk_window_resize(GTK_WINDOW(window), conf.window_width, conf.window_height);
        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

        // signals and settings
        g_signal_connect(window, "destroy", G_CALLBACK(destroy_callback), this);
        g_signal_connect(window, "key_release_event", G_CALLBACK(on_key_release_callback), this);
        if (conf.console_to_stdout) {
            webkit_settings_set_enable_write_console_messages_to_stdout(webkit_web_view_get_settings(web_view), TRUE);
        }

        // disable context menu
        g_signal_connect(web_view, "context-menu", G_CALLBACK(context_menu_callback), nullptr);

        // compose
        gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(web_view));
        if (conf.fullscreen) {
            gtk_window_fullscreen(GTK_WINDOW(window));
        } else {
            gtk_window_resize(GTK_WINDOW(window), conf.window_width, conf.window_height);
        }
        if (conf.inspector_mode) {
            webkit_settings_set_enable_developer_extras(webkit_web_view_get_settings(web_view), TRUE);
            inspector = webkit_web_view_get_inspector(WEBKIT_WEB_VIEW(web_view));
        }
    }

    void run(webview&) {
        gtk_widget_show_all(window);
        webkit_web_view_load_uri(web_view, conf.url.c_str());
        gtk_widget_grab_focus(GTK_WIDGET(web_view));
        if (conf.inspector_mode) {
            webkit_web_inspector_show(WEBKIT_WEB_INSPECTOR(inspector));
        }
        gtk_main();
    }

    static void initialize() {
        gtk_init(nullptr, nullptr);
    }

private:

    void on_key_release(unsigned int keyval) {
        if (conf.close_key == keyval) {
            gtk_main_quit();
        } else if (conf.fullscreen_key == keyval) {
            if (fullscreen_state) {
                gtk_window_unfullscreen(GTK_WINDOW(window));
            } else {
                gtk_window_fullscreen(GTK_WINDOW(window));
            }
            this->fullscreen_state = !fullscreen_state;
        }
    }
 
    static void destroy_callback(GtkWidget*, GtkWidget*, gpointer) {
        gtk_main_quit();
    }

    static gboolean context_menu_callback(GtkWidget*, GtkWidget*, WebKitHitTestResult*, gboolean, gpointer) {
        return TRUE;
    }

    static gboolean on_key_release_callback(GtkWidget*, GdkEventKey* event, gpointer instance) {
        if (nullptr == event || nullptr == instance) {
            return TRUE;
        }
        auto ptr = reinterpret_cast<webview::impl*>(instance);
        ptr->on_key_release(event->keyval);
        return TRUE;
    }

};
PIMPL_FORWARD_CONSTRUCTOR(webview, (webview_config&&), (), support::exception)
PIMPL_FORWARD_METHOD(webview, void, run, (), (), support::exception)
PIMPL_FORWARD_METHOD_STATIC(webview, void, initialize, (), (), support::exception)

} // namespace
}
