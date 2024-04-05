#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>


// Add event filter to listen for key press events
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect the line edit's returnPressed signal to a slot for handling Enter key press
    connect(ui->txtTask, &QLineEdit::returnPressed, this, &MainWindow::on_txtTask_returnPressed);

    // Load tasks from file
    loadTasksFromFile();
}

void MainWindow::on_txtTask_returnPressed()
{
    // Get the text from the line edit
    QString task = ui->txtTask->text().trimmed();

    // If the text is not empty, add it to the list widget
    if (!task.isEmpty()) {
        QListWidgetItem* item = new QListWidgetItem(task, ui->listWidget);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        ui->txtTask->clear();
    }
}

void MainWindow::loadTasksFromFile()
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file for reading:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString task = in.readLine().trimmed();
        if (!task.isEmpty()) {
            QListWidgetItem* item = new QListWidgetItem(task, ui->listWidget);
            item->setFlags(item->flags() | Qt::ItemIsEditable);
        }
    }
    file.close();
}


MainWindow::~MainWindow()
{
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file for writing:" << file.errorString();
        return;
    }

    QTextStream out(&file);
    for(int i = 0; i < ui->listWidget->count(); ++i) {
        out << ui->listWidget->item(i)->text() << "\n";
    }
    file.close();

    delete ui;
}

void MainWindow::on_btnAdd_clicked()
{
    QString task = ui->txtTask->text().trimmed();
    if(!task.isEmpty()) {
        QListWidgetItem* item = new QListWidgetItem(task, ui->listWidget);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        ui->txtTask->clear();
        ui->txtTask->setFocus();
    }
}

void MainWindow::on_btnRemove_clicked()
{
    QListWidgetItem* item = ui->listWidget->takeItem(ui->listWidget->currentRow());
    delete item;
}

void MainWindow::on_btnRemoveAll_clicked()
{
    ui->listWidget->clear();
}
