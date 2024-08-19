#ifndef WEBPROFILE_H
#define WEBPROFILE_H
#include <QWebEngineProfile>
#include <QWebEngineDownloadRequest>
#include <QProgressDialog>
class WebProfile: public QWebEngineProfile
{
public:
    WebProfile();
    ~WebProfile();
    void load();
private slots:
    void on_download(const QWebEngineDownloadRequest *download);
    void downloadFile(const QUrl &url, const QString &filePath);
private:
    QProgressDialog *pd;
};

#endif // WEBPROFILE_H
