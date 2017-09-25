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

using namespace std;

class Breaker;
class MakerAreas;

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
        const shared_ptr<MakerAreas>& GetMaker();

        void Draw();
        void DrawColorCombo();

    protected:

    private:
        shared_ptr<Breaker>      breaker_;
        shared_ptr<MakerAreas>   maker_;
        shared_ptr<QComboBox>    combobox_;
};

#endif // DECODINGBOARD_H
