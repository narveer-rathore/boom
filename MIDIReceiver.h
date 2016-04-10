#pragma once

#include "IPlug_include_in_plug_hdr.h"

#include <IMidiQueue.h>


class MIDIReceiver
{
private:
	IMidiQueue mMidiQueue;
	static const int keyCount = 128;
	int mNumKeys; // keys played at the moment
	bool mKeyStatus[keyCount];
	int mLastNoteNumber;
	double mLastFrequency;
	int mLastVelocity;
	int mOffset;
	inline double noteNumberToFrequency(int number) {
		return 440.0 * pow(2.0, (number - 69.0) / 12.0);
	}

public:
	MIDIReceiver(void) :
		mNumKeys(0),
		mLastNoteNumber(-1),
		mLastFrequency(-1.0),
		mLastVelocity(0),
		mOffset(0) {
			for (int i = 0; i < keyCount; i++) {
				mKeyStatus[i] = false;
			} 
		};

	inline bool getKeyStatus(int keyIndex) const { return mKeyStatus[keyIndex]; }
	inline int getNumKeys() const { return mNumKeys; }
	inline int getLastNoteNumber() const { return mLastNoteNumber; }
	inline double getLastFrequency() const { return mLastFrequency;}
	inline int getLastVelocity() const { return mLastVelocity; }

	void advance();
	void onMessageReceived(IMidiMsg * midiMessage);

	inline void flush(int nFrames) {mMidiQueue.Flush(nFrames); mOffset = 0; }
	inline void resize(int blockSize) { mMidiQueue.Resize(blockSize); }

	~MIDIReceiver(void);
};

