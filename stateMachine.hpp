#pragma once
#include <memory>
#include <stack>
#include "State.hpp"
namespace GameEngine
{
	typedef std::unique_ptr<State> StateRef;
	class StateMachine
	{
		std::stack<StateRef> _states;
		StateRef _newState;
		bool _isRemoving;
		bool _isAdding, _isReplacing;

	public:
		StateMachine() {}
		~StateMachine() {}
		void AddState(StateRef newState, bool isReplacing = true);
		void RemoveState();
		void ProcessStateChanges();
		StateRef &GetActiveState();
	};
} // namespace GameEngine