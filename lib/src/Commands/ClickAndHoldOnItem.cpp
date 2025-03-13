/***
 * Copyright (C) Falko Axmann. All rights reserved.
 * Licensed under the MIT license.
 * See LICENSE.txt file in the project root for full license information.
 ****/

#include "ClickAndHoldOnItem.h"

#include <Scene/Scene.h>

namespace spix {
namespace cmd {

ClickAndHoldOnItem::ClickAndHoldOnItem(ItemPosition path, std::chrono::milliseconds holdTime, MouseButton mouseButton)
: m_holdTime(holdTime)
, m_position(std::move(path))
, m_mouseButton(mouseButton)
{
}

void ClickAndHoldOnItem::execute(CommandEnvironment& env)
{
    env.scene().events().mouseUp(m_item.get(), m_mousePoint, m_mouseButton);
}

bool ClickAndHoldOnItem::canExecuteNow(CommandEnvironment& env)
{
    if (!m_timerInitialized) {
        m_timerInitialized = true;
        m_startTime = std::chrono::steady_clock::now();

        auto path = m_position.itemPath();
        m_item = env.scene().itemAtPath(path);

        if (!m_item) {
            env.state().reportError("ClickAndHoldOnItem: Item not found: " + path.string());
            return false;
        }

        auto size = m_item->size();
        m_mousePoint = m_position.positionForItemSize(size);
        env.scene().events().mouseDown(m_item.get(), m_mousePoint, m_mouseButton);
        return false;
    }

    auto timeSinceStart = std::chrono::steady_clock::now() - m_startTime;
    return timeSinceStart >= m_holdTime;
}

} // namespace cmd
} // namespace spix
