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

#ifndef _QCCTV_LOCAL_CAMERA_H
#define _QCCTV_LOCAL_CAMERA_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>

#include "QCCTV.h"
#include "QCCTV_CRC32.h"
#include "QCCTV_Watchdog.h"
#include "QCCTV_ImageCapture.h"

class QThread;
class QCamera;
class QCameraImageCapture;

class QCCTV_LocalCamera : public QObject
{
    Q_OBJECT
    Q_PROPERTY (int fps
                READ fps
                WRITE setFPS
                NOTIFY fpsChanged)
    Q_PROPERTY (QString name
                READ name
                WRITE setName
                NOTIFY nameChanged)
    Q_PROPERTY (QString group
                READ group
                WRITE setGroup
                NOTIFY groupChanged)
    Q_PROPERTY (int resolution
                READ resolution
                WRITE setResolution
                NOTIFY resolutionChanged)
    Q_PROPERTY (bool flashlightEnabled
                READ flashlightStatus
                WRITE setFlashlightEnabled
                NOTIFY lightStatusChanged)
    Q_PROPERTY (bool autoRegulateResolution
                READ autoRegulateResolution
                WRITE setAutoRegulateResolution
                NOTIFY autoRegulateResolutionChanged)
    Q_PROPERTY (int minimumFps
                READ minimumFPS
                CONSTANT)
    Q_PROPERTY (int maximumFps
                READ maximumFPS
                CONSTANT)
    Q_PROPERTY (int statusCode
                READ cameraStatus
                NOTIFY cameraStatusChanged)
    Q_PROPERTY (QString statusString
                READ statusString
                NOTIFY cameraStatusChanged)
    Q_PROPERTY (bool readyForCapture
                READ readyForCapture
                NOTIFY cameraStatusChanged)
    Q_PROPERTY (bool flashlightAvailable
                READ flashlightAvailable
                NOTIFY cameraStatusChanged)
    Q_PROPERTY (QStringList connectedHosts
                READ connectedHosts
                NOTIFY hostCountChanged)
    Q_PROPERTY (QStringList resolutions
                READ availableResolutions
                NOTIFY hostCountChanged)

Q_SIGNALS:
    void fpsChanged();
    void nameChanged();
    void imageChanged();
    void groupChanged();
    void hostCountChanged();
    void resolutionChanged();
    void lightStatusChanged();
    void focusStatusChanged();
    void cameraStatusChanged();
    void autoRegulateResolutionChanged();

public:
    QCCTV_LocalCamera (QObject* parent = NULL);
    ~QCCTV_LocalCamera();

    int fps() const;
    int resolution() const;
    int minimumFPS() const;
    int maximumFPS() const;
    int cameraStatus() const;
    int flashlightStatus() const;

    QString name() const;
    QString group() const;
    QImage currentImage() const;
    QString statusString() const;

    bool readyForCapture() const;
    bool flashlightAvailable() const;
    bool autoRegulateResolution() const;

    QStringList connectedHosts() const;
    QStringList availableResolutions() const;

public Q_SLOTS:
    void takePhoto();
    void focusCamera();
    void setFPS (const int fps);
    void setCamera (QCamera* camera);
    void setName (const QString& name);
    void setGroup (const QString& group);
    void setResolution (const int resolution);
    void setFlashlightEnabled (const bool enabled);
    void setAutoRegulateResolution (const bool regulate);

private Q_SLOTS:
    void update();
    void changeImage();
    void broadcastInfo();
    void onDisconnected();
    void acceptConnection();
    void readCommandPacket();
    void onWatchdogTimeout();

private:
    void updateStatus();
    void generateData();
    QString deviceName();
    void sendCameraData();
    void addStatusFlag (const QCCTV_CameraStatus status);
    void setCameraStatus (const QCCTV_CameraStatus status);
    void removeStatusFlag (const QCCTV_CameraStatus status);
    void setFlashlightStatus (const QCCTV_LightStatus status);

private:
    QImage m_image;
    QThread* m_thread;
    QCamera* m_camera;
    QCameraImageCapture* m_capture;
    QCCTV_ImageCapture* m_imageCapture;

    bool m_autoRegulateResolution;
    QCCTV_Resolution m_resolution;

    int m_fps;
    int m_cameraStatus;
    int m_flashlightStatus;

    QString m_name;
    QString m_group;
    QByteArray m_data;
    QByteArray m_imageData;

    QCCTV_CRC32 m_crc32;
    QTcpServer m_server;
    QUdpSocket m_cmdSocket;
    QUdpSocket m_broadcastSocket;
    QList<QTcpSocket*> m_sockets;
    QList<QCCTV_Watchdog*> m_watchdogs;
};

#endif
