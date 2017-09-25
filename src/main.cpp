//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \file      main.cpp
/// \brief     Implementation of main function
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

#include "mainwindow.h"
#include <QApplication>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     main
/// \brief  main function
///
/// \param  argc
/// \brief  argument count
///
/// \param  argv
/// \brief  array of argument values
///
/// \return int
/// \brief  result of executing of the program
/// \retval 0: normal executing
/// \retval 1: error (abnormal) executing
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
