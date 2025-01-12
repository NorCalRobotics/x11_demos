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

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

#include "hsv2rgb.h"

#define NUM_STARS 200
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    int x, y, z;
    XColor xcolor;
} Star;

// Initial window dimensions
int width = 800;
int height = 600;
int center_x, center_y;
int rear_z = 256;

void colorize_star(Display *display, Star * p_star) {
    uint8_t h, s, v;
    uint8_t r, g, b;

    h = rand() & 0xFF;
    s = rand() % 100;
    v = 0xFF;

    hsv_to_rgb(h, s, v, &r, &g, &b);

    p_star->xcolor.red = r << 8;
    p_star->xcolor.green = g << 8;
    p_star->xcolor.blue = b << 8;

    XAllocColor(display, DefaultColormap(display, DefaultScreen(display)), &(p_star->xcolor));
}

void reset_star(Star * p_star) {
    p_star->x = ((rand() % width) - center_x) * rear_z;
    p_star->y = ((rand() % height) - center_y) * rear_z;
    p_star->z = rear_z;
}

int main() {
    Display *display;
    Window window;
    GC gc;
    XEvent event;
    XSetWindowAttributes attr;
    Atom wm_delete_window;
    Star stars[NUM_STARS];
    int speed = 1, x, y, x0, y0, diam, w0, h0;
    bool closed = false;

    center_x = width >> 1, center_y = height >> 1;

    // Initialize display
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        return 1;
    }

    // Get WM_DELETE_WINDOW atom
    wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", False);

    // Create window
    int screen = DefaultScreen(display);
    attr.background_pixel = BlackPixel(display, screen);
    attr.event_mask = StructureNotifyMask;
    window = XCreateWindow(display, RootWindow(display, screen), 0, 0, width, height, 0,
                           CopyFromParent, InputOutput, CopyFromParent,
                           CWBackPixel | CWEventMask, &attr);
    XMapWindow(display, window);

    XSetWMProtocols(display, window, &wm_delete_window, 1);

    // Create graphics context
    gc = XCreateGC(display, window, 0, NULL);

    // Initialize stars
    srand(time(NULL));
    for (int i = 0; i < NUM_STARS; ++i) {
        colorize_star(display, &(stars[i]));
        reset_star(&(stars[i]));
    }

    while (! closed) {
        // Handle events
        while (XPending(display) > 0) {
            XNextEvent(display, &event);
            if (XFilterEvent(&event, None)) continue;

            if (event.type == ConfigureNotify) {
                width = event.xconfigure.width;
                height = event.xconfigure.height;
                center_x = width >> 1;
                center_y = height >> 1;
                continue;
            }

            if (event.type == ClientMessage) {
                if (event.xclient.data.l[0] == (long)wm_delete_window) {
                    closed = true;
                    break;
                }
            }
        }

        // Clear the window
        XClearWindow(display, window);

        // Draw stars
        for (int i = 0; i < NUM_STARS; ++i) {
            if (stars[i].z <= 0) reset_star(&(stars[i]));

            x = center_x + stars[i].x / stars[i].z;
            y = center_y + stars[i].y / stars[i].z;
            if (x < 0 || x >= width || y < 0 || y >= height) {
                reset_star(&(stars[i]));
                x = center_x + stars[i].x / stars[i].z;
                y = center_y + stars[i].y / stars[i].z;
            }

            // XDrawPoint(display, window, gc, x, y);
            diam = 200 / stars[i].z;

            x0 = MAX(0, x - diam / 2);
            y0 = MAX(0, y - diam / 2);
            w0 = MAX(1, MIN(width - x0, diam));
            h0 = MAX(1, MIN(height - y0, diam));

            XSetForeground(display, gc, stars[i].xcolor.pixel);
            XFillRectangle(display, window, gc, x0, y0, w0, h0);

            stars[i].z -= speed;
        }

        XFlush(display);
        usleep(10000);
        XSync(display, False);
    }

    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    return 0;
}
