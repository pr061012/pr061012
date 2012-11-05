#include <iostream>
#include <cassert>

#include "../../model/World/ParamArray/ParamArray.h"

int main()
{
    ParamArray pa;

    assert(pa.getValue("key") == 0);

    pa.addKey("key", 1);
    assert(pa.getValue("key") == 1);

    pa.addKey("another_key", 2);
    assert(pa.getValue("another_key") == 2);

    assert(pa.removeKey("key") == true);
    assert(pa.getValue("key") == 0);

    assert(pa.removeKey("key") == false);

    return 0;
}
