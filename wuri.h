#ifndef WURI_H
#define WURI_H
// wuri means Web Engine Url Request Interceptor
#include <QWebEngineUrlRequestInterceptor>
#include <QWebEngineUrlRequestInfo>
class WUri : public QWebEngineUrlRequestInterceptor
{
    Q_OBJECT
public:
    WUri(QObject *p = Q_NULLPTR);
    void interceptRequest(QWebEngineUrlRequestInfo &info);
};

#endif // WURI_H
