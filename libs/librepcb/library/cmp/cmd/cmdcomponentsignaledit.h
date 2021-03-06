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

#ifndef LIBREPCB_LIBRARY_CMDCOMPONENTSIGNALEDIT_H
#define LIBREPCB_LIBRARY_CMDCOMPONENTSIGNALEDIT_H

/*****************************************************************************************
 *  Includes
 ****************************************************************************************/
#include <QtCore>
#include <librepcb/common/undocommand.h>
#include "../componentsignal.h"

/*****************************************************************************************
 *  Namespace / Forward Declarations
 ****************************************************************************************/
namespace librepcb {
namespace library {

/*****************************************************************************************
 *  Class CmdComponentSignalEdit
 ****************************************************************************************/

/**
 * @brief The CmdComponentSignalEdit class
 */
class CmdComponentSignalEdit final : public UndoCommand
{
    public:

        // Constructors / Destructor
        CmdComponentSignalEdit() = delete;
        CmdComponentSignalEdit(const CmdComponentSignalEdit& other) = delete;
        explicit CmdComponentSignalEdit(ComponentSignal& signal) noexcept;
        ~CmdComponentSignalEdit() noexcept;

        // Setters
        void setName(const QString& name) noexcept;
        void setRole(const SignalRole& role) noexcept;
        void setForcedNetName(const QString& name) noexcept;
        void setIsRequired(bool required) noexcept;
        void setIsNegated(bool negated) noexcept;
        void setIsClock(bool clock) noexcept;

        // Operator Overloadings
        CmdComponentSignalEdit& operator=(const CmdComponentSignalEdit& rhs) = delete;


    private: // Methods

        /// @copydoc UndoCommand::performExecute()
        bool performExecute() override;

        /// @copydoc UndoCommand::performUndo()
        void performUndo() override;

        /// @copydoc UndoCommand::performRedo()
        void performRedo() override;


    private: // Data
        ComponentSignal& mSignal;

        QString mOldName;
        QString mNewName;
        SignalRole mOldRole;
        SignalRole mNewRole;
        QString mOldForcedNetName;
        QString mNewForcedNetName;
        bool mOldIsRequired;
        bool mNewIsRequired;
        bool mOldIsNegated;
        bool mNewIsNegated;
        bool mOldIsClock;
        bool mNewIsClock;
};

/*****************************************************************************************
 *  End of File
 ****************************************************************************************/

} // namespace library
} // namespace librepcb

#endif // LIBREPCB_LIBRARY_CMDCOMPONENTSIGNALEDIT_H
