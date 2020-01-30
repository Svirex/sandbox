//
// Created by svirex on 30.01.2020.
//

#include "Actor.h"
#include "Component.h"

Component::Component(Actor *owner, int updateOrder): mOwner(owner), mUpdateOrder(updateOrder) {
    mOwner->addComponent(this);
}

Component::~Component() {
    mOwner->removeComponent(this);
}

int Component::getUpdateOrder() const { return mUpdateOrder; }

void Component::update(float deltaTime) {}
