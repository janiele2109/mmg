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

#include <memory>

#include <QMainWindow>

#include "mastermindgame.h"

using namespace std;

namespace Ui
{
    class MainWindow;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \class      MainWindow
/// \brief      Abstract object which is responsible for main window
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        const shared_ptr<MasterMindGame>& GetMasterMindGame();

        void SetWindowSize();
        void SetWindowPos();

        void StartNewGame();

    private slots:
        void on_actionExit_triggered();
        void on_actionAbout_triggered();
        void on_actionNewGame_triggered();

    private:
        /// handle ui of the application
        Ui::MainWindow* ui;

        /// handle processing for master mind game
        shared_ptr<MasterMindGame> master_mind_game_;
};

#endif // MAINWINDOW_H
