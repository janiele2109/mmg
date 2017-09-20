#ifndef DECODINGBOARD_H
#define DECODINGBOARD_H

#include <memory>

using namespace std;

class Breaker;
class MakerAreas;

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
        shared_ptr<Breaker>      breaker_areas_;
        shared_ptr<MakerAreas>   maker_areas_;
};

#endif // DECODINGBOARD_H
