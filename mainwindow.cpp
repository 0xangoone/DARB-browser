#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "webview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(0);

    ui->verticalLayout->setSpacing(0);
    ui->verticalLayout->setContentsMargins(0,0,0,0);
    setContentsMargins(0,0,0,0);
    ui->centralwidget->setContentsMargins(0,0,0,0);

    const QIcon *window_icon = new QIcon(":/img/img/darb.png");
    setWindowIcon(*window_icon);
    setWindowTitle(u8"متصفح درب");

    MainWindow::addNewTab();
    if (QApplication::arguments().length() >= 2){
        QWidget *currentTab = ui->tabWidget->currentWidget();
        QWebEngineView *webView = currentTab->findChild<QWebEngineView *>();
        webView->load(QUrl(QApplication::arguments()[1]));
    }

    QPushButton *addTabButton = new QPushButton("+", this);
    QFont font = addTabButton->font();
    font.setPixelSize(25);
    addTabButton->setFont(font);
    addTabButton->setFixedSize(35, 35);
    addTabButton->setStyleSheet("color:white;"
                                "background:rgb(15,15,15);"
                                "margin:0px;");
    addTabButton->setToolTip("إضافة تبويبة جديدة");
    QWidget *cornerWidget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(cornerWidget);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    layout->addWidget(addTabButton);
    layout->setAlignment(addTabButton, Qt::AlignRight);

    ui->tabWidget->setCornerWidget(cornerWidget, Qt::TopRightCorner);


    connect(addTabButton, &QPushButton::clicked, this, &MainWindow::addNewTab);
}
void MainWindow::addNewTab() {
    QWidget *newTab = new QWidget();

    QVBoxLayout *layout = new QVBoxLayout(newTab);
    layout->setAlignment(Qt::AlignTop);


    QLineEdit *search_input = new QLineEdit();
    search_input->setStyleSheet("border-radius:10px;"
                         "background:#303030;"
                         "font-size:18px;"
                         "padding:5px;"
                         "color:white;");

    const QIcon* search_icon   = new QIcon(":/img/img/search.png" );
    const QIcon* refresh_icon  = new QIcon(":/img/img/refresh.png");
    const QIcon* settings_icon = new QIcon(":img/img/setting.png" );
    const QIcon* home_icon     = new QIcon(":img/img/home.png"    );
    const QIcon* left_icon     = new QIcon(":img/img/left.png"    );
    const QIcon* right_icon    = new QIcon(":img/img/right.png"   );

    QPushButton* search_btn    = new QPushButton();
    search_btn->setIcon(*search_icon);

    QPushButton* refresh_btn = new QPushButton();
    refresh_btn->setIcon(*refresh_icon);

    QPushButton* settings_btn = new QPushButton();
    settings_btn->setIcon(*settings_icon);

    QPushButton* home_btn = new QPushButton();
    home_btn->setIcon(*home_icon);

    QPushButton* back_btn = new QPushButton();
    back_btn->setIcon(*left_icon);
    back_btn->setIconSize(QSize(20,40));

    QPushButton* forward_btn = new QPushButton();
    forward_btn->setIcon(*right_icon);
    forward_btn->setIconSize(QSize(20,40));


    WebView* web_view = new WebView();

    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(back_btn);
    hbox->addWidget(refresh_btn);
    hbox->addWidget(forward_btn);
    hbox->addWidget(home_btn);

    hbox->addWidget(search_input);

    hbox->addWidget(search_btn);
    hbox->addWidget(settings_btn);

    layout->setContentsMargins(0,9,0,9);

    layout->addLayout(hbox);
    layout->addWidget(web_view);

    newTab->setLayout(layout);
    ui->tabWidget->addTab(newTab, QString("رئيسية"));

    int last_tab_index = ui->tabWidget->count();
    ui->tabWidget->setCurrentIndex(last_tab_index - 1);

    connect(search_input,&QLineEdit::returnPressed,this,&MainWindow::onSearchButtonClicked);

    connect(search_btn, &QPushButton::clicked, this, &MainWindow::onSearchButtonClicked);
    connect(refresh_btn, &QPushButton::clicked, this, &MainWindow::onRefreshButtonClicked);
    connect(home_btn, &QPushButton::clicked, this, &MainWindow::onHomeButtonClicked);

    connect(back_btn , &QPushButton::clicked ,this,&MainWindow::onBack);
    connect(forward_btn , &QPushButton::clicked ,this ,&MainWindow::onForward);

    connect(settings_btn, &QPushButton::clicked, this, &MainWindow::onSettingsButtonClicked);

    connect(web_view->page(),&QWebEnginePage::newWindowRequested,this,&MainWindow::on_newWindow);
    connect(web_view->page(),&QWebEnginePage::fullScreenRequested,this,&MainWindow::on_web_full_screen);
    connect(web_view,&QWebEngineView::titleChanged,this,&MainWindow::onTitleChanged);
    connect(web_view,&QWebEngineView::urlChanged,this,&MainWindow::onUrlChanged);
    connect(web_view,&QWebEngineView::iconChanged,this,&MainWindow::onIconChanged);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onSearchButtonClicked(){
    QWidget *currentTab = ui->tabWidget->currentWidget();
    QLineEdit *searchInput = currentTab->findChild<QLineEdit *>();
    QWebEngineView *webView = currentTab->findChild<QWebEngineView *>();
    QString search_query = searchInput->text();
    if (!search_query.startsWith("http")){
        search_query.replace(" ","+");
        search_query = "https://google.com/search?q=" + search_query;
    }
    webView->load(QUrl(search_query));
}
void MainWindow::onBack(){
    QWidget *currentTab = ui->tabWidget->currentWidget();
    QWebEngineView *webView = currentTab->findChild<QWebEngineView *>();
    webView->back();
}
void MainWindow::onForward(){
    QWidget *currentTab = ui->tabWidget->currentWidget();
    QWebEngineView *webView = currentTab->findChild<QWebEngineView *>();
    webView->forward();
}
void MainWindow::onRefreshButtonClicked(){
    QWidget *currentTab = ui->tabWidget->currentWidget();
    QWebEngineView *webView = currentTab->findChild<QWebEngineView *>();
    webView->reload();
}
void MainWindow::onHomeButtonClicked(){
    QWidget *currentTab = ui->tabWidget->currentWidget();
    QWebEngineView *webView = currentTab->findChild<QWebEngineView *>();
    webView->load(QUrl("https://www.google.com/"));
}

void MainWindow::onSettingsButtonClicked(){

}
void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if (ui->tabWidget->count() == 1){
        ui->tabWidget->setCurrentIndex(index);
        QWidget *currentTab = ui->tabWidget->currentWidget();
        QWebEngineView *webView = currentTab->findChild<QWebEngineView *>();
        webView->close();
        ui->tabWidget->removeTab(index);
        MainWindow::close();
    }
    ui->tabWidget->setCurrentIndex(index);
    QWidget *currentTab = ui->tabWidget->currentWidget();
    QWebEngineView *webView = currentTab->findChild<QWebEngineView *>();
    webView->close();
    ui->tabWidget->removeTab(index);
}
void MainWindow::keyPressEvent(QKeyEvent *event) {
    handleKeyPress(event->key());
}

void MainWindow::handleKeyPress(int key) {
    switch (key) {
        case Qt::Key_F11:
            if (this->isFullScreen() == false){
                this->SetFullScreen();
            }else{
                this->disableFullScreen();
            }
            break;
        default:
            break;
    }
}

