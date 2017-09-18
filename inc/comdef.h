#ifndef COMDEF_H
#define COMDEF_H

namespace comdef
{
    namespace mainwindow
    {
        constexpr uint16_t kDefWindowWidth  = 180;
        constexpr uint16_t kDefWindowHeight = 510;
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
        const QString kRedStr       =   "red";
        const QString kGreenStr     =   "green";
        const QString kBlueStr      =   "blue";
        const QString kWhiteStr     =   "white";
        const QString kBlackStr     =   "black";
        const QString kYellowStr    =   "yellow";
        const QString kGreyStr      =   "grey";

        const QColor kRed       =   QColor(Qt::red);
        const QColor kGreen     =   QColor(Qt::green);
        const QColor kBlue      =   QColor(Qt::blue);
        const QColor kWhite     =   QColor(Qt::white);
        const QColor kBlack     =   QColor(Qt::black);
        const QColor kYellow    =   QColor(Qt::yellow);
        const QColor kGrey      =   QColor(192, 192, 192);

        const QString kBgColorStyleRgb   =   "background-color: rgb(%1, %2, %3)";
        const QString kBgColorStyleText  =   "background-color: %1";
    }

    constexpr char kEmptyString[]    = "";
}

#endif // COMDEF_H
