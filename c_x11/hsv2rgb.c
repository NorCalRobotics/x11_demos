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

#include "hsv2rgb.h"

void hsv_to_rgb(uint8_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g, uint8_t *b) {
    uint8_t c = (v * s) >> 8;
    uint8_t x = c * (255 - abs((h * 2 - 255) % 255 - 128)) >> 8;
    uint8_t m = v - c;

    if (h < 43) { // 0-42
        *r = c + m;
        *g = x + m;
        *b = m;
    } else if (h < 85) { // 43-84
        *r = x + m;
        *g = c + m;
        *b = m;
    } else if (h < 128) { // 85-127
        *r = m;
        *g = c + m;
        *b = x + m;
    } else if (h < 170) { // 128-169
        *r = m;
        *g = x + m;
        *b = c + m;
    } else if (h < 213) { // 170-212
        *r = x + m;
        *g = m;
        *b = c + m;
    } else { // 213-255
        *r = c + m;
        *g = m;
        *b = x + m;
    }
}
