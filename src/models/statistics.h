#include <iostream>
#include "../utils/data.h"

class Statistics : public Record {
    
    public:

    const std::string title;
    int numberOfSales; 

    Statistics(std::string title, int numberOfSales);
    ~Statistics();

    void display() const override;

};