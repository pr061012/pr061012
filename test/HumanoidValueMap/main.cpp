#include <iostream>
#include <cassert>

#include "../../model/World/Object/Creatures/Humanoid/HumanoidValueMap.h"

class Test : public Object
{
public:
    Test(Vector coords, uint amount, double size) :
        Object(RESOURCE, true, false),
        amount(amount)
    {
        this -> setCoords(coords);
        this -> setShapeSize(size);
        this -> setShapeType(CIRCLE);
    }

    std::vector<Action>* getActions() { return nullptr; }
    void receiveMessage(Message msg) {}
    uint damage(uint delta) { return 0; }
    uint heal(uint delta) { return 0; }
    uint getHealthPoints() const { return amount; }
    uint getMaxHealthPoints() const { return 0; }
    std::string getTypeName() const { return "test"; }

private:
    uint amount;
};

int main()
{
    srand(time(nullptr));

    // Creating heap.
    ObjectHeap heap;

    // Creating value map.
    HumanoidValueMap map(&heap, 10, 10, 1);
    Vector coords = map.getBestPlace();
    assert(coords.getX() == -1);
    assert(coords.getY() == -1);

    // Creating objects.
    Test t1(Vector(4.5, 4.5), 1, 0.5); heap.push(&t1);
    Test t2(Vector(3.1, 7.2), 1, 0.5); heap.push(&t2);

    // Reevaluating map.
    map.reevaluate();
    coords = map.getBestPlace();
    std::cout << map.print() << std::endl << coords.getX() << " " <<
                 coords.getY() << std::endl;

    return 0;
}
