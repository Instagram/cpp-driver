/*
  Copyright (c) 2014 DataStax

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#include "cassandra.hpp"
#include "statement.hpp"


extern "C" {

CASS_EXPORT
CassStatement* cass_statement_new(CassString statement,
                   size_t parameter_count,
                   CassConsistency consistency) {
  cass::Statement* query = new cass::QueryRequest(parameter_count, consistency);
  query->statement(statement.data, statement.length);
  return CassStatement::to(query);
}

CASS_EXPORT
void cass_statement_free(CassStatement *statement) {
  statement->release();
}

CASS_EXPORT
CassError cass_statement_bind_null(CassStatement* statement,
                                   cass_size_t index) {
  return statement->bind_null(index);
}

CASS_EXPORT
CassError cass_statement_bind_int32(CassStatement* statement,
                                    size_t index,
                                    int32_t value) {
  return statement->bind_int32(index, value);
}

CASS_EXPORT
CassError cass_statement_bind_int64(CassStatement* statement,
                                    size_t index,
                                    int64_t value) {
  return statement->bind_int64(index, value);
}

CASS_EXPORT
CassError cass_statement_bind_float(CassStatement* statement,
                                    size_t index,
                                    float value) {
  return statement->bind_float(index, value);
}

CASS_EXPORT
CassError cass_statement_bind_double(CassStatement* statement,
                                     size_t index,
                                     double value) {
  return statement->bind_double(index, value);
}

CASS_EXPORT
CassError cass_statement_bind_bool(CassStatement* statement,
                                   size_t index,
                                   cass_bool_t value) {
  return statement->bind_bool(index, value);
}

CASS_EXPORT
CassError cass_statement_bind_string(CassStatement* statement,
                                     size_t index,
                                     CassString value) {
  return statement->bind(index, value.data, value.length);
}

CASS_EXPORT
CassError cass_statement_bind_bytes(CassStatement* statement,
                                    size_t index,
                                    CassBytes value) {
  return statement->bind(index, value.data, value.size);
}

CASS_EXPORT
CassError cass_statement_bind_uuid(CassStatement* statement,
                                   size_t index,
                                   const CassUuid value) {
  return statement->bind(index, value);
}

CASS_EXPORT
CassError cass_statement_bind_inet( CassStatement* statement,
                                    size_t index,
                                    CassInet value) {
  return statement->bind(index, value.address, value.address_length);
}

CASS_EXPORT
CassError cass_statement_bind_decimal(CassStatement* statement,
                                      cass_size_t index,
                                      CassDecimal value) {
  return statement->bind(index, value.scale, value.varint.data, value.varint.size);
}

CASS_EXPORT
CassError cass_statement_bind_collection( CassStatement* statement,
                                          size_t index,
                                          const CassCollection* collection,
                                          cass_bool_t is_map) {
  return statement->bind(index, collection->from(), static_cast<bool>(is_map));
}

CASS_EXPORT
CassError cass_statement_bind_custom(CassStatement* statement,
                                     cass_size_t index,
                                     cass_size_t size,
                                     cass_byte_t** output) {
  return statement->bind(index, size, output);
}

} // extern "C"
