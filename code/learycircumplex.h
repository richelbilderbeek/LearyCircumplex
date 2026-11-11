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
#ifndef LEARYCIRCUMPLEX_H
#define LEARYCIRCUMPLEX_H

#include <array>
#include <string>

#include <QImage>

/// The number of scores (and legend items) in a Leary circumplex
constexpr int n_leary_scores = 8;

/// Draw a Leary circumplex on a square image of 'image_size' pixels.
/// A score goes from 0.0 (none) to 1.0 (full).
/// The image size will be at least 100 pixels
QImage DrawLearyCircumplex(
  const std::array<double, n_leary_scores>& scores,
  const std::array<std::string, n_leary_scores>& legend,
  const int image_size
);

#endif // LEARYCIRCUMPLEX_H
