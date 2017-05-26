/* Copyright 2014  Endless Mobile
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"

#include "xapian-enums.h"

#define XAPIAN_GLIB_DEFINE_ENUM_VALUE(value,nick) \
  { value, #value, nick },

#define XAPIAN_GLIB_DEFINE_ENUM_TYPE(TypeName,type_name,values) \
GType \
type_name ## _get_type (void) \
{ \
  static volatile gsize g_define_id__volatile = 0; \
  if (g_once_init_enter (&g_define_id__volatile)) \
    { \
      static const GEnumValue v[] = { \
        values \
        { 0, NULL, NULL }, \
      }; \
      GType g_define_id = g_enum_register_static (g_intern_static_string (#TypeName), v); \
      g_once_init_leave (&g_define_id__volatile, g_define_id); \
    } \
  return g_define_id__volatile; \
}

#define XAPIAN_GLIB_DEFINE_FLAGS_TYPE(TypeName,type_name,values) \
GType \
type_name ## _get_type (void) \
{ \
  static volatile gsize g_define_id__volatile = 0; \
  if (g_once_init_enter (&g_define_id__volatile)) \
    { \
      static const GFlagsValue v[] = { \
        values \
	{ 0, NULL, NULL }, \
      }; \
      GType g_define_id = g_flags_register_static (g_intern_static_string (#TypeName), v); \
      g_once_init_leave (&g_define_id__volatile, g_define_id); \
    } \
  return g_define_id__volatile; \
}

XAPIAN_GLIB_DEFINE_ENUM_TYPE (XapianDatabaseAction, xapian_database_action,
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_DATABASE_ACTION_CREATE_OR_OPEN, "create-or-open")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_DATABASE_ACTION_CREATE, "create")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_DATABASE_ACTION_CREATE_OR_OVERWRITE, "create-or-overwrite")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_DATABASE_ACTION_OPEN, "open"))

XAPIAN_GLIB_DEFINE_ENUM_TYPE (XapianError, xapian_error,
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_ERROR_ASSERTION, "assertion")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_ERROR_INVALID_ARGUMENT, "invalid-argument")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_ERROR_INVALID_OPERATION, "invalid-operation")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_ERROR_UNIMPLEMENTED, "unimplemented")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_ERROR_DATABASE, "database")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_ERROR_DATABASE_CORRUPT, "database-corrupt")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_ERROR_DATABASE_CREATE, "database-create")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_ERROR_DATABASE_LOCK, "database-lock")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_ERROR_DATABASE_MODIFIED, "database-modified")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_ERROR_DATABASE_OPENING, "database-opening")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_ERROR_DATABASE_VERSION, "database-version")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_ERROR_DOC_NOT_FOUND, "doc-not-found")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_ERROR_FEATURE_UNAVAILABLE, "feature-unavailable")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_ERROR_INTERNAL, "internal")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_ERROR_NETWORK, "network")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_ERROR_NETWORK_TIMEOUT, "network-timeout")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_ERROR_QUERY_PARSER, "query-parser")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_ERROR_SERIALISATION, "serialisation")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_ERROR_RANGE, "range")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_ERROR_LAST, "type-last"))

XAPIAN_GLIB_DEFINE_ENUM_TYPE (XapianQueryOp, xapian_query_op,
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_OP_AND, "and")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_OP_OR, "or")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_OP_AND_NOT, "and-not")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_OP_XOR, "xor")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_OP_AND_MAYBE, "and-maybe")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_OP_FILTER, "filter")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_OP_NEAR, "near")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_OP_PHRASE, "phrase")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_OP_VALUE_RANGE, "value-range")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_OP_SCALE_WEIGHT, "scale-weight")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_OP_ELITE_SET, "elite-set")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_OP_VALUE_GE, "value-ge")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_OP_VALUE_LE, "value-le")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_OP_SYNONYM, "synonym")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_OP_LAST, "op-last"))

XAPIAN_GLIB_DEFINE_FLAGS_TYPE (XapianTermGeneratorFeature, xapian_term_generator_feature,
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_TERM_GENERATOR_FEATURE_NONE, "none")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_TERM_GENERATOR_FEATURE_SPELLING, "spelling"))

XAPIAN_GLIB_DEFINE_FLAGS_TYPE (XapianQueryParserFeature, xapian_query_parser_feature,
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_PARSER_FEATURE_BOOLEAN, "boolean")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_PARSER_FEATURE_PHRASE, "phrase")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_PARSER_FEATURE_LOVEHATE, "lovehate")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_PARSER_FEATURE_BOOLEAN_ANY_CASE, "boolean-any-case")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_PARSER_FEATURE_WILDCARD, "wildcard")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_PARSER_FEATURE_PURE_NOT, "pure-not")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_PARSER_FEATURE_PARTIAL, "partial")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_PARSER_FEATURE_SPELLING_CORRECTION, "spelling-correction")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_PARSER_FEATURE_SYNONYM, "synonym")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_PARSER_FEATURE_AUTO_SYNONYMS, "auto-synonyms")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_PARSER_FEATURE_AUTO_MULTIWORD_SYNONYMS, "auto-multiword-synonyms")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_QUERY_PARSER_FEATURE_DEFAULT, "default"))

XAPIAN_GLIB_DEFINE_ENUM_TYPE (XapianStemStrategy, xapian_stem_strategy,
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_STEM_STRATEGY_STEM_NONE, "stem-none")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_STEM_STRATEGY_STEM_SOME, "stem-some")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_STEM_STRATEGY_STEM_ALL, "stem-all")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_STEM_STRATEGY_STEM_ALL_Z, "stem-all-z"))

XAPIAN_GLIB_DEFINE_FLAGS_TYPE (XapianDatabaseFlags, xapian_database_flags,
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_DATABASE_FLAGS_NO_SYNC, "no-sync")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_DATABASE_FLAGS_FULL_SYNC, "full-sync")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_DATABASE_FLAGS_DANGEROUS, "dangerous")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_DATABASE_FLAGS_NO_TERMLIST, "no-termlist")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_DATABASE_FLAGS_RETRY_LOCK, "retry-lock"))

XAPIAN_GLIB_DEFINE_ENUM_TYPE (XapianDatabaseBackend, xapian_database_backend,
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_DATABASE_BACKEND_GLASS, "glass")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_DATABASE_BACKEND_CHERT, "chert")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_DATABASE_BACKEND_STUB, "stub")
  XAPIAN_GLIB_DEFINE_ENUM_VALUE (XAPIAN_DATABASE_BACKEND_INMEMORY, "inmemory"))
