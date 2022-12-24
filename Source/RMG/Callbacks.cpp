/*
 * Rosalie's Mupen GUI - https://github.com/Rosalie241/RMG
 *  Copyright (C) 2020 Rosalie Wanders <rosalie@mailbox.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 3.
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.
 */
#include "Callbacks.hpp"

#include <RMG-Core/Core.hpp>

//
// Local Variables
//

static CoreCallbacks* l_CoreCallbacks = nullptr;

//
// Exported Functions
//

CoreCallbacks::CoreCallbacks(QObject* parent) : QObject(parent)
{

}

CoreCallbacks::~CoreCallbacks()
{
    l_CoreCallbacks = nullptr;
}

bool CoreCallbacks::Init(void)
{
    // needed for Qt
    qRegisterMetaType<CoreDebugMessageType>("CoreDebugMessageType");

    l_CoreCallbacks = this;
    return CoreSetupCallbacks(this->coreDebugCallback);
}

void CoreCallbacks::Stop(void)
{
    l_CoreCallbacks = nullptr;
}

void CoreCallbacks::coreDebugCallback(CoreDebugMessageType type, std::string context, std::string message)
{
    if (l_CoreCallbacks == nullptr)
    {
        return;
    }

    emit l_CoreCallbacks->OnCoreDebugCallback(type, QString::fromStdString(context), QString::fromStdString(message));
}
