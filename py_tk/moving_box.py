#!/usr/bin/env python
# Copyright (c) 2025 NorCal Robotics - All Rights Reserved.
#
# This source code is licensed under the MIT License.
#
# You may obtain a copy of the License at
#
#      https://opensource.org/licenses/MIT
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Author: Gabriel Field

import tkinter as tk


class MovingBox:
    def __init__(self, master):
        self.master = master
        self.width = 800
        self.height = 600
        self.canvas = tk.Canvas(self.master, width=self.width, height=self.height, bg="white")
        self.canvas.pack()

        # Starting position of the box
        self.x = 0
        self.box = self.canvas.create_rectangle(self.x, 290, self.x + 10, 300, fill="blue")

        # Start animation
        self.move_box()

    def move_box(self):
        # Move the box to the right
        self.x += 2
        if self.x > self.width:  # If box goes beyond right side, reset to left
            self.x = 0

        # Update the position of the box on the canvas
        self.canvas.coords(self.box, self.x, 290, self.x + 10, 300)

        # Schedule the next movement
        self.master.after(16, self.move_box)  # Update every 16ms, roughly 60 fps


root = tk.Tk()
moving_box = MovingBox(root)
root.mainloop()
