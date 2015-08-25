#pragma once

namespace GeniEngine
{
	/// \brief System base class
	/// inherit from this class when making custom systems
	/// \note The type must ALWAYS be overriden
	class System
	{
	public:
		virtual ~System() {}

		enum Type
		{
			TYPE_INVALID,
			TYPE_POSITION,
			NUM_TYPES
		};

		virtual void process() = 0;
		static Type getType() { return type_; }

	private:
		static Type type_;
	};
}

