//
// Created by svirex on 29.03.2020.
//

#include <algorithm>
#include <cstring>
#include <iterator>

#include <SDL.h>

#include "InputSystem.h"

void KeyboardState::initCurrentState() {
  mCurrentState = SDL_GetKeyboardState(nullptr);
}

void KeyboardState::setCurrentState(const Uint8 *currentState) {}

void KeyboardState::clearPreviousState() {
  std::fill(std::begin(mPreviousState), std::end(mPreviousState), 0);
}

void KeyboardState::moveCurrentIntoPrevious() {
  std::memcpy(mPreviousState, mCurrentState, SDL_NUM_SCANCODES);
}

bool KeyboardState::getKeyValue(SDL_Scancode keyCode) const {
  return mCurrentState[keyCode] == 1;
}
ButtonState KeyboardState::getKeyState(SDL_Scancode keyCode) const {
  if (mPreviousState[keyCode] == 0) {
    if (mCurrentState[keyCode] == 0) {
      return ENone;
    } else {
      return EPressed;
    }
  } else {
    if (mCurrentState[keyCode] == 0) {
      return EReleased;
    } else {
      return EHeld;
    }
  }
}

void MouseState::moveCurrentIntoPrevious() {
  mPreviousButtons = mCurrentButtons;
}

const glm::vec2 &MouseState::getPosition() const { return mMousePosition; }

void MouseState::update() {
  int x = 0, y = 0;
  if (mIsRelative) {
    mCurrentButtons = SDL_GetRelativeMouseState(&x, &y);
  } else {
    mCurrentButtons = SDL_GetMouseState(&x, &y);
  }

  mMousePosition.x = static_cast<float>(x);
  mMousePosition.y = static_cast<float>(y);
}

void MouseState::setRelativeMode(bool isRelative) {
  SDL_bool relative = isRelative ? SDL_TRUE : SDL_FALSE;
  SDL_SetRelativeMouseMode(relative);
  mIsRelative = isRelative;
}

bool MouseState::isRelative() const { return mIsRelative; }

bool MouseState::getButtonValue(MouseButtons button) const {
  return (SDL_BUTTON(button) & mCurrentButtons) == 1;
}

ButtonState MouseState::getButtonState(MouseButtons button) const {
  unsigned mask = SDL_BUTTON(button);
  if ((mask & mPreviousButtons) == 0) {
    if ((mask & mCurrentButtons) == 0) {
      return ENone;
    } else {
      return EPressed;
    }
  } else {
    if ((mask & mCurrentButtons) == 1) {
      return EHeld;
    } else {
      return EReleased;
    }
  }
}

bool InputSystem::initialize() {
  mState.keyboard.initCurrentState();
  mState.keyboard.clearPreviousState();
  mState.mouse.setRelativeMode(true);
  return true;
}

void InputSystem::shutdown() {}

void InputSystem::prepareForUpdate() {
  mState.keyboard.moveCurrentIntoPrevious();

  mState.mouse.moveCurrentIntoPrevious();
}

void InputSystem::update() { mState.mouse.update(); }

const InputState &InputSystem::getState() const { return mState; }
