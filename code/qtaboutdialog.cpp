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
#include "qtaboutdialog.h"

#include <QDialogButtonBox>
#include <QLabel>
#include <QPlainTextEdit>
#include <QVBoxLayout>

QtAboutDialog::QtAboutDialog(QWidget* parent)
  : QDialog(parent)
{
  setWindowTitle("About");
  QVBoxLayout* const layout = new QVBoxLayout(this);

  QLabel* const title = new QLabel("Leary Circumplex");
  QFont title_font = title->font();
  title_font.setPointSize(24);
  title_font.setBold(true);
  title->setFont(title_font);
  title->setAlignment(Qt::AlignCenter);
  layout->addWidget(title);

  for (const char* const text: {
    "Version 2.0",
    "(C) 2009-2026 Richèl Bilderbeek",
    "Programmed by Richèl Bilderbeek",
    "Version 1.0 (VCL) on the 25th of August of 2009",
    "Version 2.0 converted to Qt",
    "Licenced under GPL 3.0",
    "From http://www.richelbilderbeek.nl"
  })
  {
    QLabel* const label = new QLabel(QString::fromUtf8(text));
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
  }

  QPlainTextEdit* const licence = new QPlainTextEdit;
  licence->setReadOnly(true);
  licence->setPlainText(QString::fromUtf8(
    "  Leary Circumplex, tool to draw a Leary circumplex\n"
    "  Copyright (C) 2009-2026  Richèl Bilderbeek\n"
    "\n"
    "  This program is free software: you can redistribute it and/or modify\n"
    "  it under the terms of the GNU General Public License as published by\n"
    "  the Free Software Foundation, either version 3 of the License, or\n"
    "  (at your option) any later version.\n"
    "\n"
    "  This program is distributed in the hope that it will be useful,\n"
    "  but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
    "  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
    "  GNU General Public License for more details.\n"
    "  You should have received a copy of the GNU General Public License\n"
    "  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n"
  ));
  QFont mono("Courier New");
  mono.setStyleHint(QFont::Monospace);
  licence->setFont(mono);
  layout->addWidget(licence);

  QDialogButtonBox* const buttons = new QDialogButtonBox(QDialogButtonBox::Ok);
  connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
  layout->addWidget(buttons);
  resize(600, 450);
}
