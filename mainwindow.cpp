#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTabWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QIcon>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(0);

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
    int tabCount = ui->tabWidget->count();

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
    search_btn->setText("search");

    QPushButton* refresh_btn = new QPushButton();
    refresh_btn->setIcon(*refresh_icon);

    QPushButton* settings_btn = new QPushButton();
    settings_btn->setIcon(*settings_icon);

    QPushButton* home_btn = new QPushButton();
    home_btn->setIcon(*home_icon);

    // add elements to horizontal layout
    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(refresh_btn);
    hbox->addWidget(search_input);
    hbox->addWidget(search_btn);
    hbox->addWidget(home_btn);
    hbox->addWidget(settings_btn);

    layout->addLayout(hbox);

    // add new Tab
    newTab->setLayout(layout);
    ui->tabWidget->addTab(newTab, QString("Home"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if (ui->tabWidget->count() == 1){
        ui->tabWidget->removeTab(index);
        MainWindow::close();
    }
    ui->tabWidget->removeTab(index);
}

