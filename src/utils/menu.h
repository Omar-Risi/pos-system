#pragma once
#include <functional>
#include <string>

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
