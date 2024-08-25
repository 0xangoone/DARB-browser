#include "webpage.h"
#include <QColor>
#include <QWebEngineSettings>
#include <QCursor>
WebPage::WebPage() {
    this->load();
}
void WebPage::load(){
    this->settings()->setAttribute(QWebEngineSettings::Accelerated2dCanvasEnabled,true);
    this->settings()->setAttribute(QWebEngineSettings::NavigateOnDropEnabled,true);
    this->settings()->setAttribute(QWebEngineSettings::ErrorPageEnabled,true);
    this->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled,true);
    this->settings()->setAttribute(QWebEngineSettings::PluginsEnabled,true);
    this->settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows,true);
    this->settings()->setAttribute(QWebEngineSettings::WebAttribute::LocalStorageEnabled,true);
    this->settings()->setAttribute(QWebEngineSettings::WebGLEnabled,true);
    this->settings()->setAttribute(QWebEngineSettings::PdfViewerEnabled,true);
    this->settings()->setAttribute(QWebEngineSettings::LocalStorageEnabled,true);
    this->settings()->setAttribute(QWebEngineSettings::ScreenCaptureEnabled,true);
    this->settings()->setAttribute(QWebEngineSettings::JavascriptCanAccessClipboard,true);
    this->settings()->setAttribute(QWebEngineSettings::JavascriptCanPaste,true);
    this->settings()->setAttribute(QWebEngineSettings::ScrollAnimatorEnabled,true);
    this->settings()->setAttribute(QWebEngineSettings::WebAttribute::ShowScrollBars,true);
    this->settings()->setUnknownUrlSchemePolicy(QWebEngineSettings::AllowAllUnknownUrlSchemes);

    this->setAudioMuted(false);
    this->triggerAction(QWebEnginePage::InspectElement, true);
    connect(this, &WebPage::featurePermissionRequested, this, &WebPage::onFeaturePermissionRequested);
}
void WebPage::onFeaturePermissionRequested(const QUrl &securityOrigin, QWebEnginePage::Feature feature){
    if(feature  == QWebEnginePage::MediaAudioCapture
        || feature == QWebEnginePage::MediaVideoCapture
        || feature == QWebEnginePage::MediaAudioVideoCapture
        || feature == QWebEnginePage::Feature::DesktopAudioVideoCapture
        || feature == QWebEnginePage::Feature::DesktopVideoCapture)
        setFeaturePermission(securityOrigin, feature, QWebEnginePage::PermissionGrantedByUser);
    else
        setFeaturePermission(securityOrigin, feature, QWebEnginePage::PermissionDeniedByUser);
}
