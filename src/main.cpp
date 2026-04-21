#include "utils/data.h"
#include "utils/io.h"
#include "utils/menu.h"
#include "utils/service.h"
#include <iostream>

using namespace std;
int main() {

  Database db;
  Service::setDatabase(&db);

  cout << Service::getDatabase() << endl;

  return 0;
}
