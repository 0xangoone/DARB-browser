#ifndef WEBPROFILE_H
#define WEBPROFILE_H
#include <QWebEngineProfile>
#include <QWebEngineDownloadRequest>
class WebProfile: public QWebEngineProfile
{
public:
    WebProfile();
    void load();
private slots:
    void on_download(const QWebEngineDownloadRequest *download);
    void downloadFile(const QUrl &url, const QString &filePath);
};

#endif // WEBPROFILE_H
