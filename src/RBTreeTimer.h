// Copyright © 2022 ichenq@gmail.com All rights reserved.
// See accompanying files LICENSE

#pragma once

#include "TimerBase.h"
#include "RBTree.h"
#include <unordered_map>

// timer scheduler implemented by red-black tree.
// complexity:
//      StartTimer  CancelTimer   PerTick
//       O(logN)     O(logN)      O(logN)
//
class RBTreeTimer : public TimerBase
{
public:
    struct NodeKey
    {
        int id = 0;
        int64_t deadline = 0;
        
        bool operator < (const NodeKey& b) const
        {
            if (deadline == b.deadline) {
                return id > b.id; 
            }
            return deadline < b.deadline;
        }
    };

public:
    RBTreeTimer();
    ~RBTreeTimer();

    TimerSchedType Type() const override
    {
        return TimerSchedType::TIMER_RBTREE;
    }

    // start a timer after `duration` milliseconds
    int Start(uint32_t duration, TimeoutAction action) override;

    // cancel a timer
    bool Cancel(int timer_id) override;

    int Tick(int64_t now = 0) override;

    int Size() const override 
    { 
        return tree_.size();
    }

private:
    void clear();

    // a hashmap timer reference, to make O(1) lookup
    std::unordered_map<int, NodeKey> ref_;

    // same rbtree algorithm implementation for all platforms.
    // you may replace with std::multimap<> instead
    RBTree<NodeKey, TimeoutAction> tree_;
};

