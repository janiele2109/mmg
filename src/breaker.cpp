#include "breaker.h"
#include "holematrix.h"

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
                                   &CustomControls::SetQPushButtonColor);

    holes_matrix_->EnableNewRow();
}

Breaker::~Breaker(){}

const shared_ptr<HoleMatrix>& Breaker::GetHolesMatrix(){ return holes_matrix_; }
