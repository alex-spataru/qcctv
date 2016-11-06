/*
 * Copyright (c) 2016 Alex Spataru
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE
 */

import QtQuick 2.0

Text {
    smooth: true
    color: "#fff"
    font.pixelSize: 14
    font.family: {
        if (font.bold && font.italic)
            return "Open Sans Bold Italic"
        else if (font.bold)
            return "Open Sans Bold"
        else if (font.italic)
            return "Open Sans Italic"
        else
            return "Open Sans Regular"
    }

    FontLoader {
        source: "qrc:/common/fonts/OpenSans-Bold.ttf"
    }

    FontLoader {
        source: "qrc:/common/fonts/OpenSans-Italic.ttf"
    }

    FontLoader {
        source: "qrc:/common/fonts/OpenSans-Regular.ttf"
    }

    FontLoader {
        source: "qrc:/common/fonts/OpenSans-BoldItalic.ttf"
    }
}
