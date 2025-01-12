/*
 * Copyright (c) 2025 NorCal Robotics - All Rights Reserved.
 *
 * This source code is licensed under the MIT License.
 *
 * You may obtain a copy of the License at
 *
 *      https://opensource.org/licenses/MIT
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Gabriel Field
 */

#ifndef _HSV2RGB_H_INCLUDED
#define HSV2RGB_H_INCLUDED

#include <stdlib.h>
#include <stdint.h>

void hsv_to_rgb(uint8_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g, uint8_t *b);

#endif
