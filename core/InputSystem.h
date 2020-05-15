//
// Created by svirex on 29.03.2020.
//

#ifndef SANDBOX_INPUTSYSTEM_H
#define SANDBOX_INPUTSYSTEM_H

#include <SDL_mouse.h>
#include <SDL_scancode.h>
#include <glm/glm.hpp>

#include "system/ObjectManager.h"

enum ButtonState { ENone, EPressed, EHeld, EReleased };

enum MouseButtons {
  ELeftButton = 1,
  EMiddleButton = 2,
  ERightButton = 3
};

class KeyboardState {
public:

  friend class InputSystem;

  bool getKeyValue (SDL_Scancode keyCode) const;

  ButtonState getKeyState (SDL_Scancode keyCode) const;


private:

  inline void setCurrentState(const Uint8 *currentState);

  inline void initCurrentState();

  inline void clearPreviousState();

  inline void moveCurrentIntoPrevious();

  const Uint8 *mCurrentState = nullptr;

  Uint8 mPreviousState[SDL_NUM_SCANCODES] = {};
};

class MouseState {
public:
  friend class InputSystem;

  const glm::vec2 &getPosition() const;

  bool getButtonValue(MouseButtons button) const;

  ButtonState getButtonState(MouseButtons button) const;

  void update();

  void setRelativeMode(bool isRelative);

  bool isRelative() const;

private:

  void moveCurrentIntoPrevious();

  glm::vec2 mMousePosition = {0, 0};

  Uint32 mCurrentButtons = 0;

  Uint32 mPreviousButtons = 0;

  bool mIsRelative = true;
};


struct InputState {
  KeyboardState keyboard;

  MouseState mouse;
};


class InputSystem {
public:
  bool initialize();

  void shutdown();

  void prepareForUpdate();

  void update();

  const InputState &getState() const;

  MANAGE(InputSystem)

private:

  InputState mState;
};

#endif // SANDBOX_INPUTSYSTEM_H
