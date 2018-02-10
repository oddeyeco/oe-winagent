#ifndef ODDEYECACHEUPLOADER_H
#define ODDEYECACHEUPLOADER_H

#include "basicoddeyeclient.h"
// Qt
#include <QTimer>
#include <QQueue>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// class COddEyeCacheUploader
/// serves for cached data uploading
class COddEyeCacheUploader : public CBasicOddEyeClient
{
    Q_OBJECT
    using Base = CBasicOddEyeClient;

public:
    COddEyeCacheUploader(QObject *parent = nullptr);

public slots:
    void Start();
    void Stop();
    void SetUpdateInterval( int nMsecs );

protected:
    // CBasicOddEyeClient interface
    void HandleSendSuccedded(QNetworkReply *pReply, const QJsonDocument &oJsonData) override;
    void HandleSendError(    QNetworkReply *pReply, const QJsonDocument &oJsonData) override;

private slots:
    void onCheckAndUpload();
private:
    void StartUploading();
    void UploadHead();
    void DequeueHead();

private:
    QTimer*  m_pTimer;
    QQueue<QString> m_qUploadingFiles;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // ODDEYECACHEUPLOADER_H
