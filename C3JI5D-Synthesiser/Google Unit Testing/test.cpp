#include "pch.h"
#include "WaveformSynthesis.h"

class OscillatorPhaseTest : public ::testing::Test {
protected:
	oscillator osc1;
};

TEST_F(OscillatorPhaseTest, TestResetPhase) {
	osc1.resetPhase();
	EXPECT_FLOAT_EQ(osc1.getPhase(), 0);
}