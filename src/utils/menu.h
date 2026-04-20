#pragma once
#include <functional>
#include <string>
#include <vector>

class Option {
  std::string title;
  std::function<void()> callback;

public:
  /* Constructs a new option
   *  @param _title title of the option
   *  @param _callback lambda function that executes upon
   * choosing the option
   */
  Option(std::string _title, std::function<void()> _callback);

  // Executes the callback function for the option
  void execute();

  /* Returns title of the option
   *  @return std::string title  title of the option
   */
  std::string getTitle();
};

class Menu {
  std::string title;
  std::vector<Option> options;

public:
  /* Constructs the Menu class
   *  @param _title title of the menu to display
   */
  Menu(std::string _title) : title(_title) {}

  /*  Appends a new option to the list of options
   *  @param option option details
   */
  void addOption(Option option);

  // Displays the list of options + one extra back option
  void display();

  // Creates a while loop and opens the menu
  void open();
};
