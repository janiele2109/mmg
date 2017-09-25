//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \file      maker.h
/// \brief     All declarations and definition for Maker area in Decoding board
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

#ifndef MAKER_H
#define MAKER_H

#include <cstdint>
#include <memory>

#include <QColor>

#include "comdef.h"

using namespace std;

class HoleMatrix;

class MakerAreas
{
    public:
        MakerAreas();

        ~MakerAreas();

        shared_ptr<HoleMatrix>                            GetPatternMatrix();
        shared_ptr<vector<comdef::AnalizedColorPattern>>  GetAnalizedColorPattern();
        shared_ptr<HoleMatrix>                            GetKeyMatrix();

        void InitPatternMatrix();
        void InitKeyMatrix();

        const shared_ptr<vector<comdef::AnalizedColorPattern>>& AnalyzeColorPattern();

        void DrawPatternMatrix();
        void DrawKeyMatrix();

        void SetKeyColor(uint8_t row_idx,
                         const QColor& color);

    protected:

    private:
        shared_ptr<HoleMatrix>  pattern_matrix_;
        shared_ptr<vector<comdef::AnalizedColorPattern>>analized_color_pattern_;
        shared_ptr<HoleMatrix>  key_matrix_;
};

#endif // MAKER_H
