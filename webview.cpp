#include "webview.h"
#include "ui_mainwindow.h"
#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QLineEdit>
#include <QWebEngineFullScreenRequest>
#include <QWebEngineProfile>
#include "webprofile.h"
#include <QWebEngineCookieStore>

WebView::WebView() {
    WebProfile* profile = new WebProfile();
    this->setPage(new QWebEnginePage(profile, this));
    this->setUrl(QUrl("https://duckduckgo.com/?q=&t=chromentp"));
    this->reload();
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //config the web view setting
    this->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled,true);
    this->settings()->setAttribute(QWebEngineSettings::PluginsEnabled,true);
    this->settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows,true);
    this->settings()->setAttribute(QWebEngineSettings::WebAttribute::LocalStorageEnabled,true);
    this->settings()->setAttribute(QWebEngineSettings::WebGLEnabled,true);
    this->settings()->setAttribute(QWebEngineSettings::PdfViewerEnabled,true);

    qDebug () << this->page()->profile()->persistentStoragePath();
    this->page()->profile()->cookieStore()->loadAllCookies();
}

WebView::~WebView(){

}
// web view slots that in the MainWindow
void MainWindow::on_web_full_screen(const QWebEngineFullScreenRequest &request){
    this->SetFullScreen();

}
void MainWindow::SetFullScreen()
{
    ui->tabWidget->setTabBarAutoHide(true);
    this->showFullScreen();
}
void MainWindow::enableFullScreen(){
    ui->tabWidget->setTabBarAutoHide(false);
    this->showNormal();
}
void MainWindow::on_newWindow(const QWebEngineNewWindowRequest &request){
    QUrl url = request.requestedUrl();
    MainWindow::addNewTab();
    QWidget *currentTab = ui->tabWidget->currentWidget();
    QWebEngineView *webView = currentTab->findChild<QWebEngineView *>();
    webView->load(url);
}
void MainWindow::onIconChanged(const QIcon &icon){
    int currentIndex = ui->tabWidget->currentIndex();
    ui->tabWidget->setTabIcon(currentIndex,icon);
}
void MainWindow::onUrlChanged(const QUrl &url){
    QWidget *currentTab = ui->tabWidget->currentWidget();
    QLineEdit *searchInput = currentTab->findChild<QLineEdit *>();
    QString str_url = url.toEncoded();
    searchInput->setText(str_url);
}
void MainWindow::onTitleChanged(const QString &title){
    int currentIndex = ui->tabWidget->currentIndex();
    ui->tabWidget->setTabText(currentIndex, title);
}
