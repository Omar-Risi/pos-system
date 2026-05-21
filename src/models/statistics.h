#include <iostream>
#include "../utils/data.h"

class Statistics : public Record {
    
    public:

    const std::string title;
    int value; 

    Statistics(std::string const title, int numberOfSales);
    ~Statistics();

    void display() const override;

};