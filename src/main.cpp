#include "utils/data.h"
#include "utils/service.h"

using namespace std;
int main() {

  Database db;
  Service::registerDatabase(&db);

  return 0;
}
