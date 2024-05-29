#include "webprofile.h"
#include <QWebEngineProfile>
#include <QStandardPaths>
#include <QWebEngineCookieStore>
#include <QNetworkCookie>
#include <QApplication>
#include <QWebEngineDownloadRequest>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>
#include <QFile>
#include <QTimer>
WebProfile::WebProfile() {
    this->setCachePath(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));
    this->setPersistentCookiesPolicy(QWebEngineProfile::PersistentCookiesPolicy::NoPersistentCookies);

    QWebEngineCookieStore *cookieStore = this->cookieStore();
    if (!cookieStore) {
        qWarning() << "Failed to get cookieStore!";
        return;
    }
    connect(cookieStore, &QWebEngineCookieStore::cookieAdded,this, [](const QNetworkCookie &cookie) {
        qDebug() << "Cookie added:" << cookie.name();
        qDebug() << cookie.path();
        qDebug() << cookie.domain();
    });
    connect(this,&QWebEngineProfile::downloadRequested,this,&WebProfile::on_download);
}
void WebProfile::on_download(const QWebEngineDownloadRequest *download){
    QString file_name = download->downloadDirectory();
    if( QSysInfo::prettyProductName().startsWith("Windows")){
        // dos file System :-)
        file_name += "\\";
    }else{
        // unix file system B-)
        file_name += "/";
    }
    file_name += download->downloadFileName();
    qDebug() << download->url() << "\n";
    // download the file
    this->downloadFile(download->url(),file_name);
}
void WebProfile::downloadFile(const QUrl &url, const QString &filePath)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QFile file(filePath);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(reply->readAll());
                file.close();
                QMessageBox* msgbox = new QMessageBox();
                msgbox->setText("تم تحميل الملف بنجاح !");
                msgbox->show();
            } else {
                QMessageBox* msgbox = new QMessageBox();
                msgbox->setText("فشل فتح الملف ياصاح هناك خطأ ما ._.");
                msgbox->show();
            }
        } else {
            QMessageBox* msgbox = new QMessageBox();
            msgbox->setText("فشل التحميل");
            msgbox->show();
        }
        reply->deleteLater();
        manager->deleteLater();
    });
}
