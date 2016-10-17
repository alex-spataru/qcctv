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

#ifndef _QCCTV_FRAME_GRABBER_H
#define _QCCTV_FRAME_GRABBER_H

#include <QObject>
#include <QPixmap>
#include <QVideoProbe>

class QCCTV_FrameGrabber : public QVideoProbe
{
    Q_OBJECT

signals:
    void newFrame (const QPixmap& frame);

public:
    QCCTV_FrameGrabber (QObject* parent = NULL);

    bool isEnabled() const;
    qreal shrinkRatio() const;
    bool isGrayscale() const;

public slots:
    void setEnabled (const bool enabled);
    void setShrinkRatio (const qreal ratio);
    void setGrayscale (const bool grayscale);

private slots:
    void grayscale (QImage* image);
    void processImage (const QVideoFrame& frame);

private:
    bool m_enabled;
    bool m_grayscale;
    qreal m_ratio;
};

#endif