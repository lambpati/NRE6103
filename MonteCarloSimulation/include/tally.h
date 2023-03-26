#pragma once

class Tally{
    private:
        static bool flux;

    public:
        //Methods
        Tally() = default;

        //Getters
        void getTallyType();

        //Setters
        void setTallyType(bool f){ flux = f;}
}