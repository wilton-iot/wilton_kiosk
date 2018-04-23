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
 * File:   wilton_kiosk.h
 * Author: alex
 *
 * Created on April 22, 2018, 9:48 PM
 */

#ifndef WILTON_KIOSK_H
#define WILTON_KIOSK_H

#include "wilton/wilton.h"

#ifdef __cplusplus
extern "C" {
#endif

char* wilton_kiosk_run(
        const char* conf,
        int conf_len);

#ifdef __cplusplus
}
#endif

#endif /* WILTON_KIOSK_H */

