#include "MIDIReceiver.h"

// this is called every time a key is pressed or released
void MIDIReceiver::onMessageReceived(IMidiMsg* midiMessage) { 
	IMidiMsg::EStatusMsg status = midiMessage->StatusMsg();

	if (status == IMidiMsg::kNoteOn || status == IMidiMsg::kNoteOff) {
		mMidiQueue.Add(midiMessage);
	}
}

void MIDIReceiver::advance() {
	while (!mMidiQueue.Empty()) {
		IMidiMsg* midiMessage = mMidiQueue.Peek();

		if (midiMessage->mOffset > mOffset) break;

		IMidiMsg::EStatusMsg status = midiMessage->StatusMsg();
		int noteNumber = midiMessage->NoteNumber();
		int velocity = midiMessage->Velocity();

		if (status == IMidiMsg::kNoteOn && velocity) {
			if (mKeyStatus[noteNumber] == false) {
				mKeyStatus[noteNumber] = true;
				mNumKeys++;
			}

			if (noteNumber != mLastNoteNumber) {
				mLastNoteNumber = noteNumber;
				mLastFrequency = noteNumberToFrequency(noteNumber);
				mLastVelocity = velocity;
			}
		} else {
			if (mKeyStatus[noteNumber] == true) {
				mKeyStatus[noteNumber] = false;
				mNumKeys -= 1;
			}
		
			if (noteNumber == mLastNoteNumber) {
				mLastFrequency = -1;
				mLastNoteNumber = -1;
				mLastVelocity = 0;
			}
		}
		mMidiQueue.Remove();
	}

	mOffset++;
}

MIDIReceiver::~MIDIReceiver(void)
{
}
