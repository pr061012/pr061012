#include <iostream>
#include <cassert>

#include "../../model/World/Object/Creatures/Humanoid/HumanoidValueMap.h"

class Test : public Object
{
public:
    Test(Vector coords) : Object(RESOURCE, true, false)
    {
        this -> setCoords(coords);
    }

    std::vector<Action>* getActions() { return nullptr; }
    void receiveMessage(Message msg) {}
    uint damage(uint delta) { return 0; }
    uint heal(uint delta) { return 0; }
    uint getHealthPoints() const { return 0; }
    uint getMaxHealthPoints() const { return 0; }
    std::string getTypeName() const { return "test"; }
};

int main()
{
    // Creating heap.
    ObjectHeap heap;

    // Creating value map.
    HumanoidValueMap map(&heap, 10, 10, 1);
    assert(map.getBestPlace().getX() == -1);
    assert(map.getBestPlace().getY() == -1);

    // Creating objects.
    Test t1(Vector(4.5, 4.9));
    heap.push(&t1);

    // Reevaluating map.
    map.reevaluate();
    std::cout << map.print();

    return 0;
}
