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

#ifndef LIBREPCB_PROJECT_BI_PLANE_H
#define LIBREPCB_PROJECT_BI_PLANE_H

/*****************************************************************************************
 *  Includes
 ****************************************************************************************/
#include <QtCore>
#include "bi_base.h"
#include <librepcb/common/fileio/serializableobject.h>
#include <librepcb/common/geometry/region.h>
#include <librepcb/common/uuid.h>

/*****************************************************************************************
 *  Namespace / Forward Declarations
 ****************************************************************************************/
namespace librepcb {
namespace project {

class Project;
class NetSignal;
class Board;
class BGI_Plane;

/*****************************************************************************************
 *  Class BI_Plane
 ****************************************************************************************/

/**
 * @brief The BI_Plane class
 *
 * @author ubruhin
 * @date 2017-11-19
 */
class BI_Plane final : public BI_Base, public SerializableObject
{
        Q_OBJECT

    public:

        // Types
        enum class ConnectStyle {
            None,       ///< do not connect pads/vias to plane
            Thermal,    ///< add thermals to connect pads/vias to plane
            Solid,      ///< completely connect pads/vias to plane
        };

        // Constructors / Destructor
        BI_Plane() = delete;
        BI_Plane(const BI_Plane& other) = delete;
        BI_Plane(Board& board, const BI_Plane& other);
        BI_Plane(Board& board, const SExpression& node);
        //BI_Plane(Board& board, const QString& layerName, const Length& lineWidth, bool fill,
        //           bool isGrabArea, const Point& startPos);
        ~BI_Plane() noexcept;

        // Getters
        const Uuid& getUuid() const noexcept {return mUuid;}
        const QString& getLayerName() const noexcept {return mLayerName;}
        NetSignal& getNetSignal() const noexcept {return *mNetSignal;}
        const Length& getMinWidth() const noexcept {return mMinWidth;}
        const Length& getMinClearance() const noexcept {return mMinClearance;}
        bool getKeepOrphans() const noexcept {return mKeepOrphans;}
        int getPriority() const noexcept {return mPriority;}
        ConnectStyle getConnectStyle() const noexcept {return mConnectStyle;}
        const Length& getThermalGapWidth() const noexcept {return mThermalGapWidth;}
        const Length& getThermalSpokeWidth() const noexcept {return mThermalSpokeWidth;}
        const Path& getOutline() const noexcept {return *mOutline;}
        const QList<Region>& getFragments() const noexcept {return mFragments;}
        bool isSelectable() const noexcept override;

        // General Methods
        void addToBoard() override;
        void removeFromBoard() override;
        void clear() noexcept;
        void rebuild() noexcept;

        /// @copydoc librepcb::SerializableObject::serialize()
        void serialize(SExpression& root) const override;

        // Inherited from BI_Base
        Type_t getType() const noexcept override {return BI_Base::Type_t::Plane;}
        const Point& getPosition() const noexcept override {static Point p(0, 0); return p;}
        bool getIsMirrored() const noexcept override {return false;}
        QPainterPath getGrabAreaScenePx() const noexcept override;
        void setSelected(bool selected) noexcept override;

        // Operator Overloadings
        BI_Plane& operator=(const BI_Plane& rhs) = delete;
        bool operator<(const BI_Plane& rhs) const noexcept;


    private slots:

        void boardAttributesChanged();


    private:
        void init();


        // General
        Uuid mUuid;
        QString mLayerName;
        NetSignal* mNetSignal;
        Length mMinWidth;
        Length mMinClearance;
        bool mKeepOrphans;
        int mPriority;
        ConnectStyle mConnectStyle;
        Length mThermalGapWidth;
        Length mThermalSpokeWidth;
        // style [round square miter] ?
        QScopedPointer<Path> mOutline;
        QScopedPointer<BGI_Plane> mGraphicsItem;

        QList<Region> mFragments;
};

/*****************************************************************************************
 *  End of File
 ****************************************************************************************/

} // namespace project
} // namespace librepcb

#endif // LIBREPCB_PROJECT_BI_PLANE_H