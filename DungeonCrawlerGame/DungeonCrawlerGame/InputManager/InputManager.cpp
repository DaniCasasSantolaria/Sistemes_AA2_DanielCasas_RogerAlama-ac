#include "InputManager.h"
#include "../ConsoleControl/ConsoleControl.h"

InputSystem::KeyBinding::KeyBinding(int key, OnKeyPress onKeyPress) {
	_key = key;
	_onKeyPress = onKeyPress;
}

InputSystem::KeyBinding::~KeyBinding() {

}

InputSystem::InputSystem() {

}

InputSystem::~InputSystem() {
	for (std::pair<int, KeyBindingList> pair : _keyBindingMap) {
		KeyBindingList bindingsList = pair.second;

		for (KeyBinding* binding : bindingsList) {
			delete binding;
		}
	}
	_keyBindingMap.clear();
}

InputSystem& InputSystem::Instance()
{
	static InputSystem instance;
    return instance;
}

InputSystem::KeyBinding* InputSystem::AddListener(int key, KeyBinding::OnKeyPress onKeyPress){
	_classMutex.lock();

	if (_keyBindingMap.find(key) == _keyBindingMap.end()) {	// Això es que si arriba al final de la llista el if es true
		_keyBindingMap[key] = std::list<KeyBinding*>();
		//_keyBindingMap[key] = KeyBindingList();		// És el mateix que la linia d'adalt
	}

	KeyBinding* keyBinding = new KeyBinding(key, onKeyPress);
	_keyBindingMap[key].push_back(keyBinding);
	
	_classMutex.unlock();

	return keyBinding;
}

void InputSystem::RemoveAndDeleteListener(KeyBinding* keyBinding){
	int key = keyBinding->_key;
	_classMutex.lock();

	if (_keyBindingMap.find(key) != _keyBindingMap.end()) {
		KeyBindingList list = _keyBindingMap[key];		// Estic fent la búsqueda 2 cops, no és òptim
		list.remove(keyBinding);
		delete keyBinding;

		if (list.size() <= 0) {
			_keyBindingMap.erase(key);
		}
	}

	_classMutex.unlock();
}

void InputSystem::AddListenerAsync(int key, KeyBinding::OnKeyPress onKeyPress){
	std::thread* addListenerThread = new std::thread(&InputSystem::AddListener, this, key, onKeyPress);
	addListenerThread->detach();
}

void InputSystem::RemoveAndDeleteListenerAsync(KeyBinding* keyBinding){
	std::thread* removeListenerThread = new std::thread(&InputSystem::RemoveAndDeleteListener, this, keyBinding);
	removeListenerThread->detach();
}

void InputSystem::StartListen(){
	_classMutex.lock();

	if (_state != Stopped) {
		_classMutex.unlock();
		return;
	}
	_state = Starting;

	std::thread* listenLoopThread = new std::thread(&InputSystem::ListenLoop, this);
	listenLoopThread->detach();

	_classMutex.unlock();
}

void InputSystem::StopListen(){
	_classMutex.lock();

	if (_state != Listening) {
		_classMutex.unlock();
		return;
	}
	_state = Stopping;

	_classMutex.unlock();
}

void InputSystem::ListenLoop(){	// 1-.Key Press?-->Execute  2-.Stopping?-->if(true){out of loop}
	_classMutex.lock();

	_state = Listening;
	State currentState = _state;
	CC::Lock();
	CC::ClearKeyBuffer();
	CC::Unlock();

	_classMutex.unlock();

	while (currentState == Listening) {
		int key = CC::ReadNextKey();

		if (key != 0) {
			_classMutex.lock();

			/*if (_keyBindingMap.find(key) != _keyBindingMap.end()) {
				KeyBindingList list = _keyBindingMap[key];

				//TODO
			}*/
			KeyBindingMap::iterator it = _keyBindingMap.find(key);		//Aquesta manera és més òptima que l'anterior però fa el mateix
			if (it != _keyBindingMap.end()) {							//Si arriba al final del mapa vol dir que no l'ha trobat
				KeyBindingList list = it->second;

				for (KeyBinding* binding : list) {
					binding->_onKeyPress();		//Així peta si no s'utilitzen les funcions amb Async perque falta un unlock
					//std::thread* onKeyPressThread = new std::thread(binding->_onKeyPress);
					//onKeyPressThread->detach();
				}
			}

			_classMutex.unlock();
		}

		_classMutex.lock();

		currentState = _state;
		
		_classMutex.unlock();
	}

	_classMutex.lock();

	if (_state == Stopping) {
		_state = Stopped;
	}

	_classMutex.unlock();
}