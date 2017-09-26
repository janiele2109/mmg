//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \file      decodingboard.h
/// \brief     All declarations and definition for Decoding board
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

#ifndef DECODINGBOARD_H
#define DECODINGBOARD_H

#include <memory>

#include <QComboBox>
#include <QCheckBox>

using namespace std;

class Breaker;
class Maker;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \class      DecodingBoard
/// \brief      Abstract object which is responsible for decoding board
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DecodingBoard
{
    public:
        DecodingBoard();
        ~DecodingBoard();

        const shared_ptr<Breaker>& GetBreaker();
        const shared_ptr<Maker>& GetMaker();
        const shared_ptr<QComboBox>& GetColorComboxBox();
        const shared_ptr<QCheckBox>& GetDisplayPatternCheckBox();

        void Draw();
        void DrawColorCombo();
        void DrawCheckbox();

    protected:

    private:
        /// handle breaker
        shared_ptr<Breaker>      breaker_;

        /// handle maker
        shared_ptr<Maker>        maker_;

        /// handle color combobox
        shared_ptr<QComboBox>    color_combobox_;

        /// handle display pattern checkbox
        shared_ptr<QCheckBox>    display_pattern_checkbox_;
};

#endif // DECODINGBOARD_H
