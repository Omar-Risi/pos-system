#include <iostream>
#include "../utils/data.h"

class Statistics : public Record {
private:
    std::string key;
    std::string title;
    int value;

public:

    /* Constructs a Statistics record
     * @param key unique key for the statistic
     * @param title human readable title
     * @param numberOfSales initial value
     */
    Statistics(std::string key, std::string title, int numberOfSales);

    /* Destructor
     * @return void
     */
    ~Statistics();

    /* Returns the statistic key
     * @return const std::string& key
     */
    const std::string &getKey() const;

    /* Sets the statistic key
     * @param value new key
     * @return void
     */
    void setKey(const std::string &value);

    /* Returns the statistic title
     * @return const std::string& title
     */
    const std::string &getTitle() const;

    /* Sets the statistic title
     * @param value new title
     * @return void
     */
    void setTitle(const std::string &value);

    /* Returns the statistic numeric value
     * @return int value
     */
    int getValue() const;

    /* Sets the statistic numeric value
     * @param value new numeric value
     * @return void
     */
    void setValue(int value);

    /* Displays statistic information
     * @return void
     */
    void display() const override;

    /* Converts the statistic to a CSV row
     * @return vector<string> row values
     */
    std::vector<std::string> toCsvRow() const override;
};