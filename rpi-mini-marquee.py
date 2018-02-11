#!/usr/bin/env python
import argparse
import Adafruit_SSD1306
import Image

RST = 24  # Reset pin
_FLIP_SCREEN = False
_systems = ["arcade", "atari2600", "atari7800", "dreamcast", "gc", "kodi", "megadrive", "n64", "nds", "neogeo", "psx",
            "segacd", "snes", "retropie"]


def load_image(path):
    image = Image.open(path).convert('1')
    w, h = image.size
    im = image.load()
    # Invert colour
    for x in range(w):
        for y in range(h):
            im[x, y] = 255 if im[x, y] == 0 else 0

    # Flip image
    if _FLIP_SCREEN:
        image.rotate(180)

    return image


def display_marquee(disp, image):
    disp.image(image)
    disp.display()


def marquee_path(system):
    if system in _systems:
        return "/usr/share/rpi-mini-marquee/marquees/black_white/{0}.pbm".format(system)
    else:
        raise ValueError("Unknown system \"{0}\"".format(system))


def init_screen():
    disp = Adafruit_SSD1306.SSD1306_128_32(rst=RST)

    # Ready the display
    disp.begin()
    disp.clear()
    disp.display()

    return disp


def set_marquee(system):
    path = marquee_path(system)
    image = load_image(path)

    disp = init_screen()

    display_marquee(disp, image)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Alters the image displayed on the Raspberry Pi's mini marquee.")
    parser.add_argument('system', type=str, nargs=1,
                        help='the system to change the marquee to, use \"clear\" to reset')
    parser.add_argument('-f', '--force', action="store_true",
                        help='forces the marquee to change, if the provided one fails, it defaults to "retropie"')

    args = parser.parse_args()
    try:
        if args.system[0] == "clear":
            init_screen()
        else:
            set_marquee(args.system[0])
    except ValueError:
        if args.force:
            set_marquee("retropie")
        else:
            print "Invalid system \"{0}\"".format(args.system[0])
