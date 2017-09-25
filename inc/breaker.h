//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \file      breaker.h
/// \brief     All declarations and definition for Breaker area in Decoding board
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

#ifndef BREAKER_H
#define BREAKER_H

#include <cstdint>
#include <memory>

#include "comdef.h"

using namespace std;

class HoleMatrix;

class Breaker
{
    public:
        Breaker(uint8_t num_of_rows            = comdef::breakerarea::kDefNumOfRows,
                uint8_t num_of_holes_per_row   = comdef::breakerarea::kDefNumOfHolesPerRow);

        ~Breaker();

        const shared_ptr<HoleMatrix>& GetHolesMatrix();

    protected:

    private:
        shared_ptr<HoleMatrix> holes_matrix_;
};

#endif // BREAKER_H
