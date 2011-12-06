/**
 * This file is a part of LuminanceHDR package.
 * ----------------------------------------------------------------------
 * Copyright (C) 2009 Franco Comida
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * ----------------------------------------------------------------------
 *
 * @author Franco Comida <fcomida@users.sourceforge.net>
 */

#include "ProgressHelper.h"

ProgressHelper::ProgressHelper(QObject *p):
    QObject(p),
    m_terminate(false)
{}

void ProgressHelper::terminate(bool b)
{
    m_terminate = b;
}

bool ProgressHelper::isTerminationRequested()
{
    return m_terminate;
}

void ProgressHelper::emitSetValue(int progress)
{
    emit setValue(progress);
}

void ProgressHelper::emitSetMaximum(int m)
{
    emit setMaximum(m);
}

void ProgressHelper::emitSetMinimum(int m)
{
    emit setMinimum(m);
}

void ProgressHelper::newValue(int progress)
{
    emit setValue(progress);
}


