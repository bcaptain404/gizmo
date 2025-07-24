#!/bin/bash

function Go() {
    local INC=(
        "-I /usr/include/gtk-3.0"
        "-I /usr/include/glib-2.0"
        "-I /usr/lib/x86_64-linux-gnu/glib-2.0/include"
        "-I /usr/include/pango-1.0"
        "-I /usr/include/harfbuzz"
        "-I /usr/include/cairo"
        "-I /usr/include/gdk-pixbuf-2.0"
        "-I /usr/include/atk-1.0"
    )
    local LIBD=(
        "-L /usr/lib/x86_64-linux-gnu"
    )
    local LIBS=(
        "-l glib-2.0"
        "-l gtk-3"
        "-l gdk-3"
        "-l pthread"
        "-l gobject-2.0"
        "-l xdo"
        #"-l gthread-2.0" 
        #"-l lrt"
        #"-l gstreamer"
    )
    g++ unitConvert.cpp \
        ${INC[@]} \
        ${LIBD[@]} \
        ${LIBS[@]} 
}

Go "${@}"

