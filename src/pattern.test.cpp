#include "pattern.h"
#include "comparinator.h"
#include "form.h"
#include "pch.h"

class PatternTest : public ::testing::Test {
protected:
    Comparinator varComp;
	//TupleTest() {}
	//~TupleTest() override {}
	void SetUp() override {
        varComp = Comparinator();
    }
	// void TearDown() override {  }
};

TEST_F(PatternTest, CanaryTest)
{
    EXPECT_TRUE(true);
}

TEST_F(PatternTest, PatternCtor)
{
    Pattern varP = Pattern();
    EXPECT_TRUE(varP.mbrBlack.checkEqual(Color(0,0,0)));
    EXPECT_TRUE(varP.mbrWhite.checkEqual(Color(1,1,1)));
    EXPECT_TRUE(varP.mbrTransform->checkEqual(IdentityMatrix(4,4)));
}
TEST_F(PatternTest, PatternTransformationAssignment)
{
    Pattern varP = Pattern();
    TranslationMatrix varTM = TranslationMatrix(1,2,3);
    varP.setTransform(varTM);
    EXPECT_TRUE(varP.mbrTransform->checkEqual(varTM));
}
TEST_F(PatternTest, PatternObjectTransformation)
{
    Sphere varObj = Sphere();
    varObj.setTransform(ScalingMatrix(2,2,2));
    // varObj.mbrMaterial->setPattern(new Pattern(Color(0,0,0), Color(1,1,1)));
    varObj.mbrMaterial->setPattern(std::make_unique<Pattern>(Color(0,0,0), Color(1,1,1)));
    Color varColor = varObj.getColorLocal(Point(2,3,4));
    EXPECT_TRUE(varColor.checkEqual(Color(1,1.5,2)));
}
TEST_F(PatternTest, PatternPatternTransformation)
{
    Sphere varObj = Sphere();
    // varObj.mbrMaterial->setPattern(new Pattern(Color(0,0,0), Color(1,1,1)));
    varObj.mbrMaterial->setPattern(std::make_unique<Pattern>(Color(0,0,0), Color(1,1,1)));
    ScalingMatrix varM = ScalingMatrix(2,2,2);
    varObj.mbrMaterial->mbrPattern->setTransform(varM);
    Color varColor = varObj.getColorLocal(Point(2,3,4));
    EXPECT_TRUE(varColor.checkEqual(Color(1,1.5,2)));
}
TEST_F(PatternTest, PatternObjectPatternTransformation)
{
    Sphere varObj = Sphere();
    varObj.setTransform(ScalingMatrix(2,2,2));
    // varObj.mbrMaterial->setPattern(new Pattern(Color(0,0,0), Color(1,1,1)));
    varObj.mbrMaterial->setPattern(std::make_unique<Pattern>(Color(0,0,0), Color(1,1,1)));
    varObj.mbrMaterial->mbrPattern->setTransform(TranslationMatrix(0.5,1,1.5));
    Color varColor = varObj.getColorLocal(Point(2.5,3,3.5));
    EXPECT_TRUE(varColor.checkEqual(Color(0.75,0.5,0.25)));
}

