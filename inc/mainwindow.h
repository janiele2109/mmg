//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \file      mainwindow.h
/// \brief     All declarations and definition for Main Window of application
///
/// \author    Janie
/// \version   1.0.0.0
///
/// \note
///
/// Version      When        Who         Remarks
/// ===========================================================================================================================
///
/// 0.0.0.1      14Sep2017   Janie       First creation
/// 1.0.0.0      25Sep2017   Janie       First release
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

    void on_actionNewGame_triggered();

private:
    Ui::MainWindow *ui;

    // Janie - ADD - START
    shared_ptr<MasterMindGame> master_mind_game_;
    // Janie - ADD - END
};

#endif // MAINWINDOW_H
