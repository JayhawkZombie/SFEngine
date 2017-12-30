/*
The Jinx library is distributed under the MIT License (MIT)
https://opensource.org/licenses/MIT
See LICENSE.TXT or Jinx.h for license details.
Copyright (c) 2016 James Boer
*/

#pragma once
#ifndef JX_VARIABLE_STACK_FRAME_H__
#define JX_VARIABLE_STACK_FRAME_H__

namespace Jinx
{

	class VariableStackFrame
	{
	public:
		VariableStackFrame();

		// Retrieve the max variable parts for the current frame
		size_t GetMaxVariableParts() const;
		
		// Set max variable parts for the current frame
		void SetMaxVariableParts(size_t varParts);

		// Assign a variable or check that it exists
		bool VariableAssign(const String & name);
		bool VariableExists(const String & name) const;

		// Begin or end a new execution frame, like with a function
		void FrameBegin();
		bool FrameEnd();

		// Begin or end current execution scope
		bool ScopeBegin();
		bool ScopeEnd();

		// Are we at the lowest frame level within the current frame (i.e. not in a scoped execution block)?
		bool IsRootScope() const;

		// Are we in the original execution frame (i.e. not in a function)?
		bool IsRootFrame() const;

		// Get last error message
		const char * GetErrorMessage() const { return m_errorMessage.c_str(); }

	private:

		void CalculateMaxVariableParts();

		typedef std::set<String, std::less<String>, Allocator<String>> VariableSet;
		typedef std::vector<VariableSet, Allocator<VariableSet>> VariableStack;
		struct FrameData
		{
			FrameData() : maxVariableParts(0) {}
			VariableStack stack;
			size_t maxVariableParts;
		};
		typedef std::vector<FrameData, Allocator<FrameData>> VariableFrames;
		VariableFrames m_frames;
		String m_errorMessage;
	};

};

#endif // JX_VARIABLE_STACK_FRAME_H__
