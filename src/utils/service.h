#include "data.h"

class Service {

  static Database *db_ptr;

public:
  /* Links the database to the service class to be used later
   * @param db_ptr pointer to database instance
   */
  static void registerDatabase(Database *_db_ptr);

  /* Returns database instance pointer
   *  @return db_ptr database pointer
   */
  static Database *getDatabase();

  ~Service() { delete db_ptr; }
};
