#pragma once

namespace GeniEngine
{
	/// \brief Base component class
	/// \note The type must ALWAYS be overriden
	class Component
	{
	public:
		virtual ~Component(){}

		enum Type
		{
			TYPE_INVALID,
			TYPE_POSITION,
			NUM_TYPES
		};

		static Type getType() { return type_; }

	private:
		static Type type_;
	};
}