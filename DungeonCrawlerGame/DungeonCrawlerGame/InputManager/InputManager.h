#pragma once
#include "InputsConsts.h"
#include <functional>
#include <thread>
#include <mutex>
#include <map>
#include <list>

#define Input InputManager::Instance()

class InputSystem {
public:
	class KeyBinding {
		friend class InputSystem;		// El InputSystem podrà crear i destruir KeyBindings
	public:
		typedef std::function<void()> OnKeyPress;		// Funció landa
	private:
		int _key;
		OnKeyPress _onKeyPress;

		KeyBinding(int key, OnKeyPress onKeyPress);
		~KeyBinding();
	};

	typedef std::list<KeyBinding*> KeyBindingList;
	typedef std::map<int, KeyBindingList> KeyBindingMap;

public:
    static InputSystem& Instance();

	KeyBinding* AddListener(int key, KeyBinding::OnKeyPress onKeyPress);
	void RemoveAndDeleteListener(KeyBinding* keyBinding);

	void AddListenerAsync(int key, KeyBinding::OnKeyPress onKeyPress);
	void RemoveAndDeleteListenerAsync(KeyBinding* keyBinding);

	void StartListen();
	void StopListen();


private:

    InputSystem();
	~InputSystem();

	std::mutex _classMutex;
	KeyBindingMap _keyBindingMap;

	enum State {
		Starting = 0,
		Listening = 1,
		Stopping = 2,
		Stopped = 3
	};

	State _state = Stopped;

	void ListenLoop();
};