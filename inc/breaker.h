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
