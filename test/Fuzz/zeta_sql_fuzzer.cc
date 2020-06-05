#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "zetasql_query_proto_to_string.h"
#include "zetasql_query_grammar.pb.h"
#include "libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"

using namespace zetasql_query_grammar;

DEFINE_BINARY_PROTO_FUZZER(const SQLQueries& sql_queries) {
    std::vector<std::string> queries = zetasql_fuzzer::SQLQueriesToVec(sql_queries);
    for (std::string query : queries) {
        std::cout << query << std::endl;
    }

}