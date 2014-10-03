/*
 *	Simple Gate (header)
 *
 *  File		: SimpleGate.h
 *	Library		: SimpleSource
 *  Version		: 1.12
 *  Class		: SimpleGate, SimpleGateRms
 *
 *	� 2006, ChunkWare Music Software, OPEN-SOURCE
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a
 *	copy of this software and associated documentation files (the "Software"),
 *	to deal in the Software without restriction, including without limitation
 *	the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *	and/or sell copies of the Software, and to permit persons to whom the
 *	Software is furnished to do so, subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included in
 *	all copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *	DEALINGS IN THE SOFTWARE.
 */


#ifndef __SIMPLE_GATE_H__
#define __SIMPLE_GATE_H__

#include "SimpleHeader.h"		// common header
#include "SimpleEnvelope.h"		// for base class
#include "SimpleGain.h"			// for gain functions

namespace chunkware_simple
{
	//-------------------------------------------------------------
	// simple gate
	//-------------------------------------------------------------
	class SimpleGate : public AttRelEnvelope
	{
	public:
		SimpleGate();
		virtual ~SimpleGate() {}

		// parameters
		virtual void   setThresh( SampleType dB );
		virtual SampleType getThresh( void ) const { return threshdB_; }
		
		// runtime
		virtual void initRuntime( void );			// call before runtime (in resume())
		void process( SampleType &in1, SampleType &in2 );	// gate runtime process
		void process( SampleType &in1, SampleType &in2, SampleType keyLinked );	// with stereo-linked key in
		
	private:
		
		// transfer function
		SampleType threshdB_;	// threshold (dB)
		SampleType thresh_;		// threshold (linear)
		
		// runtime variables
		SampleType env_;		// over-threshold envelope (linear)
		
	};	// end SimpleGate class

	//-------------------------------------------------------------
	// simple gate with RMS detection
	//-------------------------------------------------------------
	class SimpleGateRms : public SimpleGate
	{
	public:
		SimpleGateRms();
		virtual ~SimpleGateRms() {}

		// sample rate
		virtual void setSampleRate( SampleType sampleRate );

		// RMS window
		virtual void setWindow( SampleType ms );
		virtual SampleType getWindow( void ) const { return ave_.getTc(); }

		// runtime process
		virtual void initRuntime( void );			// call before runtime (in resume())
		void process( SampleType &in1, SampleType &in2 );	// gate runtime process

	private:

		EnvelopeDetector ave_;	// averager
		SampleType aveOfSqrs_;		// average of squares

	};	// end SimpleGateRms class

}	// end namespace chunkware_simple

// include inlined process function
#include "SimpleGateProcess.inl"

#endif	// end __SIMPLE_GATE_H__
