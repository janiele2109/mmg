//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \file      breaker.cpp
/// \brief     Implementation of Breaker area in Decoding board
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

#include "breaker.h"
#include "holematrix.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn         Breaker::Breaker
/// \brief      Constructor (with default values for arguments, played role as default constructor as well as
///             parameterized constructor)
///             - Init data member (allocate memory and set default values for all push controls in Breaker area)
///             - Enable the first row of push buttons in Breaker area
///
/// \param      num_of_rows
/// \brief      number of rows in Breaker area
/// \default    comdef::breakerarea::kDefNumOfRows
///
/// \param      num_of_holes_per_row
/// \brief      number of holes per row in Breaker area
/// \default    comdef::breakerarea::kDefNumOfHolesPerRow
///
/// \return     none
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Breaker::Breaker(uint8_t num_of_rows,
                 uint8_t num_of_holes_per_row):holes_matrix_{new HoleMatrix{num_of_rows,
                                                                            num_of_holes_per_row}}
{
    holes_matrix_->InitHolesMatrix(comdef::decodingboard::pushbutton::kInitLargeRect,
                                   comdef::color::kLight,
                                   comdef::kEmptyString,
                                   comdef::breakerarea::kDefRowBreakIndex,
                                   &QPushButton::clicked,
                                   new CustomControls(),
                                   &CustomControls::SetQPushButtonColor,
                                   false);

    holes_matrix_->EnableNewRow();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     Breaker::~Breaker
/// \brief  Destructor
///         - Cleanup activities (Do nothing right now, shared_ptr variable will be destroyed automatically)
///
/// \param  none
///
/// \return none
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Breaker::~Breaker(){}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \fn     Breaker::GetHolesMatrix
/// \brief  Get hole matrix (all of push buttons in Breaker area)
///
/// \param  none
///
/// \return const shared_ptr<HoleMatrix>&
/// \brief  holes matrix in Breaker area
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const shared_ptr<HoleMatrix>& Breaker::GetHolesMatrix(){ return holes_matrix_; }
