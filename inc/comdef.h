#ifndef COMDEF_H
#define COMDEF_H

#include <QString>
#include <QRect>
#include <QColor>

namespace comdef
{
    namespace mainwindow
    {
        constexpr uint16_t kDefWindowWidth  = 180;
        constexpr uint16_t kDefWindowHeight = 550;

        const   QString     kTitle   =   "MasterMind";
    }

    namespace makerarea
    {
        constexpr uint8_t kDefNumOfRows             = 1;
        constexpr uint8_t kDefNumOfLargeHolesPerRow = 4;
    }

    namespace breakerarea
    {
        constexpr uint8_t kDefNumOfRows             = 12;
        constexpr uint8_t kDefNumOfLargeHolesPerRow = makerarea::kDefNumOfLargeHolesPerRow;
    }

    namespace decodingboard
    {
        namespace combobox
        {
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
    }

    namespace color
    {
        const QString kGreenStr      =   "1-green";
        const QString kBlueStr       =   "2-blue";
        const QString kYellowStr     =   "3-yellow";
        const QString kLightGreenStr =   "4-dark green";
        const QString kBrownStr      =   "5-brown";
        const QString kRedStr        =   "6-red";
        const QString kBlackStr      =   "7-black";
        const QString kWhiteStr      =   "8-white";
        const QString kLightStr      =   "9-empty hole";

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

    namespace errorMsg
    {
        const QString kErr001      =   "This hole does not accept Black and White color!";
    }

    constexpr char kEmptyString[]    = "";
}

#endif // COMDEF_H
