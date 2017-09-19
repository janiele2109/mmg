#include "mainwindow.h"
#include "ui_mainwindow.h"

// Janie - ADD - START
#include <QDesktopWidget>

#include "comdef.h"

#include "decodingboard.h"
#include "holematrix.h"
// Janie - ADD - END

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
// Janie - ADD - START
    ,master_mind_game_(new MasterMindGame)
// Janie - ADD - END
{
    ui->setupUi(this);

    // Janie - ADD - START
    SetWindowSize();
    SetWindowPos();

    master_mind_game_->GetDecodingBoard()->Draw();
    // Janie - ADD - END
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Janie - ADD - START

void MainWindow::on_actionNewGame_triggered() {}

void MainWindow::on_actionExit_triggered() { QApplication::quit(); }

shared_ptr<MasterMindGame> MainWindow::GetMasterMindGame() { return master_mind_game_; }

void MainWindow::SetWindowSize()
{
    int width = comdef::mainwindow::kDefWindowWidth;
    int height = comdef::mainwindow::kDefWindowHeight;

    setFixedSize(width, height);
}

void MainWindow::SetWindowPos()
{
    QDesktopWidget *desktop_widget = QApplication::desktop();
    QSize window_size = size();

    int width = desktop_widget->width();
    int height = desktop_widget->height();

    int x = (width - window_size.width()) / 2;
    int y = (height - window_size.height()) / 2;

    move(x, y);
}
// Janie - ADD - END
