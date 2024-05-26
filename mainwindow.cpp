#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTabWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QIcon>
#include <QWebEngineView>
#include <QScrollBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(0);

    //setting the window icon
    const QIcon *window_icon = new QIcon(":/img/img/darb.png");
    setWindowIcon(*window_icon);
    setWindowTitle(u8"متصفح درب");
    // add the startup tab
    MainWindow::addNewTab();

    //new tab button
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

    // search text box element
    QLineEdit *search_input = new QLineEdit();
    search_input->setStyleSheet("border-radius:10px;"
                         "background:#303030;"
                         "font-size:18px;"
                         "padding:5px;"
                         "color:white;");
    // load buttons icons
    const QIcon* search_icon = new QIcon(":/img/img/search.png");
    const QIcon* refresh_icon = new QIcon(":/img/img/refresh.png");
    const QIcon* settings_icon = new QIcon(":img/img/setting.png");
    const QIcon* home_icon = new QIcon(":img/img/home.png");
    //buttons
    QPushButton* search_btn = new QPushButton();
    search_btn->setIcon(*search_icon);
    search_btn->setText("بحث");

    QPushButton* refresh_btn = new QPushButton();
    refresh_btn->setIcon(*refresh_icon);

    QPushButton* settings_btn = new QPushButton();
    settings_btn->setIcon(*settings_icon);

    QPushButton* home_btn = new QPushButton();
    home_btn->setIcon(*home_icon);

    // the web view
    QWebEngineView* web_view = new QWebEngineView();
    web_view->setUrl(QUrl("https://duckduckgo.com/"));
    web_view->reload();

    // add elements to horizontal layout
    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(refresh_btn);
    hbox->addWidget(search_input);
    hbox->addWidget(search_btn);
    hbox->addWidget(home_btn);
    hbox->addWidget(settings_btn);  

    layout->addLayout(hbox);
    layout->addWidget(web_view);

    web_view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // add new Tab
    newTab->setLayout(layout);
    ui->tabWidget->addTab(newTab, QString("رئيسية"));

    int last_tab_index = ui->tabWidget->count();
    ui->tabWidget->setCurrentIndex(last_tab_index - 1);

    connect(search_input,&QLineEdit::returnPressed,this,&MainWindow::onSearchButtonClicked);

    // Connect button signals to slots
    connect(search_btn, &QPushButton::clicked, this, &MainWindow::onSearchButtonClicked);
    connect(refresh_btn, &QPushButton::clicked, this, &MainWindow::onRefreshButtonClicked);
    connect(home_btn, &QPushButton::clicked, this, &MainWindow::onHomeButtonClicked);
    connect(settings_btn, &QPushButton::clicked, this, &MainWindow::onSettingsButtonClicked);

    connect(web_view,&QWebEngineView::titleChanged,this,&MainWindow::onTitleChanged);
    connect(web_view,&QWebEngineView::urlChanged,this,&MainWindow::onUrlChanged);
    connect(web_view,&QWebEngineView::iconChanged,this,&MainWindow::onIconChanged); 
}

MainWindow::~MainWindow()
{
    delete ui;
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
void MainWindow::onSearchButtonClicked(){
    QWidget *currentTab = ui->tabWidget->currentWidget();
    QLineEdit *searchInput = currentTab->findChild<QLineEdit *>();
    QWebEngineView *webView = currentTab->findChild<QWebEngineView *>();
    QString search_query = searchInput->text();
    webView->load(QUrl(search_query));
}
void MainWindow::onRefreshButtonClicked(){
    QWidget *currentTab = ui->tabWidget->currentWidget();
    QWebEngineView *webView = currentTab->findChild<QWebEngineView *>();
    webView->reload();
}
void MainWindow::onHomeButtonClicked(){
    QWidget *currentTab = ui->tabWidget->currentWidget();
    QWebEngineView *webView = currentTab->findChild<QWebEngineView *>();
    webView->load(QUrl("https://duckduckgo.com/"));
}
void MainWindow::onSettingsButtonClicked(){

}
void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if (ui->tabWidget->count() == 1){
        ui->tabWidget->removeTab(index);
        MainWindow::close();
    }
    ui->tabWidget->removeTab(index);
}

