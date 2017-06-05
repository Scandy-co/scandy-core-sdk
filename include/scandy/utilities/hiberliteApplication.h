/****************************************************************************\
 * Copyright (C) 2016 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

// For distribution.

#ifndef Scandy_Hiberlite_App_h
#define Scandy_Hiberlite_App_h

#include <scandy/core/PoseSerialization.h>
#include <scandy/core/IntrinsicsSerialization.h>
#include <scandy/core/logging.h>
#include <scandy/core/ScannerType.h>

#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/json.hpp>

#include <hiberlite.h>

#include <map>

using namespace scandy::internal::core;


namespace hiberlite {

  // *** Start scandy::core::ScannerType
  template <class A>
  void hibernate(A& ar, scandy::core::ScannerType& value, const unsigned int) {
    ar & db_atom<scandy::core::ScannerType>(value);
  }

  template <>
  inline std::string db_atom<scandy::core::ScannerType>::sqliteStorageClass() {
    return "INTEGER";
  }

  template <>
  template <class Stmt, class Arg>
  void db_atom<scandy::core::ScannerType>::loadValue(Stmt& res, Arg& arg) {
    val = static_cast<scandy::core::ScannerType>(res.get_int(arg));
  }

  template <>
  inline void db_atom<scandy::core::ScannerType>::bindValue(sqlite3_stmt* stmt, int col) {
    sqlite3_bind_int(stmt, col, static_cast<int>(val));
  }
  // *** end auto serialization of ScannerType

  // *** Start bool
  template <class A>
  void hibernate(A& ar, bool& value, const unsigned int) {
    ar & db_atom<bool>(value);
  }

  template <>
  inline std::string db_atom<bool>::sqliteStorageClass() {
    return "INTEGER";
  }

  template <>
  template <class Stmt, class Arg>
  void db_atom<bool>::loadValue(Stmt& res, Arg& arg) {
    val = static_cast<bool>(res.get_int(arg));
  }

  template <>
  inline void db_atom<bool>::bindValue(sqlite3_stmt* stmt, int col) {
    sqlite3_bind_int(stmt, col, static_cast<int>(val));
  }
  // *** end auto serialization of bool

  // *** Start scandy::utilities::Pose
  template <class A>
  void hibernate(A& ar, scandy::utilities::Pose& value, const unsigned int) {
    ar & db_atom<scandy::utilities::Pose>(value);
  }

  template <>
  inline std::string db_atom<scandy::utilities::Pose>::sqliteStorageClass() {
    return "TEXT";
  }

  template <>
  template <class Stmt, class Arg>
  void db_atom<scandy::utilities::Pose>::loadValue(Stmt& res, Arg& arg) {
    std::stringstream json;
    const char *szjson = reinterpret_cast<const char *>(res.get_text(arg));
    json << szjson;
    if(json.str().length() > 0)
    {
      cereal::JSONInputArchive iarchive(json);
      iarchive(val);
    }
  }

  template <>
  inline void db_atom<scandy::utilities::Pose>::bindValue(sqlite3_stmt* stmt, int col) {
    std::stringstream json;
    {
      cereal::JSONOutputArchive oarchive(json);
      oarchive(val);
    }
    int rc = sqlite3_bind_text(stmt, col, json.str().c_str(), -1, SQLITE_TRANSIENT);
    if(rc != SQLITE_OK) {
      logging::error("Error could not bind json");
    }
  }
  // *** end auto serialization of scandy::utilities::Pose

  // *** Start scandy::utilities::RelativePose
  template <class A>
  void hibernate(A& ar, scandy::utilities::RelativePose& value, const unsigned int) {
    ar & db_atom<scandy::utilities::RelativePose>(value);
  }

  template <>
  inline std::string db_atom<scandy::utilities::RelativePose>::sqliteStorageClass() {
    return "TEXT";
  }

  template <>
  template <class Stmt, class Arg>
  void db_atom<scandy::utilities::RelativePose>::loadValue(Stmt& res, Arg& arg) {
    std::stringstream json;
    const char *szjson = reinterpret_cast<const char *>(res.get_text(arg));
    json << szjson;
    if(json.str().length() > 0)
    {
      cereal::JSONInputArchive iarchive(json);
      iarchive(val);
    }
  }

  template <>
  inline void db_atom<scandy::utilities::RelativePose>::bindValue(sqlite3_stmt* stmt, int col) {
    std::stringstream json;
    {
      cereal::JSONOutputArchive oarchive(json);
      oarchive(val);
    }
    int rc = sqlite3_bind_text(stmt, col, json.str().c_str(), -1, SQLITE_TRANSIENT);
    if(rc != SQLITE_OK) {
      logging::error("Error could not bind json");
    }
  }
  // *** end auto serialization of scandy::utilities::Pose

  // *** Start scandy::utilities::CameraIntrinsics
  template <class A>
  void hibernate(A& ar, scandy::utilities::CameraIntrinsics& value, const unsigned int) {
    ar & db_atom<scandy::utilities::CameraIntrinsics>(value);
  }

  template <>
  inline std::string db_atom<scandy::utilities::CameraIntrinsics>::sqliteStorageClass() {
    return "TEXT";
  }

  template <>
  template <class Stmt, class Arg>
  void db_atom<scandy::utilities::CameraIntrinsics>::loadValue(Stmt& res, Arg& arg) {
    std::stringstream json;
    const char *szjson = reinterpret_cast<const char *>(res.get_text(arg));
    json << szjson;
    if(json.str().length() > 0)
    {
      cereal::JSONInputArchive iarchive(json);
      iarchive(val);
    }
  }

  template <>
  inline void db_atom<scandy::utilities::CameraIntrinsics>::bindValue(sqlite3_stmt* stmt, int col) {
    std::stringstream json;
    {
      cereal::JSONOutputArchive oarchive(json);
      oarchive(val);
    }
    int rc = sqlite3_bind_text(stmt, col, json.str().c_str(), -1, SQLITE_TRANSIENT);
    if(rc != SQLITE_OK) {
      logging::error("Error could not bind json");
    }
  }
  // *** end auto serialization of scandy::utilities::CameraIntrinsics
}

namespace scandy { namespace utilities {

/**
 * Hiberlite has the capability to customize queries but the main header doesn't expose it.
 * Expose that functionality here.  No need to worry about binding parameters since we use the
 * database internally exclusively.
 * @param  con    [description]
 * @param  [name] [description]
 * @return        [description]
 */
