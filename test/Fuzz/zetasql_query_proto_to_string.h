#include <string>
#include <vector>

#include "zetasql_queries.pb.h"

namespace zetasql_fuzzer {
std::string SQLQueriesToString(
    const zetasql_query_grammar::SQLQueries& sql_queries);
std::vector<std::string> SQLQueriesToVec(
    const zetasql_query_grammar::SQLQueries& sql_queries);

}


//std::string PrintfToString(const zetasql_query_grammar::Printf&);
//std::string StrftimeFnToString(const zetasql_query_grammar::StrftimeFn&);
//std::string ExprToString(const zetasql_query_grammar::Expr&);
//std::string SQLQueryToString(const zetasql_query_grammar::SQLQuery&);