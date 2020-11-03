#include "pch.h"
#include "WaveformSynthesis.h"

class OscillatorPhaseTest : public ::testing::Test {
protected:
	oscillator osc1;
};

TEST_F(OscillatorPhaseTest, TestConstructorPhase) {
	EXPECT_FLOAT_EQ(osc1.getPhase(), 0);
}
TEST_F(OscillatorPhaseTest, TestResetPhase) {
	osc1.resetPhase();
	EXPECT_FLOAT_EQ(osc1.getPhase(), 0);
}

TEST_F(OscillatorPhaseTest, TestResetPhaseSpecificValue) {
	osc1.resetPhase(1);
	EXPECT_FLOAT_EQ(osc1.getPhase(), 1);
}

TEST_F(OscillatorPhaseTest, TestResetPhaseAfterSynthesis) {
	for (int i = 0; i < 1000; ++i) {
		osc1.sine(480);
	}
	osc1.resetPhase();
	EXPECT_FLOAT_EQ(osc1.getPhase(), 0) << "Failure to reset phase after 1000 sine synthesis runs at 480hz";
}

TEST_F(OscillatorPhaseTest, SineSynthesisPhaseTest) {
	for (int i = 0; i < 99; ++i) {
		osc1.sine(480);
		EXPECT_FLOAT_EQ(osc1.getPhase(), (i+1) * 48) << "Phase mismatch with expected value at iteration " << i;
	}
}

TEST_F(OscillatorPhaseTest, SineSynthesisPhaseResetTest) {
	for (int i = 0; i < 100; ++i){
		osc1.sine(480);
	}
	EXPECT_FLOAT_EQ(osc1.getPhase(), 0);
}

TEST_F(OscillatorPhaseTest, SquareSynthesisPhaseTest) {
	for (int i = 0; i < 99; ++i) {
		osc1.square(480);
		EXPECT_FLOAT_EQ(osc1.getPhase(), (i + 1) * 48) << "Phase mismatch with expected value at iteration " << i;
	}
}

TEST_F(OscillatorPhaseTest, SquareSynthesisPhaseResetTest) {
	for (int i = 0; i < 100; ++i) {
		osc1.square(480);
	}
	EXPECT_FLOAT_EQ(osc1.getPhase(), 0);
}

TEST_F(OscillatorPhaseTest, SawSynthesisPhaseTest) {
	for (int i = 0; i < 99; ++i) {
		osc1.saw(480);
		EXPECT_FLOAT_EQ(osc1.getPhase(), (i + 1) * 48) << "Phase mismatch with expected value at iteration " << i;
	}
}

TEST_F(OscillatorPhaseTest, SawSynthesisPhaseResetTest) {
	for (int i = 0; i < 200; ++i) {
		osc1.saw(480);
	}
	EXPECT_FLOAT_EQ(osc1.getPhase(), 0);
}

TEST_F(OscillatorPhaseTest, SawSynthesisPhaseFlipTest) {
	for (int i = 0; i < 100; ++i) {
		osc1.saw(480);
	}
	EXPECT_FLOAT_EQ(osc1.getPhase(), -4800);
}
TEST_F(OscillatorPhaseTest, TriangleSynthesisPhaseTest) {
	for (int i = 0; i < 99; ++i) {
		osc1.triangle(480);
		EXPECT_FLOAT_EQ(osc1.getPhase(), (i + 1) * 48) << "Phase mismatch with expected value at iteration " << i;
	}
}

TEST_F(OscillatorPhaseTest, TriangleSynthesisPhaseResetTest) {
	for (int i = 0; i < 100; ++i) {
		osc1.triangle(480);
	}
	EXPECT_FLOAT_EQ(osc1.getPhase(), 0);
}