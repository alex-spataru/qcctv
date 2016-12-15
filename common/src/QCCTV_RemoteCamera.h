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

#ifndef _QCCTV_CAMERA_H
#define _QCCTV_CAMERA_H

#include <QTcpSocket>
#include <QUdpSocket>

#include "QCCTV.h"
#include "QCCTV_CRC32.h"
#include "QCCTV_Watchdog.h"
#include "QCCTV_ImageSaver.h"

class QCCTV_RemoteCamera : public QObject
{
    Q_OBJECT

Q_SIGNALS:
    void newCameraGroup();
    void newImage (const int id);
    void connected (const int id);
    void fpsChanged (const int id);
    void disconnected (const int id);
    void newCameraName (const int id);
    void newCameraStatus (const int id);
    void resolutionChanged (const int id);
    void lightStatusChanged (const int id);
    void autoRegulateResolutionChanged (const int id);

public:
    QCCTV_RemoteCamera (QObject* parent = NULL);
    ~QCCTV_RemoteCamera();

    Q_INVOKABLE int id() const;
    Q_INVOKABLE int fps() const;
    Q_INVOKABLE int status() const;
    Q_INVOKABLE QImage image() const;
    Q_INVOKABLE QString name() const;
    Q_INVOKABLE QString group() const;
    Q_INVOKABLE bool isConnected() const;
    Q_INVOKABLE QString statusString() const;
    Q_INVOKABLE QHostAddress address() const;
    Q_INVOKABLE bool autoRegulateResolution() const;
    Q_INVOKABLE QCCTV_Resolution resolution() const;
    Q_INVOKABLE QCCTV_LightStatus lightStatus() const;

public Q_SLOTS:
    void start();
    void requestFocus();
    void changeID (const int id);
    void changeFPS (const int fps);
    void setImageQuality (const int quality);
    void setSaveIncomingMedia (const bool save);
    void setRecordingsPath (const QString& path);
    void changeResolution (const int resolution);
    void setAddress (const QHostAddress& address);
    void changeAutoRegulate (const bool regulate);
    void changeFlashlightStatus (const int status);

private Q_SLOTS:
    void clearBuffer();
    void endConnection();
    void onDataReceived();
    void sendCommandPacket();
    void resetFocusRequest();
    void updateFPS (const int fps);
    void updateStatus (const int status);
    void updateName (const QString& name);
    void updateGroup (const QString& group);
    void updateConnected (const bool status);
    void updateResolution (const int resolution);
    void updateAutoRegulate (const bool regulate);
    void updateFlashlightStatus (const int status);

private:
    void readCameraPacket();
    void acknowledgeReception();

private:
    int m_id;
    int m_quality;
    bool m_focus;
    QTcpSocket* m_socket;
    QCCTV_Watchdog* m_watchdog;
    QString m_group;
    bool m_connected;
    QUdpSocket* m_commandSocket;
    bool m_oldAutoRegulate;
    bool m_newAutoRegulate;
    QString m_name;
    bool m_saveIncomingMedia;
    int m_oldFPS;
    int m_newFPS;
    int m_oldResolution;
    int m_newResolution;
    int m_cameraStatus;
    int m_oldFlashlightStatus;
    int m_newFlashlightStatus;
    QImage m_image;

    QByteArray m_data;
    QCCTV_CRC32 m_crc32;
    QList<QImage> m_images;
    QHostAddress m_address;
    QString m_recordingsPath;
    QCCTV_ImageSaver m_saver;
};

#endif
