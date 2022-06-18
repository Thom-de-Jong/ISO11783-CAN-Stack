#include "can_internal_control_function.hpp"

#include "can_types.hpp"

#include <algorithm>

namespace isobus
{
	std::list<InternalControlFunction *> InternalControlFunction::internalControlFunctionList;

	InternalControlFunction::InternalControlFunction(NAME desiredName, std::uint8_t preferredAddress, std::uint8_t CANPort) :
	  ControlFunction(desiredName, NULL_CAN_ADDRESS, CANPort),
	  stateMachine(preferredAddress, desiredName, CANPort)
	{
		internalControlFunctionList.push_back(this);
	}

	InternalControlFunction::~InternalControlFunction()
	{
		auto thisObject = std::find(internalControlFunctionList.begin(), internalControlFunctionList.end(), this);
		internalControlFunctionList.erase(thisObject);
	}

	InternalControlFunction *InternalControlFunction::get_internal_control_function(std::uint32_t index)
	{
		InternalControlFunction *retVal = nullptr;

		if (index < get_number_internal_control_functions())
		{
			auto listPosition = internalControlFunctionList.begin();

			std::advance(listPosition, index);
			retVal = *listPosition;
		}
		return retVal;
	}

	std::uint32_t InternalControlFunction::get_number_internal_control_functions()
	{
		return internalControlFunctionList.size();
	}

	void InternalControlFunction::update_address_claiming()
	{
		for (auto currentControlFunction : internalControlFunctionList)
		{
			if (nullptr != currentControlFunction)
			{
				currentControlFunction->update();
			}
		}
	}

	void InternalControlFunction::update()
	{
		stateMachine.update();
	}

} // namespace isobus