{
    "targets": [
        {
            "target_name": "cairo",
            "sources": [
                "src/node-cairo.cc",
                "src/node-cairo-utils.cc",
                "src/node-cairo-context.cc",
                "src/node-cairo-device.cc",
                "src/node-cairo-enum.cc",
                "src/node-cairo-font-face.cc",
                "src/node-cairo-font-options.cc",
                "src/node-cairo-matrix.cc",
                "src/node-cairo-path.cc",
                "src/node-cairo-pattern.cc",
                "src/node-cairo-region.cc",
                "src/node-cairo-scaled-font.cc",
                "src/node-cairo-surface.cc",
                "src/node-pango-enum.cc",
                "src/node-pango-font-description.cc",
                "src/node-pango-layout.cc",
                "src/node-pango-layout-iter.cc",
                "src/node-pango-layout-line.cc",
                "src/node-pango-utils.cc",
                "src/node-rsvg-handle.cc",
                "src/node-rsvg-enum.cc"
            ],
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")",
                "/usr/local/opt/cairo/include/cairo",
                "/usr/local/opt/pango/include/pango-1.0",
                "/usr/local/opt/glib/include/glib-2.0",
                "/usr/local/opt/glib/lib/glib-2.0/include",
                "/usr/local/opt/harfbuzz/include/harfbuzz",
                "/usr/local/opt/librsvg/include/librsvg-2.0",
                "/usr/local/opt/gdk-pixbuf/include/gdk-pixbuf-2.0"
            ],
            "defines": ['NAPI_DISABLE_CPP_EXCEPTIONS'],
            "libraries": [
                "/usr/local/opt/cairo/lib/libcairo.dylib",
                "/usr/local/opt/pango/lib/libpangocairo-1.0.dylib",
                "/usr/local/opt/librsvg/lib/librsvg-2.dylib"
            ]
        }
    ]
}
