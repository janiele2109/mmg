#ifndef DECODINGBOARD_H
#define DECODINGBOARD_H

#include <memory>

using namespace std;

class BreakerAreas;
class MakerAreas;

class DecodingBoard
{
    public:
        DecodingBoard();
        ~DecodingBoard();

        shared_ptr<BreakerAreas> GetBreakerAreas();
        shared_ptr<MakerAreas> GetMakerAreas();

        void Draw();
        void DrawColorCombo();

    protected:

    private:
        shared_ptr<BreakerAreas> breaker_areas_;
        shared_ptr<MakerAreas>   maker_areas_;
};

#endif // DECODINGBOARD_H
