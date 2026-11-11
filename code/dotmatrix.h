/*
  Leary Circumplex, tool to draw a Leary circumplex
  Copyright (C) 2009-2026  Richel Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// From http://www.richelbilderbeek.nl
#ifndef DOTMATRIX_H
#define DOTMATRIX_H

#include <array>
#include <string>

#include <QImage>

/// A dot-matrix glyph: 7 rows (height) of 5 columns (width).
/// Indices are y-x ordered: glyph[y][x]
using DotMatrixGlyph = std::array<std::array<int, 5>, 7>;

/// Get the dot-matrix glyph of a character.
/// Unknown characters result in an empty glyph
DotMatrixGlyph GetMatrix(const char c);

/// Create an image with the text drawn in dot-matrix characters.
/// Each character is 5 x 7 dots, 6 x 8 including spacing.
/// Each dot is 'scale' x 'scale' pixels.
/// The dots are drawn in 'foreground' on a 'background' (which may be transparent)
QImage CreateDotMatrixImage(
  const std::string& s,
  const int scale = 1,
  const QColor& foreground = Qt::black,
  const QColor& background = Qt::white
);

#endif // DOTMATRIX_H
