#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tabWidget_tabCloseRequested(int index);
    void addNewTab();
    void onSearchButtonClicked();
    void onRefreshButtonClicked();
    void onHomeButtonClicked();
    void onSettingsButtonClicked();
    void onTitleChanged(const QString &title);
    void onUrlChanged(const QUrl &url);
    void onIconChanged(const QIcon &icon);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
