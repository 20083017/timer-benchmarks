// Copyright (C) 2022 ichenq@gmail.com. All rights reserved.
// Distributed under the terms and conditions of the Apache License. 
// See accompanying files LICENSE.

#include "TimerBase.h"
#include "PriorityQueueTimer.h"
#include "QuatHeapTimer.h"
#include "RBTreeTimer.h"
#include "HashedWheelTimer.h"
#include "HHWheelTimer.h"

TimerBase::TimerBase()
{
}

TimerBase::~TimerBase()
{
}

int TimerBase::nextId()
{
    return next_id_++; // we do no duplicate checking here
}


std::shared_ptr<TimerBase> CreateTimer(TimerSchedType sched_type)
{
    switch (sched_type)
    {
    case TimerSchedType::TIMER_PRIORITY_QUEUE:
        return std::shared_ptr<TimerBase>(new PriorityQueueTimer());
    case TimerSchedType::TIMER_QUAD_HEAP:
        return std::shared_ptr<TimerBase>(new QuatHeapTimer());
    case TimerSchedType::TIMER_RBTREE:
        return std::shared_ptr<TimerBase>(new RBTreeTimer());
    case TimerSchedType::TIMER_HASHED_WHEEL:
        return std::shared_ptr<TimerBase>(new HashedWheelTimer());
    case TimerSchedType::TIMER_HH_WHEEL:
        return std::shared_ptr<TimerBase>(new HHWheelTimer());
    default:
        return nullptr;
    }
}
