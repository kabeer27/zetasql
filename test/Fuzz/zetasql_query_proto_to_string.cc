#include <algorithm>
#include <array>
#include <cctype>
#include <cstdint>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "zetasql_query_grammar.pb.h"
#include "zetasql_queries.pb.h"

using namespace zetasql_query_grammar;

#define CONV_FN(TYPE, VAR_NAME) std::string TYPE##ToString(const TYPE& VAR_NAME)

namespace zetasql_fuzzer{

namespace {
constexpr uint32_t kMaxColumnNumber = 20;
constexpr uint32_t kMaxTableNumber = 8;

}

CONV_FN(Column, col) {
    std::string ret("Col");
    ret += std::to_string(col.col() % kMaxColumnNumber);
    return ret;
}

CONV_FN(Table, table) {
    std::string ret("Table");
    ret += std::to_string(table.table() % kMaxTableNumber);
    return ret;
}

CONV_FN(ColumnDefinition, col_def) {
    std::string ret;
    ret += ColumnToString(col_def.col());
    // To do implementaton of typenames and column constraints
    return ret;
}

CONV_FN(Replace, replace) {
    std::string ret;
    if (replace.exist()) {
        ret += "OR REPLACE";
    }
    return ret;
}

CONV_FN(IfNotExist, if_not_exist) {
    std::string ret;
    if (if_not_exist.exist()) {
        ret += "IF NOT EXISTS";
    }
}

CONV_FN(TableStructure, table_structure) {
    std::string ret;
    ret += ColumnDefinitionToString(table_structure.col_def());

    for(int i = 0; i < table_structure.extra_col_defs_size(); i++) {
        ret +=  ", ";
        ret += ColumnDefinitionToString(table_structure.extra_col_defs(i));
    }

    // To do Table constraints
    return ret;
}

CONV_FN(CreateTable, create_table) {
    std::string ret("CREATE ");
    if (create_table.has_replace()) {
        ret += ReplaceToString(create_table.replace());
        ret += " ";
    }
    if (create_table.has_temp_modifier()) {
        ret += create_table.temp_modifier();
        ret += " ";
    }

    ret += "TABLE ";
    if (create_table.has_if_not_exist()) {
        ret += "IF NOT EXISTS ";
    }
    ret += TableToString(create_table.table());
    ret += "(";
    ret += TableStructureToString(create_table.table_structure());
    ret += ")";
    // To do partition by cluster by options and as query.
    return ret;
}

CONV_FN(SQLQuery, query) {
    //Todo Switch case for different types of queries.
    return CreateTableToString(query.create_table());
}

std::vector<std::string> SQLQueriesToVec(const SQLQueries& sql_queries) {
  std::vector<std::string> queries;
  //queries.reserve(sql_queries.extra_queries_size() + 1);
  queries.push_back(CreateTableToString(sql_queries.create_table()) + ";");
  //for (int i = 0; i < sql_queries.extra_queries_size(); i++) {
  //  std::string query = SQLQueryToString(sql_queries.extra_queries(i));
  //  if (query == "")
  //    continue;
    //query += ";";
    //queries.push_back(query);
  //}
  return queries;
}

CONV_FN(SQLQueries, sql_queries) {
    std::string queries;

    for(std::string& query : SQLQueriesToVec(sql_queries)) {
        queries += query;
         queries += "\n";
    }
}


} //name space zetasql_fuzzer