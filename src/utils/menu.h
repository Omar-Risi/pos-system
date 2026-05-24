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

  /* Executes the callback function for the option
   * @return void
   */
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
   *  @param _title title of the option
   *  @param _callback lambda function to run when selected
   */
  void addOption(std::string _title, std::function<void()> _callback);

  /* Displays the list of options + one extra back option
   * @return void
   */
  void display();

  /* Creates a while loop and opens the menu
   * @return void
   */
  void open();

  /* Opens a one-time menu (dialog style) and returns the selected index
   * @return int index  the selected option index
   */
  int openOnce();

  /* Simple yes/no dialog helper
   * @param title dialog title
   * @param yesLabel label for affirmative option
   * @param noLabel label for negative option
   * @return bool true if yes selected, false otherwise
   */
  static bool confirm(const std::string &title,
                      const std::string &yesLabel = "Yes",
                      const std::string &noLabel = "No");
};
