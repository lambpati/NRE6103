#pragma once

class Tally {
private:
   inline static bool flux;

public:
    //Methods
    Tally() = default;

    //Getters
    static const bool getTallyType() { return flux; };

    //Setters
    static void setTallyType(bool f) { flux = f; }
};