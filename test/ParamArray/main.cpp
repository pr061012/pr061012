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
        assert(pa.getValue<int>("key") == 0);
    }
    catch(EParamArrayBadKey & exc)
    {
        exc_was = true;
    }
    assert(exc_was == true);

    // Testing adding and getting values.
    pa.addKey<int>("key", 1);
    assert(pa.getValue<int>("key") == 1);
    pa.addKey<double>("another_key", 3.14);
    assert(pa.getValue<double>("another_key") == 3.14);

    // Testing key remove.
    assert(pa.removeKey("key") == true);
    assert(pa.removeKey("key") == false);

    // Testing what key doesn't exist anymore.
    exc_was = false;
    try
    {
        assert(pa.getValue<int>("key") == 0);
    }
    catch(EParamArrayBadKey & exc)
    {
        exc_was = true;
    }
    assert(exc_was == true);

    pa.addKey<int>("key", 1);
    pa.addKey<long long>("another_key", 2);
    pa.addKey<std::string>("string key", "string key value");

    return 0;
}
