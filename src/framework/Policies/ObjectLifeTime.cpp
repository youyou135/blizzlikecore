/*
 * Copyright (C) 2011-2013 BlizzLikeCore <http://blizzlike.servegame.com/>
 * Please, read the credits file.
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdlib>
#include "ObjectLifeTime.h"

namespace BlizzLike
{
    extern "C" void external_wrapper(void *p)
    {
        std::atexit( (void (*)())p );
    }

    void at_exit( void (*func)() )
    {
        external_wrapper((void*)func);
    }
}

