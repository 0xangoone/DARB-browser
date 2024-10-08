#include "webview.h"
#include "ui_mainwindow.h"
#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QLineEdit>
#include <QWebEngineFullScreenRequest>
#include <QWebEngineProfile>
#include "webprofile.h"
#include <QWebEngineCookieStore>
#include "webpage.h"

WebView::WebView() {
    QWebEngineProfile *qprofile = new QWebEngineProfile(QString::fromLatin1("04394584267356253.%1").arg(qWebEngineChromiumVersion()));
    WebProfile *profile = static_cast<WebProfile*>(qprofile);
    profile->load();
    QWebEnginePage *_webpage = new QWebEnginePage(profile,this);
    WebPage *webpage = static_cast<WebPage*>(_webpage);
    webpage->load();
    this->setPage(webpage);
    this->setUrl(QUrl("https://google.com"));
    this->reload();
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    qDebug () << this->page()->profile()->persistentStoragePath();
    this->page()->profile()->cookieStore()->loadAllCookies();
}

WebView::~WebView(){

}


void MainWindow::on_web_full_screen(QWebEngineFullScreenRequest request){
    if (request.toggleOn()){
        request.accept();
        this->SetFullScreen();
    }
    else {
        request.accept();
        this->disableFullScreen();
    }
    //this->SetFullScreen();
}
void MainWindow::SetFullScreen()
{
    ui->tabWidget->setTabBarAutoHide(true);
    this->showFullScreen();
}
void MainWindow::disableFullScreen(){
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
