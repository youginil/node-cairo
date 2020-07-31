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
                "src/node-cairo-path.cc",
                "src/node-cairo-pattern.cc",
                "src/node-cairo-region.cc",
                "src/node-cairo-scaled-font.cc",
                "src/node-cairo-surface.cc",
            ],
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")",
                "/usr/local/opt/cairo/include/cairo"
            ],
            "defines": ['NAPI_DISABLE_CPP_EXCEPTIONS'],
            "libraries": ["/usr/local/opt/cairo/lib/libcairo.dylib"]
        }
    ]
}