class ScandyHiberliteDatabase : public hiberlite::Database {
public:
  ScandyHiberliteDatabase() : hiberlite::Database() {}

  // we need to be able to specify constraints
  template<class T>
  std::vector<hiberlite::sqlid_t> getBeanIds(std::string where = "", std::string order = "") {
    return dbSelectIds(con, getClassName<T>(), where, order);
  }

  // we need to execute raw sql to add column constraints
  void dbExecQuery(std::string query) {
    hiberlite::Database::dbExecQuery(query);
  }

  // get underlying sqlite error messages
  std::string getErrorMsg() {
    return std::string(sqlite3_errmsg(con->getSQLite3Ptr()));
  }

  // we need to be able to check if a file is compatible with current track store metadata
  bool checkModel()
  {
    if(!mx)
      throw std::logic_error("register bean classes first");
    hiberlite::Model mdl = mx->getModel();
    for(hiberlite::Model::iterator it = mdl.begin(); it != mdl.end(); it++) {
      hiberlite::Table& scandy_table = it->second;

      // query database for table info
      std::string table_query = "pragma table_info(" + scandy_table.name + ");";
      sqlite3_stmt* sql_cmd = nullptr;
      int rc = sqlite3_prepare_v2(con->getSQLite3Ptr(), table_query.c_str(), -1, &sql_cmd, NULL);
      if(rc != SQLITE_OK) {
        return false;
      }

      // get column info for table (name, type)
      std::map<std::string, std::string> existing_columns;
      do {
        rc = sqlite3_step(sql_cmd);
        std::string column_name = (char *) sqlite3_column_text(sql_cmd, 1);
        std::string column_type = (char *) sqlite3_column_text(sql_cmd, 2);
        existing_columns[column_name] = column_type;
      }
      while(rc == SQLITE_ROW);

      // check if all columns exist
      for(std::map<std::string, hiberlite::Column>::iterator c = scandy_table.columns.begin();
        c != scandy_table.columns.end();
        c++) {
        hiberlite::Column& col = c->second;
        bool bColumnExists = false;
        if(existing_columns.find(col.name) != existing_columns.end() &&
          existing_columns[col.name] == col.storage_type) {
          bColumnExists = true;
        }
        if(!bColumnExists) {
          return false;
        }
      }
    }
    return true;
  }
};

}}

#endif
