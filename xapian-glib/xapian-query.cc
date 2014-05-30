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

#include "xapian-query-private.h"

#include "xapian-enums.h"
#include "xapian-error-private.h"

#define XAPIAN_QUERY_GET_PRIVATE(obj) \
  ((XapianQueryPrivate *) xapian_query_get_instance_private ((XapianQuery *) (obj)))

typedef struct {
  Xapian::Query *mQuery;
} XapianQueryPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (XapianQuery, xapian_query, G_TYPE_OBJECT)

Xapian::Query *
xapian_query_get_internal (XapianQuery *self)
{
  XapianQueryPrivate *priv = XAPIAN_QUERY_GET_PRIVATE (self);

  return priv->mQuery;
}

static void
xapian_query_dispose (GObject *gobject)
{
  XapianQueryPrivate *priv = XAPIAN_QUERY_GET_PRIVATE (gobject);

  if (priv->mQuery)
    {
      delete priv->mQuery;
      priv->mQuery = NULL;
    }

  G_OBJECT_CLASS (xapian_query_parent_class)->dispose (gobject);
}

static void
xapian_query_class_init (XapianQueryClass *klass)
{
  G_OBJECT_CLASS (klass)->dispose = xapian_query_dispose;
}

static void
xapian_query_init (XapianQuery *self)
{
}

XapianQuery *
xapian_query_new_from_query (const Xapian::Query &aQuery)
{
  XapianQuery *res = static_cast<XapianQuery *> (g_object_new (XAPIAN_TYPE_QUERY, NULL));

  XapianQueryPrivate *priv = XAPIAN_QUERY_GET_PRIVATE (res);
  priv->mQuery = new Xapian::Query (aQuery);

  return res;
}

/**
 * xapian_query_new:
 *
 * Creates a new, empty #XapianQuery instance.
 *
 * Returns: (transfer full): the newly created #XapianQuery instance
 */
XapianQuery *
xapian_query_new (void)
{
  return static_cast<XapianQuery *> (g_object_new (XAPIAN_TYPE_QUERY, NULL));
}

/**
 * xapian_query_new_for_term:
 * @term: the term to query
 *
 * Creates a new #XapianQuery for the given @term.
 *
 * Returns: (transfer full): the newly created #XapianQuery instance
 */
XapianQuery *
xapian_query_new_for_term (const char *term)
{
  g_return_val_if_fail (term != NULL, NULL);

  Xapian::Query q = Xapian::Query (std::string (term));

  return xapian_query_new_from_query (q);
}

/**
 * xapian_query_new_for_pair:
 * @op: a #XapianQueryOp
 * @a: a #XapianQuery
 * @b: a #XapianQuery
 *
 * Creates a new #XapianQuery using two #XapianQuery instances
 * and an @op between the two.
 *
 * Returns: (transfer full): the newly created #XapianQuery instance
 */
XapianQuery *
xapian_query_new_for_pair (XapianQueryOp op,
                           XapianQuery  *a,
                           XapianQuery  *b)
{
  g_return_val_if_fail (XAPIAN_IS_QUERY (a), NULL);
  g_return_val_if_fail (XAPIAN_IS_QUERY (b), NULL);

  Xapian::Query *query_a = xapian_query_get_internal (a);
  Xapian::Query *query_b = xapian_query_get_internal (b);
  Xapian::Query::op query_op = Xapian::Query::OP_AND;

#ifdef XAPIAN_GLIB_ENABLE_DEBUG
  switch (op)
    {
    case XAPIAN_QUERY_OP_AND:
      query_op = Xapian::Query::OP_AND;
      break;

    case XAPIAN_QUERY_OP_OR:
      query_op = Xapian::Query::OP_OR;
      break;

    case XAPIAN_QUERY_OP_AND_NOT:
      query_op = Xapian::Query::OP_AND_NOT;
      break;

    case XAPIAN_QUERY_OP_XOR:
      query_op = Xapian::Query::OP_XOR;
      break;

    case XAPIAN_QUERY_OP_AND_MAYBE:
      query_op = Xapian::Query::OP_AND_MAYBE;
      break;

    case XAPIAN_QUERY_OP_FILTER:
      query_op = Xapian::Query::OP_FILTER;
      break;

    case XAPIAN_QUERY_OP_NEAR:
      query_op = Xapian::Query::OP_NEAR;
      break;

    case XAPIAN_QUERY_OP_PHRASE:
      query_op = Xapian::Query::OP_PHRASE;
      break;

    case XAPIAN_QUERY_OP_VALUE_RANGE:
      query_op = Xapian::Query::OP_VALUE_RANGE;
      break;

    case XAPIAN_QUERY_OP_SCALE_WEIGHT:
      query_op = Xapian::Query::OP_SCALE_WEIGHT;
      break;

    case XAPIAN_QUERY_OP_ELITE_SET:
      query_op = Xapian::Query::OP_ELITE_SET;
      break;

    case XAPIAN_QUERY_OP_VALUE_GE:
      query_op = Xapian::Query::OP_VALUE_GE;
      break;

    case XAPIAN_QUERY_OP_VALUE_LE:
      query_op = Xapian::Query::OP_VALUE_LE;
      break;

    case XAPIAN_QUERY_OP_SYNONYM:
      query_op = Xapian::Query::OP_SYNONYM;
      break;

    default:
      g_assert_not_reached ();
    }
#else
  /* we keep XapianQueryOP and Xapian::Query::op in sync */
  query_op = (Xapian::Query::op) op;
#endif /* XAPIAN_GLIB_ENABLE_DEBUG */

  Xapian::Query query = Xapian::Query (query_op, *query_a, *query_b);

  return xapian_query_new_from_query (query);
}

/**
 * xapian_query_new_from_string:
 * @data: a string containing a query in normal form, as
 *   returned by xapian_query_serialise()
 *
 * Creates a new #XapianQuery from its normal form.
 *
 * Returns: (transfer full): the newly created #XapianQuery instance
 */
XapianQuery *
xapian_query_new_from_string (const char *data)
{
  g_return_val_if_fail (data != NULL, NULL);

  Xapian::Query query = Xapian::Query (std::string (data));

  return xapian_query_new_from_query (query);
}

/**
 * xapian_query_is_empty:
 * @query: a #XapianQuery
 *
 * Checks whether @query is empty.
 *
 * Returns: %TRUE if the #XapianQuery is empty
 */
gboolean
xapian_query_is_empty (XapianQuery *query)
{
  g_return_val_if_fail (XAPIAN_IS_QUERY (query), TRUE);

  return xapian_query_get_internal (query)->empty () ? TRUE : FALSE;
}

char *
xapian_query_get_description (XapianQuery *query)
{
  g_return_val_if_fail (XAPIAN_IS_QUERY (query), NULL);

  std::string desc = xapian_query_get_internal (query)->get_description ();

  return g_strdup (desc.c_str ());
}

unsigned int
xapian_query_get_length (XapianQuery *query)
{
  g_return_val_if_fail (XAPIAN_IS_QUERY (query), 0);

  return xapian_query_get_internal (query)->get_length ();
}

/**
 * xapian_query_serialise:
 * @query: a #XapianQuery
 *
 * Serialises @query into a normal form that can be used
 * with xapian_query_new_from_string().
 *
 * Returns: (transfer full): the query in normal form
 */
char *
xapian_query_serialise (XapianQuery *query)
{
  g_return_val_if_fail (XAPIAN_IS_QUERY (query), NULL);

  std::string data = xapian_query_get_internal (query)->serialise ();

  return g_strdup (data.c_str ());
}
