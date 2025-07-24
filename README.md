# Gizmo

**Gizmo** is a lightweight GTK-based desklet for Linux desktops.  
This initial version is a simple unit converter for weight — converting between ounces, grams, and pounds.

It’s sticky. It’s minimal. It lives on your desktop like a polite little ghost.

## Features

- Converts between:
  - Ounces (oz)
  - Grams (g)
  - Pounds (lb)
- Transparent, undecorated always-on-bottom window
- Designed to stay out of your way, like a proper desklet should

## Build Instructions

### Dependencies

- GTK+ 3
- GLib
- libxdo (from `xdotool`)

### Compile

```bash
g++ gizmo.cpp -o gizmo `pkg-config --cflags --libs gtk+-3.0 x11 xdo`

