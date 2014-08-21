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

/**
 * SECTION:xapian-simple-stopper
 * @Title: XapianSimpleStopper
 * @short_description: Simple stopper
 *
 * Simple implementation of Stopper class - this will suit most users.
 */

#include "config.h"

#include "xapian-stopper-private.h"
#include "xapian-simple-stopper.h"
#include "xapian-error-private.h"

G_DEFINE_TYPE (XapianSimpleStopper, xapian_simple_stopper, XAPIAN_TYPE_STOPPER)

static void
xapian_simple_stopper_class_init (XapianSimpleStopperClass *klass)
{
}

static Xapian::SimpleStopper *
xapian_simple_stopper_get_internal (XapianSimpleStopper *self)
{
  Xapian::Stopper *stopper = xapian_stopper_get_internal (XAPIAN_STOPPER (self));
  Xapian::SimpleStopper *simple_stopper = dynamic_cast<Xapian::SimpleStopper *> (stopper);

  return simple_stopper;
}


static void
xapian_simple_stopper_init (XapianSimpleStopper *self)
{
  Xapian::SimpleStopper *aStopper = new Xapian::SimpleStopper ();

  xapian_stopper_set_internal(XAPIAN_STOPPER (self), aStopper);
}

/**
 * xapian_simple_stopper_add:
 * @word: stop word to be added
 *
 * Adds a single stop word.
 * Since 1.2
 */
void
xapian_simple_stopper_add (XapianSimpleStopper *stopper,
                           const gchar *word)
{
  g_return_if_fail (XAPIAN_IS_SIMPLE_STOPPER (stopper));

  Xapian::SimpleStopper *mSimpleStopper = xapian_simple_stopper_get_internal(stopper);

  mSimpleStopper->add(word);
}

/**
 * xapian_simple_stopper_get_description:
 * @stopper: stopper
 *
 * Return a string describing this object. 
 *
 * Returns: (transfer full): description of the stopper
 * Since 1.2
 */
char *
xapian_simple_stopper_get_description (XapianSimpleStopper *stopper)
{
  g_return_val_if_fail (XAPIAN_IS_SIMPLE_STOPPER (stopper), NULL);

  Xapian::SimpleStopper *mSimpleStopper = xapian_simple_stopper_get_internal(stopper);

  std::string desc = mSimpleStopper->get_description ();

  return g_strdup (desc.c_str ());
}
