#include <iostream>
#include "../utils/data.h"

class Statistics : public Record {

public:
    const std::string key;
    const std::string title;
    int value;

    Statistics(std::string key, std::string title, int numberOfSales);
    ~Statistics();

    void display() const override;

    std::vector<std::string> toCsvRow() const override;
};