TEST_F(PatternTest, StripePatternCtor)
{
    PatternStripe varP = PatternStripe();
    EXPECT_TRUE(varP.mbrColors[0].checkEqual(varP.mbrWhite));
    EXPECT_TRUE(varP.mbrColors[1].checkEqual(varP.mbrBlack));
}
TEST_F(PatternTest, StripePatternConstantInX)
{
    PatternStripe varP = PatternStripe();
    EXPECT_TRUE(varP.getColorLocal(Point(0,0,0)).checkEqual(varP.mbrWhite));
    EXPECT_TRUE(varP.getColorLocal(Point(0,1,0)).checkEqual(varP.mbrWhite));
    EXPECT_TRUE(varP.getColorLocal(Point(0,2,0)).checkEqual(varP.mbrWhite));
}
TEST_F(PatternTest, StripePatternConstantInZ)
{
    PatternStripe varP = PatternStripe();
    EXPECT_TRUE(varP.getColorLocal(Point(0,0,0)).checkEqual(varP.mbrWhite));
    EXPECT_TRUE(varP.getColorLocal(Point(0,0,1)).checkEqual(varP.mbrWhite));
    EXPECT_TRUE(varP.getColorLocal(Point(0,0,2)).checkEqual(varP.mbrWhite));
}
TEST_F(PatternTest, StripePatternAlternateInX)
{
    PatternStripe varP = PatternStripe();
    EXPECT_TRUE(varP.getColorLocal(Point(0,0,0)).checkEqual(varP.mbrWhite));
    EXPECT_TRUE(varP.getColorLocal(Point(0.9,0,0)).checkEqual(varP.mbrWhite));
    EXPECT_TRUE(varP.getColorLocal(Point(1,0,0)).checkEqual(varP.mbrBlack));
    EXPECT_TRUE(varP.getColorLocal(Point(-0.1,0,0)).checkEqual(varP.mbrBlack));
    EXPECT_TRUE(varP.getColorLocal(Point(-1,0,0)).checkEqual(varP.mbrBlack));
    EXPECT_TRUE(varP.getColorLocal(Point(-1.1,0,0)).checkEqual(varP.mbrWhite));
    EXPECT_TRUE(varP.getColorLocal(Point(-1.9,0,0)).checkEqual(varP.mbrWhite));
    EXPECT_TRUE(varP.getColorLocal(Point(-2,0,0)).checkEqual(varP.mbrWhite));
}
TEST_F(PatternTest, StripePatternObjectTransformation)
{
    Sphere varObj = Sphere();
    varObj.setTransform(ScalingMatrix(2,2,2));
    // varObj.mbrMaterial->setPattern(new PatternStripe());
    varObj.mbrMaterial->setPattern(std::make_unique<PatternStripe>());
    Color varColor = varObj.getColorLocal(Point(1.5,0,0));
    EXPECT_TRUE(varColor.checkEqual(Color(1,1,1)));
}
TEST_F(PatternTest, StripePatternPatternTransformation)
{
    Sphere varObj = Sphere();
    ScalingMatrix varMS = ScalingMatrix(2,2,2);
    // varObj.mbrMaterial->setPattern(new PatternStripe());
    varObj.mbrMaterial->setPattern(std::make_unique<PatternStripe>());
    varObj.mbrMaterial->mbrPattern->setTransform(varMS);
    Color varColor = varObj.getColorLocal(Point(1.5,0,0));
    EXPECT_TRUE(varColor.checkEqual(Color(1,1,1)));
}
TEST_F(PatternTest, StripePatternObjectPatternTransformation)
{
    Sphere varObj = Sphere();
    TranslationMatrix varMT = TranslationMatrix(0.5,0,0);
    varObj.setTransform(ScalingMatrix(2,2,2));
    // varObj.mbrMaterial->setPattern(new PatternStripe());
    varObj.mbrMaterial->setPattern(std::make_unique<PatternStripe>());
    varObj.mbrMaterial->mbrPattern->setTransform(varMT);
    Color varColor = varObj.getColorLocal(Point(2.5,0,0));
    EXPECT_TRUE(varColor.checkEqual(Color(1,1,1)));
}

TEST_F(PatternTest, GradientPattern)
{
    PatternGradient varPG = PatternGradient();
    EXPECT_TRUE(varPG.getColorLocal(Point(0,0,0)).checkEqual(Color(1,1,1)));
    EXPECT_TRUE(varPG.getColorLocal(Point(0.25,0,0)).checkEqual(Color(0.75,0.75,0.75)));
    EXPECT_TRUE(varPG.getColorLocal(Point(0.5,0,0)).checkEqual(Color(0.5,0.5,0.5)));
    EXPECT_TRUE(varPG.getColorLocal(Point(0.75,0,0)).checkEqual(Color(.25,.25,.25)));
}

TEST_F(PatternTest, RingPattern)
{
    PatternRing varPR = PatternRing();
    EXPECT_TRUE(varPR.getColorLocal(Point(0,0,0)).checkEqual(Color(1,1,1)));
    EXPECT_TRUE(varPR.getColorLocal(Point(1,0,0)).checkEqual(Color(0,0,0)));
    EXPECT_TRUE(varPR.getColorLocal(Point(0,0,1)).checkEqual(Color(0,0,0)));
    EXPECT_TRUE(varPR.getColorLocal(Point(0.708,0,0.708)).checkEqual(Color(0,0,0)));
}

TEST_F(PatternTest, RingChecker)
{
    PatternChecker varCh = PatternChecker();
    EXPECT_TRUE(varCh.getColorLocal(Point(0,0,0)).checkEqual(Color(1,1,1)));
    EXPECT_TRUE(varCh.getColorLocal(Point(0.99,0,0)).checkEqual(Color(1,1,1)));
    EXPECT_TRUE(varCh.getColorLocal(Point(1.01,0,0)).checkEqual(Color(0,0,0)));
    EXPECT_TRUE(varCh.getColorLocal(Point(0,0.99,0)).checkEqual(Color(1,1,1)));
    EXPECT_TRUE(varCh.getColorLocal(Point(0,1.01,0)).checkEqual(Color(0,0,0)));
    EXPECT_TRUE(varCh.getColorLocal(Point(0,0,0.99)).checkEqual(Color(1,1,1)));
    EXPECT_TRUE(varCh.getColorLocal(Point(0,0,1.01)).checkEqual(Color(0,0,0)));
}