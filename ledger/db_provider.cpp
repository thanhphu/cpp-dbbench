/*
Copyright Medium Corp. 2019 All Rights Reserved.
creator : hs.kwon
*/

#include <ledger/db_provider.h>

#include <sys/types.h>
#include <sys/stat.h>

namespace avis {

DBProvider::DBProvider() = default;

DBProvider::~DBProvider() = default;

bool DBProvider::create(const std::string& dbname, int dbType) {

    struct stat st{};
    if (stat(dbname.c_str(), &st) != 0) {
        std::string cmd = "mkdir -p ";
        cmd.append(dbname);
        system(cmd.c_str());
    }

    switch (dbType) {
        case DBType::LEVEL_DB: _db = new LevelDB(); break;
        case DBType::ROCKS_DB: _db = new RocksDB(); break;
        case DBType::REDIS   : _db = new RedisDB(); break;
        case DBType::LM_DB   : _db = new LMDB();    break;
        default: _db = new LevelDB(); break;
    }

    return _db->open(dbname);
}

StateDB* DBProvider::createSingle(const std::string& dbname, int dbType) {
    StateDB* _db{};

    struct stat st{};
    if (stat(dbname.c_str(), &st) != 0) {
        std::string cmd = "mkdir -p ";
        cmd.append(dbname);
        system(cmd.c_str());
    }

    switch (dbType) {
        case DBType::LEVEL_DB: _db = new LevelDB(); break;
        case DBType::ROCKS_DB: _db = new RocksDB(); break;
        case DBType::REDIS   : _db = new RedisDB(); break;
        case DBType::LM_DB   : _db = new LMDB();    break;
        default: _db = new LevelDB(); break;
    }

    return _db;
}
}
