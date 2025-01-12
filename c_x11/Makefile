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

CC=gcc
CFLAGS=-Wall -Wextra -std=c99

all: starfield

starfield: starfield.c hsv2rgb.o
	$(CC) $(CFLAGS) starfield.c hsv2rgb.o -o starfield -lX11

hsv2rgb.o: hsv2rgb.c hsv2rgb.h
	$(CC) $(CFLAGS) -c hsv2rgb.c -o hsv2rgb.o

clean:
	rm -f starfield *.o
