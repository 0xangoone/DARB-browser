#include "wuri.h"
#include <QWebEngineUrlRequestInfo>
#include <QDebug>
WUri::WUri(QObject *p)
    :QWebEngineUrlRequestInterceptor(p)
{
}
void WUri::interceptRequest(QWebEngineUrlRequestInfo &info) {
    info.setHttpHeader("User-Agent","ZeroTeam/1.0 (Windows NT 6.2; Unkown) AppleWebKit/537.36 (KHTML, like Gecko) DarbBrowser/0.3.1 Chrome/128.0.0.0 Safari/537.36");
}
