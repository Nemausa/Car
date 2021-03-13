#pragma once

#include <CarApi.h>

class CanDrv : public carsrv::CarApi
{
public:
    CanDrv() = default;
    ~CanDrv() = default;

    bool
    setValue(const SigName& name, SigValue& value)
    {
        return Set(name, value);
    }
};