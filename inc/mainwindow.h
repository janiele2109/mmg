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
    const shared_ptr<MasterMindGame>& GetMasterMindGame();

    void SetWindowSize();
    void SetWindowPos();

    void StartNewGame();
    // Janie - ADD - END

private slots:

    // Janie - ADD - START
    void on_actionExit_triggered();

    void on_actionAbout_triggered();
    // Janie - ADD - END

private:
    Ui::MainWindow *ui;

    // Janie - ADD - START
    shared_ptr<MasterMindGame> master_mind_game_;
    // Janie - ADD - END
};

#endif // MAINWINDOW_H
