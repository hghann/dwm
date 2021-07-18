## dwm - dynamic window manager

dwm is an extremely fast, small, and dynamic window manager for X.


## Requirements

In order to build dwm you need the Xlib header files.


## Installation

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

```
git clone https://github.com/worthyox/dwm
cd dwm
sudo make clean install
```

## Running dwm

Add the following line to your .xinitrc to start dwm using startx:

```
exec dwm
```

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

```
DISPLAY=foo.bar:1 exec dwm
```

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

```
while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
do
    sleep 1
done &
exec dwm
```


## Configuration

The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.


## Patches and features

- swallow: if a program run from a terminal would make it inoperable, it temporarily takes its place to save space.
- scratchpads: allows for multiple different scratchpad windows assigned to different keybinds
- sticky: easily make a client visible on all tags (make it "sticky").
- movestack: move windows up and down in the master and stack layout.
- shiftview: function to shift current view left/right.
- actualfullscreen: actually toggle fullscreen instead of hiding the bar and entering monocle layout.
- fullgaps: adds gaps between client windows. Similar to gaps, but contains additional functionality.
- autostart: runs dwmblocks on startup


## Notes

After applying various gap patchs it seems that some terminals like
st are unable to expand to fill arbitrary space on the screen. When
resizehints is set to 1, space is left around the window.
(Source: https://dwm.suckless.org/faq)
