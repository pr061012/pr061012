#include <iostream>
#include <cassert>

#include "../../model/World/ParamArray/ParamArray.h"
#include "../../model/World/ParamArray/EParamArrayBadKey.h"

int main()
{
    ParamArray pa;
    bool exc_was = false;

    // Testing exception throwing for getValue().
    try
    {
        assert(pa.getValue("key") == 0);
    }
    catch(EParamArrayBadKey & exc)
    {
        exc_was = true;
    }
    assert(exc_was == true);

    // Testing adding and getting values.
    pa.addKey("key", 1);
    assert(pa.getValue("key") == 1);
    pa.addKey("another_key", 2);
    assert(pa.getValue("another_key") == 2);

    // Testing key remove.
    assert(pa.removeKey("key") == true);
    assert(pa.removeKey("key") == false);

    // Testing what key doesn't exist anymore.
    exc_was = false;
    try
    {
        assert(pa.getValue("key") == 0);
    }
    catch(EParamArrayBadKey & exc)
    {
        exc_was = true;
    }
    assert(exc_was == true);

    return 0;
}
