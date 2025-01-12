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
import random
from recordclass import recordclass

nt_star = recordclass('star', ['x', 'y', 'z', 'oval'])


class Starfield:
    def __init__(self, master):
        self.master = master
        self.width = 800
        self.height = 600
        self.center_x = self.width / 2
        self.center_y = self.height / 2
        self.rear_z = 256
        self.speed = 1
        self.canvas = tk.Canvas(self.master, width=self.width, height=self.height, bg="black")
        self.canvas.pack()

        # List to hold star coordinates and speed
        self.stars = []
        self.max_stars = 100

        # Initialize stars
        for _ in range(self.max_stars):
            self.add_star()

        # Bind resize event
        self.master.bind("<Configure>", self.on_resize)

        # Start animation
        self.animate()

    def on_resize(self, event):
        # Update width and height when window is resized
        self.width = event.width
        self.height = event.height
        self.center_x = self.width / 2
        self.center_y = self.height / 2

    def add_star(self):
        x = random.uniform(-self.center_x, self.center_x) * self.rear_z
        y = random.uniform(-self.center_y, self.center_y) * self.rear_z
        self.stars.append(nt_star(x, y, self.rear_z, None))

    def move_stars(self):
        for star in self.stars:
            # Perspective projection: x and y get larger as z decreases
            try:
                x_projected = self.center_x + star.x / star.z
            except ZeroDivisionError:
                x_projected = -1000

            try:
                y_projected = self.center_y + star.y / star.z
            except ZeroDivisionError:
                y_projected = -1000

            # If star is out of bounds, reset it behind us
            if x_projected < 0 or x_projected > self.width or y_projected < 0 or y_projected > self.height or star.z <= 0:
                self.stars.remove(star)
                if star.oval is not None:
                    self.canvas.delete(star.oval)
                    star.oval = None
                self.add_star()
                continue

            # Draw or update the star
            size = max(1, (1 / star.z * 20))  # Star size inversely proportional to distance
            color = "#FFFFFF"
            if star.z < 10:
                color = "#FFFF00"  # Stars become yellow when very close
            if star.oval is None:
                star.oval = self.canvas.create_oval(x_projected - size, y_projected - size, x_projected + size, y_projected + size, fill=color, outline="")
            else:
                self.canvas.itemconfig(star.oval, fill=color)
                self.canvas.coords(star.oval, x_projected - size, y_projected - size, x_projected + size, y_projected + size)

            # Move the star one unit forward on Z
            star.z -= self.speed

    def animate(self):
        self.move_stars()
        self.master.after(16, self.animate)


root = tk.Tk()
starfield = Starfield(root)
root.mainloop()
