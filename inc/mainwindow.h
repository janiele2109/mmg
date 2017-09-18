#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Janie - ADD - START
#include <memory>

#include "mastermindgame.h"

using namespace std;
// Janie - ADD - END

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Janie - ADD - START
    shared_ptr<MasterMindGame> getMasterMindGame();

    void setWindowSize();
    void setWindowPos();
    // Janie - ADD - END

private slots:

    // Janie - ADD - START
    void on_actionNewGame_triggered();

    void on_actionExit_triggered();
    // Janie - ADD - END

private:
    Ui::MainWindow *ui;

    // Janie - ADD - START
    shared_ptr<MasterMindGame> masterMindGame;
    // Janie - ADD - END
};

#endif // MAINWINDOW_H
