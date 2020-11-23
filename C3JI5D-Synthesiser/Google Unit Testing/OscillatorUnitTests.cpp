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

class OscillatorValueTest : public ::testing::Test {
protected:
	oscillator osc1;
};

TEST_F(OscillatorValueTest, SineSynthesisValueTest) {
	osc1.resetPhase(-48);
	EXPECT_FLOAT_EQ(osc1.sine(480), 0) << "Synthesis failed at 0 degrees";
	osc1.resetPhase(1200-48);
	EXPECT_FLOAT_EQ(osc1.sine(480), 1) << "Synthesis failed at 90 degrees";
	osc1.resetPhase(2400-48);
	EXPECT_FLOAT_EQ(osc1.sine(480), 0.00000000000012668789) << "Synthesis failed at 180 degrees";
	osc1.resetPhase(3600-48);
	EXPECT_FLOAT_EQ(osc1.sine(480), -1) << "Synthesis failed at 270 degrees";
	osc1.resetPhase(4800-48);
	EXPECT_FLOAT_EQ(osc1.sine(480), 0) << "Synthesis failed at 360 degrees";
}

TEST_F(OscillatorValueTest, SquareSynthesisValueTest) {
	osc1.resetPhase(-48);
	EXPECT_FLOAT_EQ(osc1.square(480), -1) << "Synthesis failed at 0 degrees";
	osc1.resetPhase(1200 - 48);
	EXPECT_FLOAT_EQ(osc1.square(480), -1) << "Synthesis failed at 90 degrees";
	osc1.resetPhase(2400 - 48);
	EXPECT_FLOAT_EQ(osc1.square(480), -1) << "Synthesis failed at 180 degrees";
	osc1.resetPhase(3600 - 48);
	EXPECT_FLOAT_EQ(osc1.square(480), 1) << "Synthesis failed at 270 degrees";
	osc1.resetPhase(4800 - 48);
	EXPECT_FLOAT_EQ(osc1.square(480), 1) << "Synthesis failed at 360 degrees";
}

TEST_F(OscillatorValueTest, SawSynthesisValueTest) {
	osc1.resetPhase(-48);
	EXPECT_FLOAT_EQ(osc1.saw(480), -0.01) << "Synthesis failed at 0 degrees";
	osc1.resetPhase(1200 - 48);
	EXPECT_FLOAT_EQ(osc1.saw(480), 0.24) << "Synthesis failed at 90 degrees";
	osc1.resetPhase(2400 - 48);
	EXPECT_FLOAT_EQ(osc1.saw(480), 0.49) << "Synthesis failed at 180 degrees";
	osc1.resetPhase(3600 - 48);
	EXPECT_FLOAT_EQ(osc1.saw(480), 0.74) << "Synthesis failed at 270 degrees";
	osc1.resetPhase(4800 - 48);
	EXPECT_FLOAT_EQ(osc1.saw(480), 0.99) << "Synthesis failed at 360 degrees";
}

TEST_F(OscillatorValueTest, TriangleSynthesisValueTest) {
	osc1.resetPhase(-48);
	EXPECT_FLOAT_EQ(osc1.triangle(480), -1) << "Synthesis failed at 0 degrees";
	osc1.resetPhase(1200 - 48);
	EXPECT_FLOAT_EQ(osc1.triangle(480), 0) << "Synthesis failed at 90 degrees";
	osc1.resetPhase(2400 - 48);
	EXPECT_FLOAT_EQ(osc1.triangle(480), 1) << "Synthesis failed at 180 degrees";
	osc1.resetPhase(3600 - 48);
	EXPECT_FLOAT_EQ(osc1.triangle(480), 0) << "Synthesis failed at 270 degrees";
	osc1.resetPhase(4800 - 48);
	EXPECT_FLOAT_EQ(osc1.triangle(480), -1) << "Synthesis failed at 360 degrees";
}

TEST_F(OscillatorValueTest, SineSynthesisValueRangeTest) {
	for (int i = 0; i < 100; ++i) {
		double testVal = abs(osc1.sine(480));
		EXPECT_LE(testVal, 1) << "Synthesis value out of expected bounds [-1.0,1.0] at iteration "<< i;
	}
}

TEST_F(OscillatorValueTest, SquareSynthesisValueRangeTest) {
	for (int i = 0; i < 100; ++i) {
		double testVal = abs(osc1.square(480));
		EXPECT_LE(testVal, 1) << "Synthesis value out of expected bounds [-1.0,1.0] at iteration " << i;
	}
}

TEST_F(OscillatorValueTest, SawSynthesisValueRangeTest) {
	for (int i = 0; i < 100; ++i) {
		double testVal = abs(osc1.saw(480));
		EXPECT_LE(testVal, 1) << "Synthesis value out of expected bounds [-1.0,1.0] at iteration " << i;
	}
}

TEST_F(OscillatorValueTest, TriangleSynthesisValueRangeTest) {
	for (int i = 0; i < 100; ++i) {
		double testVal = abs(osc1.triangle(480));
		EXPECT_LE(testVal, 1) << "Synthesis value out of expected bounds [-1.0,1.0] at iteration " << i;
	}
}