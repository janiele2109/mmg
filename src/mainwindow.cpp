#include "mainwindow.h"
#include "ui_mainwindow.h"

// Janie - ADD - START
#include <QDesktopWidget>
#include <QMessageBox>

#include "comdef.h"

#include "decodingboard.h"
#include "holematrix.h"
// Janie - ADD - END

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Janie - ADD - START
    SetWindowSize();
    SetWindowPos();

    StartNewGame();
    // Janie - ADD - END
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Janie - ADD - START

const shared_ptr<MasterMindGame>& MainWindow::GetMasterMindGame(){ return master_mind_game_; }

void MainWindow::on_actionNewGame_triggered(){ StartNewGame(); }

void MainWindow::on_actionExit_triggered(){ QApplication::quit(); }

void MainWindow::on_actionAbout_triggered()
{
    QString msg;

    msg.append(comdef::info::about::kAppName);
    msg.append(comdef::info::about::kAppVersion);
    msg.append(comdef::info::about::kAppAuthor);
    msg.append(comdef::info::about::kAppCopyright);

    QMessageBox::information(nullptr,
                             comdef::info::kAppName,
                             msg,
                             QMessageBox::Ok,
                             QMessageBox::Icon::Information);
}

void MainWindow::StartNewGame()
{
    try
    {
        master_mind_game_.reset(new MasterMindGame);

        master_mind_game_->GetDecodingBoard()->Draw();
    }
    catch(const std::exception& e)
    {
        QString msg{"%1\n\n%2"};

        msg.arg(comdef::error::kErr001).arg(e.what());

        QMessageBox::information(nullptr, comdef::info::kAppName, msg, QMessageBox::Retry);
    }
}

void MainWindow::SetWindowSize()
{
    setFixedSize(comdef::mainwindow::kDefWindowWidth,
                 comdef::mainwindow::kDefWindowHeight);
}

void MainWindow::SetWindowPos()
{
    QSize desktop_size = QApplication::desktop()->size();
    QSize main_window_size = size();

    int x = (desktop_size.width() - main_window_size.width()) / 2;
    int y = (desktop_size.height() - main_window_size.height()) / 2;

    move(x, y);
}
// Janie - ADD - END
