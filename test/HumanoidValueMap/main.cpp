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
    srand(time(nullptr));

    // Creating heap.
    ObjectHeap heap;

    // Creating value map.
    HumanoidValueMap map(&heap, 10, 10, 1);
    Vector coords = map.getBestPlace();
    assert(coords.getX() == -1);
    assert(coords.getY() == -1);

    // Creating objects.
    Test t1(Vector(4.5, 4.9)); heap.push(&t1);
    Test t2(Vector(3.1, 7.2)); heap.push(&t2);
    Test t3(Vector(1.2, 9.1)); heap.push(&t3);
    Test t4(Vector(8.9, 2.1)); heap.push(&t4);
    Test t5(Vector(0.1, 2.5)); heap.push(&t5);
    Test t6(Vector(4.4, 4.2)); heap.push(&t6);

    // Reevaluating map.
    map.reevaluate();
    coords = map.getBestPlace();
    std::cout << map.print() << std::endl << coords.getX() << " " <<
                 coords.getY() << std::endl;

    return 0;
}
