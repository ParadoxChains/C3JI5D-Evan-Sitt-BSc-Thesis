#include "Delays.h"



delay_chain::delay_chain() {
    memset(memory, 0, 88200 * sizeof(double));
}


double delay_chain::dl(double input, int size, double feedback) {
    if (phase >= size)
    {
        phase = 0;
    }
    output = memory[phase];
    memory[phase] = (memory[phase] * feedback) + (input * feedback) * 0.5;
    phase += 1;
    return(output);

}

double delay_chain::dl(double input, int size, double feedback, int position) {
    if (phase >= size)
    {
        phase = 0;
    }
    if (position >= size)
    {
        position = 0;
    }
    output = memory[position];
    memory[phase] = (memory[phase] * feedback) + (input * feedback) * chandiv;
    phase += 1;
    return(output);

}

fractional_delay::fractional_delay(void) {
    memset(memory, 0, delaySize * sizeof(double));
}

double fractional_delay::dl(double sig, double delayTime, double feedback)
{
    delayTime = fmin(fabs(delayTime), delaySize);
    int32_t delay = delayTime; 
    double fractAmount = delayTime - delay;
    double truncAmount = 1.0f - fractAmount;


    readPointer = writePointer - delay;
    if (readPointer < 0)
    {
        readPointer += delaySize;
    }
    int readPointerFractPart = readPointer - 1;
    if (readPointerFractPart < 0)
    {
        readPointerFractPart += delaySize;
    }

    double y = memory[readPointer] * truncAmount + memory[readPointerFractPart] * fractAmount;


    memory[writePointer] = y * feedback + sig;


    if (++writePointer >= delaySize)
    {
        writePointer -= delaySize;
    }
    
    return y;

}

