#include "Patch.h"
//#include "FloatArray.h"
//#include <math.h>

class Template : public Patch {
    
    private:
    
        float phase = 0;
        float phase2 = 0;
        float phase3 = 0;
  
    public:
    
        Template() {
            registerParameter(PARAMETER_A, "");
            registerParameter(PARAMETER_B, "");
            registerParameter(PARAMETER_C, "");
            registerParameter(PARAMETER_D, "");

            registerParameter(PARAMETER_F, ""); // CV 1
            registerParameter(PARAMETER_G, ""); // CV 2
        }
  
    void processAudio(AudioBuffer &buffer) {
      
        float freq = pow(2, getParameterValue(PARAMETER_B)*10) * 20;
        
        float buttA = isButtonPressed(BUTTON_A);
        
        FloatArray left = buffer.getSamples(LEFT_CHANNEL);
        FloatArray right = buffer.getSamples(RIGHT_CHANNEL);
    
        for(int i=0; i<buffer.getSize(); ++i){
        
//        left[i] = gain*left[i];
//        right[i] = gain*right[i];
//        right[i] = 0.1;
            phase3 += (1/48000.0) * 2;
            if(phase3>1) phase3 -= 1;

            phase += (1/48000.0) * freq;
            if(phase>1) phase -= 1;
           
            phase2 += (1/48000.0) * freq * (5.0/3);
            if(phase2>1) phase2 -= 1;

            left[i] = 0.5 * ( sin(phase*M_PI*2) + sin(phase2*M_PI*2) );

            right[i] = left[i] * buttA;

        }
        
        setButton(BUTTON_A, phase3>0.5);
        setButton(BUTTON_B, phase3>0.5);
        setButton(BUTTON_C, phase3<0.5);

        setParameterValue(PARAMETER_F, 0.5);
        setParameterValue(PARAMETER_G, 0.5);
        
    }
};

/*
class Template : public Patch {
	
	private: 
		 FloatArray left_duplicate;
		 FloatArray right_duplicate;
	
    public:
	   Template() {
	
		 registerParameter(PARAMETER_A, "A");
         registerParameter(PARAMETER_B, "B");
         registerParameter(PARAMETER_C, "C");
         registerParameter(PARAMETER_D, "D");
		 left_duplicate = FloatArray::create(getBlockSize());//becomes right channel
         right_duplicate = FloatArray::create(getBlockSize());
		 
	}
	
	~Template() {
		
		FloatArray::destroy(left_duplicate);
		FloatArray::destroy(right_duplicate);
	}
	
	// we need to create and destroy buffers outside of process audio
	void processAudio(AudioBuffer &buffer) {

        float gain_1 = getParameterValue(PARAMETER_A);
        float gain_2 = getParameterValue(PARAMETER_B);
	    float pan_1 = getParameterValue(PARAMETER_C);
        float pan_2 = getParameterValue(PARAMETER_D);
		
	    FloatArray left = buffer.getSamples(LEFT_CHANNEL);
	    left_duplicate.copyFrom(left);
        FloatArray right = buffer.getSamples(RIGHT_CHANNEL);
	    right_duplicate.copyFrom(right);//becomes left channel

	    for (int i = 0; i < buffer.getSize(); ++i) {
			
            left[i] = left[i] * gain_1;
		    left_duplicate[i] = left_duplicate[i] * gain_1;
		    right[i] = right[i] * gain_2;
		    right_duplicate[i] = right_duplicate[i] * gain_2;//right channel to be mixed with left
		    right[i] = (right[i] * pow(pan_2, 0.75)) + (left_duplicate[i] * pow(pan_1,0.75));
		    left[i] = (left[i] * pow(1.-pan_1, 0.75)) + (right_duplicate[i] * pow(1.-pan_2, 0.75));

	    }
	}
};
*/

