/*
 * LibrePCB - Professional EDA for everyone!
 * Copyright (C) 2013 LibrePCB Developers, see AUTHORS.md for contributors.
 * http://librepcb.org/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*****************************************************************************************
 *  Includes
 ****************************************************************************************/
#include <QtCore>
#include "strokefont.h"
#include "../fileio/fileutils.h"
#include <fontobene/parser.h>

/*****************************************************************************************
 *  Namespace
 ****************************************************************************************/
namespace librepcb {

/*****************************************************************************************
 *  Constructors / Destructor
 ****************************************************************************************/

StrokeFont::StrokeFont(const FilePath& fontFilePath)
{
    QByteArray content = FileUtils::readFile(fontFilePath); // can throw

    try { // wrap std::exception from fontobene
        mFont.reset(new fontobene::Font(fontobene::parse(content))); // can throw
    } catch (const std::exception& e) {
        throw RuntimeError(__FILE__, __LINE__, QString(tr("Error while parsing '%1': %2"))
                                               .arg(fontFilePath.toNative()).arg(e.what()));
    }
}

StrokeFont::StrokeFont(const StrokeFont& other) noexcept :
    mFont(new fontobene::Font(*other.mFont))
{
}

StrokeFont::~StrokeFont() noexcept
{
}

/*****************************************************************************************
 *  General Methods
 ****************************************************************************************/

QPainterPath StrokeFont::stroke(const QString& text, qreal size) const noexcept
{
    QPainterPath p;
    qreal x = 0;
    foreach (const QChar& c, text) {
        p.addPath(stroke(c, size).translated(x, 0));
        x += size;
    }
    return p;
}

QPainterPath StrokeFont::stroke(const QChar& glyph, qreal size) const noexcept
{
    QPainterPath p;
    foreach (const fontobene::Polyline& l, mFont->value(glyph.unicode()).polylines) {
        if (l.isEmpty()) continue;
        p.moveTo(l.first().x * size / 9, l.first().y * size / 9);
        foreach (const fontobene::Vertex& v, l) {
            p.lineTo(v.x * size / 9, v.y * size / 9);
        }
    }
    return p;
}

/*****************************************************************************************
 *  Operator Overloadings
 ****************************************************************************************/

StrokeFont& StrokeFont::operator=(const StrokeFont& rhs) noexcept
{
    mFont.reset(new fontobene::Font(*rhs.mFont));
    return *this;
}

/*****************************************************************************************
 *  Private Methods
 ****************************************************************************************/

/*****************************************************************************************
 *  End of File
 ****************************************************************************************/

} // namespace librepcb
