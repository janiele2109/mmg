//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \file      comdef.h
/// \brief     All common declarations and definition for the application
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

#ifndef COMDEF_H
#define COMDEF_H

#include <string>

#include <QString>
#include <QRect>
#include <QColor>

using namespace std;

namespace comdef
{
    struct AnalizedColorPattern
    {
        AnalizedColorPattern()
        {
            color{comdef::color::kGrey};
            count{0};
        }

        QColor color;
        uint8_t count;
    };

    struct AnalizedCodeColor
    {
        AnalizedCodeColor()
        {
            code_color{comdef::color::kGrey};
            key_color{comdef::color::kGrey};
        }

        QColor code_color;
        QColor key_color;
    };

    namespace mainwindow
    {
        const string   kClassName  =   "QMainWindow";

        constexpr uint16_t kDefWindowWidth  = 180;
        constexpr uint16_t kDefWindowHeight = 550;
    }

    namespace makerarea
    {
        constexpr uint8_t kDefRowBreakIndex    = 2;
        constexpr uint8_t kDefNumOfRows        = 1;
        constexpr uint8_t kDefNumOfHolesPerRow = 4;
    }

    namespace breakerarea
    {
        constexpr uint8_t kDefRowBreakIndex    = -1;
        constexpr int     kLastEnableRowIndex  = -1;
        constexpr uint8_t kDefNumOfRows        = 12;
        constexpr uint8_t kDefNumOfHolesPerRow = makerarea::kDefNumOfHolesPerRow;
    }

    namespace decodingboard
    {
        namespace combobox
        {
            constexpr   uint8_t   kInitCurrentIndex = 0;

            const string   kClassName  =   "QComboBox";

            const QRect kInitRect = QRect(10,
                                          mainwindow::kDefWindowHeight - 50,
                                          110,
                                          20);
        }

        namespace pushbutton
        {
            constexpr   uint8_t     kInitX           =   10;

            constexpr   int8_t      kInitSmallY      =   -7;
            constexpr   uint8_t     kInitLargeY      =   10;

            constexpr   uint8_t     kLargeWidth      =   20;
            constexpr   uint8_t     kLargeHeight     =   20;

            constexpr   uint8_t     kSmallWidth      =   10;
            constexpr   uint8_t     kSmallHeight     =   10;

            constexpr   uint8_t     kSmallPadding    =   5;
            constexpr   uint8_t     kLargePadding    =   10;

            constexpr   uint8_t     kSmallRowSpacing =   8;
            constexpr   uint8_t     kLargeRowSpacing =   kLargeHeight + 18;

            const       QRect       kInitLargeRect   =   QRect(kInitX,
                                                               kInitLargeY,
                                                               kLargeWidth,
                                                               kLargeHeight);

            const       QRect       kInitSmallRect   =   QRect(kInitX,
                                                               kInitSmallY,
                                                               kSmallWidth,
                                                               kSmallHeight);
        }

        constexpr   uint8_t     kDefRowBreakIndex    =   -1;
    }

    namespace color
    {
        const QString kGreenStr      =   "1-green";
        const QString kBlueStr       =   "2-blue";
        const QString kYellowStr     =   "3-yellow";
        const QString kLightGreenStr =   "4-dark green";
        const QString kBrownStr      =   "5-brown";
        const QString kRedStr        =   "6-red";
        const QString kLightStr      =   "7-empty hole";
        const QString kBlackStr      =   "8-black";
        const QString kWhiteStr      =   "9-white";

        const QColor kGreen         =   QColor(Qt::green);
        const QColor kBlue          =   QColor(Qt::blue);
        const QColor kYellow        =   QColor(Qt::yellow);
        const QColor kRed           =   QColor(Qt::red);
        const QColor kBlack         =   QColor(Qt::black);
        const QColor kWhite         =   QColor(Qt::white);
        const QColor kLightGreen    =   QColor(0, 128, 64);
        const QColor kBrown         =   QColor(164, 0, 0);
        const QColor kGrey          =   QColor(192, 192, 192);
        const QColor kLight         =   QColor(234, 234, 234);

        const QString kBgColorStyleRgb   =   "background-color: rgb(%1, %2, %3)";
        const QString kBgColorStyleText  =   "background-color: %1";
    }

    constexpr char kEmptyString[]    = "";

    namespace info
    {
        namespace about
        {
            const QString kAppName      =   "Name: MasterMind\n\n";
            const QString kAppVersion   =   "Version: 0.0.0.1\n\n";
            const QString kAppAuthor    =   "Author: Janie Le\n\n";
            const QString kAppCopyright =   "Copyright@2017\n";
        }

        const QString kAppName      =   "Name: MasterMind\n\n";
    }

    namespace error
    {
        const QString kErr001      =   "There looks like something went wrong!";
    }
}

#endif // COMDEF_H
