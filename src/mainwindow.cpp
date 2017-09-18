#include "mainwindow.h"
#include "ui_mainwindow.h"

// Janie - ADD - START
#include <QDesktopWidget>
#include <QVBoxLayout>

#include "comdef.h"

#include "decodingboard.h"      // For debug
#include "holematrix.h"        // For debug
#include <QMessageBox>          // For debug
// Janie - ADD - END

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
// Janie - ADD - START
    ,masterMindGame(new MasterMindGame)
// Janie - ADD - END
{
    ui->setupUi(this);

    // Janie - ADD - START
    setWindowSize();
    setWindowPos();

//    QPalette pal = centralWidget()->palette();    // For debug

//    pal.setColor(QPalette::Background, Qt::green);  // For debug

//    centralWidget()->setPalette(pal);   // For debug

//    centralWidget()->setAutoFillBackground(true); // For debug

    //WidgetTracker* wt = new WidgetTracker;  // For debug

    //wt->startTracking();                    // For debug

    getMasterMindGame()->GetDecodingBoard()->Draw();

    //QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget());   // For debug

    //auto w1 = new QPushButton("w1");                              // For debug

    //parentLayout->addWidget(w1);                                     // For debug

    // Janie - ADD - END
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Janie - ADD - START

void MainWindow::on_actionNewGame_triggered() {}

void MainWindow::on_actionExit_triggered() { QApplication::quit(); }

shared_ptr<MasterMindGame> MainWindow::getMasterMindGame() { return masterMindGame; }

void MainWindow::setWindowSize()
{
    //QDesktopWidget *desktopWidget = QApplication::desktop();

    int width = 180;//desktopWidget->width() * 0.5;
    int height = 510;//desktopWidget->height() * 0.5;

    setFixedSize(width, height);
}

void MainWindow::setWindowPos()
{
    QDesktopWidget *desktopWidget = QApplication::desktop();
    QSize windowSize = size();

    int width = desktopWidget->width();
    int height = desktopWidget->height();

    int x = (width - windowSize.width()) / 2;
    int y = (height - windowSize.height()) / 2;

    move(x, y);
}
// Janie - ADD - END
