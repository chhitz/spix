/***
 * Copyright (C) Falko Axmann. All rights reserved.
 * Licensed under the MIT license.
 * See LICENSE.txt file in the project root for full license information.
 ****/

#include <Spix/Data/ItemPosition.h>

#include <cmath>

namespace spix {

ItemPosition::ItemPosition(ItemPath path, Point proportion, Point offset)
: m_itemPath(std::move(path))
, m_proportion(proportion)
, m_offset(offset)
{
}

const ItemPath& ItemPosition::itemPath() const
{
    return m_itemPath;
}

Point ItemPosition::positionForItemSize(const Size& size) const
{
    return {std::round(size.width * m_proportion.x + m_offset.x), std::floor(size.height * m_proportion.y + m_offset.y)};
}

} // namespace spix
