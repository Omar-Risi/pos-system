#include <iostream>
#include "../utils/data.h"

class Statistics : public Record {
private:
    std::string key;
    std::string title;
    int value;

public:

    Statistics(std::string key, std::string title, int numberOfSales);
    ~Statistics();

    const std::string &getKey() const;
    void setKey(const std::string &value);

    const std::string &getTitle() const;
    void setTitle(const std::string &value);

    int getValue() const;
    void setValue(int value);

    void display() const override;

    std::vector<std::string> toCsvRow() const override;
};