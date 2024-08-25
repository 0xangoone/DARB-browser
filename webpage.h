#ifndef WEBPAGE_H
#define WEBPAGE_H
#include <QWebEnginePage>
#include <QWebEngineProfile>

class WebPage : public QWebEnginePage
{
public:
    WebPage();
    void load();
protected:
private Q_SLOTS:
    void onFeaturePermissionRequested(const QUrl &securityOrigin, QWebEnginePage::Feature feature);
private:
};

#endif // WEBPAGE_H
