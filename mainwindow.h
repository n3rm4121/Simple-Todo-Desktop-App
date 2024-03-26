#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>
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
    void on_btnAdd_clicked();

    void on_btnRemove_clicked();

    void on_btnRemoveAll_clicked();

private:
    Ui::MainWindow *ui;
    QString filePath = QCoreApplication::applicationDirPath() + "/todo.txt";
     void on_txtTask_returnPressed();
    void loadTasksFromFile();
};
#endif // MAINWINDOW_H
