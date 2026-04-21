#include "service.h"
#include "data.h"

Database *Service::db_ptr = nullptr;
void Service::setDatabase(Database *_db_ptr) { db_ptr = _db_ptr; }
Database *Service::getDatabase() { return db_ptr; }
