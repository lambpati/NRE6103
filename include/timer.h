#pragma once

#include <iostream>
#include <chrono>

struct timer{
    typedef std::chrono::steady_clock clock ;
    typedef std::chrono::seconds seconds ;

    void reset() { start = clock::now() ; }

    unsigned long long seconds_elapsed() const
    { return std::chrono::duration_cast<seconds>( clock::now() - start ).count() ; }

    private: clock::time_point start = clock::now() ;
};