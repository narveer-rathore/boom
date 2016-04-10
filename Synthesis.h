#ifndef __SYNTHESIS__
#define __SYNTHESIS__

#include "IPlug_include_in_plug_hdr.h"


#include "Oscillator.h"
#include "MIDIReceiver.h"

class Synthesis : public IPlug
{
public:
	Synthesis(IPlugInstanceInfo instanceInfo);
	~Synthesis();
	void Reset();
	void OnParamChange(int paramIdx);
	void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);
	void ProcessMidiMsg(IMidiMsg* pMsg);
	inline int GetNumKeys() const { return mMIDIReceiver.getNumKeys(); };
	inline bool GetKeyStatus(int key) const { return mMIDIReceiver.getKeyStatus(key); };
	static const int virtualKeyboardMinimumNoteNumber = 48;
	int lastVirtualKeyboardNoteNumber;

private:
	double mFrequency;
	void CreatePresets();

	// core
	Oscillator mOscillator;
	// handle key in Queue
	MIDIReceiver mMIDIReceiver;
	// virtual keyboard
	IControl* mVirtualKeyboard;
	void processVirtualKeyboard();
};

#endif
